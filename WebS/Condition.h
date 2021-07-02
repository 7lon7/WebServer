#ifndef SS_CONDITION_H
#define SS_CONDITION_H
#include "Mutex.h"
#include "nocopyable.h"


class Condition : nocopyable
{
public:
    explicit Condition(Mutex& mutex) : mutex_(mutex), cond_(PTHREAD_COND_INITIALIZER) {};
    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }
    void wait()
    {
        pthread_cond_wait(&cond_,mutex_.get());
    }
    void notify()
    {
        pthread_cond_signal(&cond_);
    }
    void notifyAll()
    {
        pthread_cond_broadcast(&cond_);
    }
private:
    Mutex& mutex_;
    pthread_cond_t cond_;
};

#endif //SS_CONDITION_H
