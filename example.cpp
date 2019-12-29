#include <iostream>// c++ io
#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time
#include <string>  // string
#include <thread>  // thread

using namespace std;

const int num_seconds = 10;

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
    for (int i = 0; i < num_seconds; ++i) {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        cout << return_current_time_and_date() << endl;
    }    
}

int main()
{
    cout << "Hello World to Multithreading!\n";
    thread time_thread_1(update_time_thread);
    time_thread_1.join();
    cout << "Time thread ended!\n";
    return 0;
}
