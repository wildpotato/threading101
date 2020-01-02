#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
class Example {
  public:
  Example();
  
  static void incVal(Example *ex)
  {
      while (ex->val < ex->max)
      {
          this_thread::sleep_for(std::chrono::milliseconds(500));
          {
            unique_lock<mutex> lock(ex->mtx);
            ++ex->val;
          }
          ex->cond_var.notify_one();
      }
  }
  
  static void recvUpdate(Example *ex)
  {
      while (ex->val < ex->max)
      {
         unique_lock<mutex> lock(ex->mtx);
         // wait until num_iter is updated
         ex->cond_var.wait(lock);
         cout << "Detected change in val: " << ex->val << endl;
      }
  }
  mutex mtx;
  condition_variable cond_var;
  int val = 0;
  const int max = 6;
}; // Example

int main()
{
    Example ex;
    thread t1(&Example::incVal, &ex);
    thread t2(&Example::recvUpdate, &ex);
    t1.join();
    t2.join();
    return 0;
}
