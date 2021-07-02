#include "ThreadPool.h"
#include <memory>
#include <cassert>

ThreadPool::ThreadPool() : running_(false),mutex_(), NotEmpty_(mutex_)
{

}

ThreadPool::~ThreadPool()
{
    if(running_)
    {
        stop();
    }
}

ThreadPool::Task ThreadPool::take()
{
    MutexGuard lock(mutex_);
    while(vTask_.empty())
    {
        NotEmpty_.wait();
    }
    Task task(vTask_.front());
    vTask_.pop_front();
    return task;
}

void ThreadPool::start(int ThreadNum)
{
    assert(ThreadNum>=0);
    vThread_.reserve(ThreadNum);
    running_= true;
    for(int i=0;i<ThreadNum;i++)
    {
        vThread_.emplace_back(new Thread(std::bind(&ThreadPool::ThreadRun,this)));
        vThread_[i]->start();
    }
    if(ThreadNum==0 && DefaultTask_)
    {
        DefaultTask_();
    }
}

void ThreadPool::stop()
{
    {
        MutexGuard lock(mutex_);
        running_= false;
        NotEmpty_.notifyAll();
    }
    for(auto & i : vThread_)
    {
        i->join();
    }
}

void ThreadPool::run(Task t)
{
    if(vThread_.empty())
    {
        t();
    }
    MutexGuard lock(mutex_);
    assert(running_);
    vTask_.push_back(std::move(t));
    NotEmpty_.notify();
}


void ThreadPool::ThreadRun()
{
    while (running_)
    {
        Task task(take());
        task();
    }
}
