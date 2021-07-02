#ifndef SS_ATOMIC_H
#define SS_ATOMIC_H

#include <cstdint>
#include "nocopyable.h"

class AtomicCount : nocopyable
{
public:
    explicit AtomicCount(int count=1) : count_(count)
    {

    };
    int get()
    {
        return __sync_val_compare_and_swap(&count_, 0, 0);
    };
    int get_then_add(int a=1)
    {
        return __sync_fetch_and_add(&count_, a);
    };
    int add_then_get(int a=1)
    {
        return get_then_add(a)+a;
    };
    int set(int a)
    {
        return __sync_lock_test_and_set(&count_, a);
    };
    int sub_then_get(int a=-1)
    {
        return add_then_get(-1);
    }
    int get_then_sub(int a=-1)
    {
        return get_then_add(-1);
    }
private:
    int count_;
};

#endif //SS_ATOMIC_H
