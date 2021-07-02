#ifndef SS_THREAD_H
#define SS_THREAD_H

#include <functional>
#include <pthread.h>
#include <string>
#include "nocopyable.h"
#include "CountDownLatch.h"
#include "Atomic.h"


class Thread : nocopyable
{
public:
    typedef std::function<void ()> ThreadFunc;
    explicit Thread(ThreadFunc func,std::string name=std::string());
   
   	void start();
      
	void join();
   
   	pid_t tid() const;
   
   	~Thread();
private:
   
   	void SetDefaultName();
   
   	bool started_;
    bool joined_;
    std::string ThreadName_;
    ThreadFunc func_;
    CountDownLatch Latch_;
    pthread_t PthreadId_;
    pid_t tid_;
    static AtomicCount ThreadCount_;
};


#endif //SS_THREAD_H
