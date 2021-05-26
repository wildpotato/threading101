#include <iostream>// c++ io
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
#include <thread>  // thread
#include <atomic>

using namespace std;

atomic<unsigned> num_iter;

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
    for (num_iter = 0; num_iter < 10; ++num_iter) {
        this_thread::sleep_for(std::chrono::milliseconds(2000));
        cout << return_current_time_and_date() << endl;
    }
}

// Simulate some process that takes more than 1 second
void do_something()
{
    this_thread::sleep_for(std::chrono::milliseconds(1500));
    return;
}

void count_second_thread()
{
    long curr = -1;
    long prev = -1;
    while (true)
    {
        curr = atomic_load(&num_iter);
        if (curr == prev) {
            cout << "Thread 1 is not incrementing num_seconds, exit thread 2 now\n";
            break;
        }
        else {
            cout << "Detected updated num_seconds: " << num_iter << std::endl;
            do_something();
            prev = curr;
        }
        this_thread::sleep_for(std::chrono::milliseconds(600));
    }
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
