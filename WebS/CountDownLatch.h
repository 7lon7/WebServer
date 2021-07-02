#ifndef SS_COUNTDOWNLATCH_H
#define SS_COUNTDOWNLATCH_H


#include "nocopyable.h"
#include "Mutex.h"
#include "Condition.h"


class CountDownLatch : nocopyable
{
public:
    explicit CountDownLatch(int count);
    
	void wait();
    
	void CountDown();
private:
    Mutex mutex_;
    Condition CountZero_;
    int count_;
};


#endif //SS_COUNTDOWNLATCH_H
