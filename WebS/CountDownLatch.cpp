#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count) : mutex_(), CountZero_(mutex_),count_(count)
{

}

void CountDownLatch::wait()
{
    MutexGuard lock(mutex_);
    while(count_>0)
    {
        CountZero_.wait();
    }
}

void CountDownLatch::CountDown()
{
    MutexGuard lock(mutex_);
    --count_;
    if(count_==0)
    {
        CountZero_.notifyAll();
    }
}
