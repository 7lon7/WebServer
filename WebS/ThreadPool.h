#ifndef SS_THREADPOOL_H
#define SS_THREADPOOL_H

#include "Mutex.h"
#include "Condition.h"
#include <vector>
#include "Thread.h"
#include <deque>
#include <memory>

class ThreadPool
{
public:
    typedef std::function<void()> Task;
    ThreadPool();
    ~ThreadPool();
    
	void start(int ThreadNum);
    
	void stop();
    
	void run(Task t);
private:
    
	Task take();
    
	void ThreadRun();
private:
    Task DefaultTask_;
    bool running_;
    Mutex mutex_;
    Condition NotEmpty_;
    std::vector<std::unique_ptr<Thread>> vThread_;
    std::deque<Task> vTask_;
};


#endif //SS_THREADPOOL_H
