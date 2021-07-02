#ifndef SS_MUTEX_H
#define SS_MUTEX_H

#include "nocopyable.h"
#include <unistd.h>
#include <pthread.h>


class Mutex : nocopyable
{
private:
    pthread_mutex_t mutex_;
public:
    Mutex() : mutex_(PTHREAD_MUTEX_INITIALIZER) {};
    ~Mutex()
    {
        lock();
        pthread_mutex_destroy(&mutex_);
    }
    void lock()
    {
        pthread_mutex_lock(&mutex_);
    }
    void unlock()
    {
        pthread_mutex_unlock(&mutex_);
    }
    pthread_mutex_t* get()
    {
        return &mutex_;
    }
};

class MutexGuard
{
private:
    Mutex& mutex_;
public:
    explicit MutexGuard(Mutex& mutex) : mutex_(mutex)
    {
        mutex_.lock();
    }
    ~MutexGuard()
    {
        mutex_.unlock();
    }
};



#endif //SS_MUTEX_H
