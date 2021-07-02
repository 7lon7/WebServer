#ifndef SS_BLOCKQUEUE_H
#define SS_BLOCKQUEUE_H

#include <queue>
#include "Mutex.h"
#include "Condition.h"
#include <deque>

template<typename T>
class BlockQueue
{
public:
    BlockQueue() : mutex_(), CanGet_(mutex_) {};
    T get()
    {
        MutexGuard lock(mutex_);
        while(q_.empty())
        {
            CanGet_.wait();
        }
        T t(q_.front());
        return t;
    }
    void push(const T& t)
    {
        MutexGuard lock(mutex_);
        q_.push_back(t);
        CanGet_.notify();
    }
    int size()
    {
        MutexGuard lock(mutex_);
        return q_.size();
    }
private:
    std::deque<T> q_;
    Mutex mutex_;
    Condition CanGet_;
};



#endif //SS_BLOCKQUEUE_H
