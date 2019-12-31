#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cond_var;
std::string data;
bool mainReady = false;
bool workerReady = false;

void worker_thread()
{
    // Wait until main() sends data
    {
        std::unique_lock<std::mutex> lock(mtx);
        cond_var.wait(lock, []{return mainReady;});
    }

    std::cout << "Worker thread is processing data: " << data << std::endl;
    data += " after processing";

    // Send data back to main()
    {
        std::lock_guard<std::mutex> lock(mtx);
        workerReady = true;
        std::cout << "Worker thread signals data processing completed\n";
    }
    cond_var.notify_one();
}

int main()
{
    std::thread worker(worker_thread);

    data = "|data to be processed among threads|";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lock(mtx);
        mainReady = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cond_var.notify_one();

    // wait for the worker
    {
        std::unique_lock<std::mutex> lock(mtx);
        cond_var.wait(lock, []{return workerReady;});
    }
    std::cout << "Back in main(), data = " << data << '\n';


    // wait until worker dies finishes execution
    worker.join();
}
