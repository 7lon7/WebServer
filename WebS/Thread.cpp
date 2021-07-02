#include "Thread.h"
#include <pthread.h>
#include <functional>
#include <unistd.h>
#include <sys/syscall.h>
#include <utility>
#include <assert.h>

namespace CurrentThread
{
    thread_local int tid_l=0;
    thread_local const char* name_l="default";
    void CacheTid()
    {
        if (tid_l==0)
        {
            tid_l=static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
    inline int tid()
    {
        if (__builtin_expect(tid_l==0,0))
        {
            CacheTid();
        }
        return tid_l;
    }
    bool IsMainThread()
    {
        return tid()==::getpid();
    }
}



class mainThreadInit
{
public:
    mainThreadInit()
    {
        CurrentThread::tid();
        CurrentThread::name_l="main";
    }
};

__attribute__((unused)) mainThreadInit init;

struct ThreadInfo
{
    typedef std::function<void ()> ThreadFunc;
    ThreadFunc func_;
    pid_t* tid_;
    CountDownLatch* Latch_;
    std::string ThreadName_;


    ThreadInfo(pid_t* tid,ThreadFunc& func,pthread_t* PthreadId,CountDownLatch* latch,std::string& name)
    :
    func_(func),tid_(tid),Latch_(latch) ,ThreadName_(name)
    {

    };

    void ThreadRun()
    {
        *tid_=CurrentThread::tid();
        CurrentThread::name_l=ThreadName_.c_str();
        Latch_->CountDown();
        tid_= nullptr;
        Latch_= nullptr;
        func_();
    }
};


static void* start_routine(void* arg)
{
    auto* ti=static_cast<ThreadInfo*>(arg);
    ti->ThreadRun();
    delete ti;
    return nullptr;
}

AtomicCount Thread::ThreadCount_;

Thread::Thread(ThreadFunc func,std::string  name)
:
started_(false),
joined_(false),
ThreadName_(std::move(name)),
func_(std::move(func)),
Latch_(1),
PthreadId_(0),
tid_(0)
{
    SetDefaultName();
}


void Thread::start()
{
    auto* ti=new ThreadInfo(&tid_,func_,&PthreadId_,&Latch_,ThreadName_);
    started_= true;
    if(pthread_create(&PthreadId_,nullptr,start_routine,ti))
    {
        started_= false;
        delete ti;
    }
    else
    {
        Latch_.wait();
        assert(tid_>0);
    }
}

void Thread::join()
{
    assert(started_);
    assert(!joined_);
    pthread_join(PthreadId_,nullptr);
    joined_= true;
}

void Thread::SetDefaultName()
{
    int num=ThreadCount_.get_then_add();
    if(ThreadName_.empty())
    {
        char t[32]={0};
        snprintf(t, sizeof(t),"thread_%d",num);
        ThreadName_=t;
    }
}



Thread::~Thread()
{
    if(started_&&!joined_)
    {
        pthread_detach(PthreadId_);
    }
}

pid_t Thread::tid()  const
{
    return tid_;
}


