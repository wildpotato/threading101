#include <iostream>// c++ io
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
#include <thread>  // thread
#include <mutex> 
#include <condition_variable>

using namespace std;

const int MAX_ITER = 10;

mutex mtx;
condition_variable cond_var;
unsigned num_iter;

string return_current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

void update_time_thread()
{
    for (num_iter = 0; num_iter < MAX_ITER; ++num_iter) {
        this_thread::sleep_for(std::chrono::milliseconds(2000));
        cout << return_current_time_and_date() << endl;
        {
            unique_lock<mutex> lock(mtx);
            cout << "Incrementing num_iter" << endl;
        }
        cond_var.notify_one();
    }    
}

// Simulate some process that takes more than 1 second
void do_something()
{
    cout << "Doing some work that requires about 0.5 seconds of CPU time" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(500));
    return;
}

void count_second_thread()
{
    
    for (int i = 0; i < MAX_ITER; ++i)
    {
        unique_lock<mutex> lock(mtx);
        // wait until num_iter is updated
        cond_var.wait(lock);
        cout << "Detected updated num_seconds: " << num_iter << std::endl;
    }
    cout << "Max number of iterations reached by thread 1!\n";
}

int main()
{
    cout << "Hello World to Multithreading!\n";
    thread time_thread_1(update_time_thread);
    thread count_thread_2(count_second_thread);
    time_thread_1.join();
    cout << "Time thread ended!\n";
    count_thread_2.join();
    cout << "Count thread ended!\n";
    return 0;
}
