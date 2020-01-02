#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

class Example {
  public:
  Example(int _val) : val(_val) {}

	mutex mtx;
  condition_variable cond_var;
  int val;
  const int max = 15;
}; // Example

void updateCallBack(Example *ex)
{
    while (ex->val < ex->max)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000));
        {
          unique_lock<mutex> lock(ex->mtx);
          ++ex->val;
          cout << "t1 increments val: " << ex->val << endl;
        }
        ex->cond_var.notify_one();
    }
}

void recv(Example *ex)
{
  int v = ex->val;
  int m = ex->max;
  while (v < m)
  {
     unique_lock<mutex> lock(ex->mtx);
     // wait until val is updated
     ex->cond_var.wait(lock);
		 cout << "t2 detected change in val: " << ex->val << endl;
     v = ex->val;
  }
}

int main()
{
	int val = 10;
	Example ex(val);
	thread t1(updateCallBack, &ex);
	thread t2(recv, &ex);
    t1.join();
    t2.join();
    return 0;
}
