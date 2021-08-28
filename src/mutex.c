#include "mutex.h"

void mutex_lock(mutex* m) {
    do
    {
        // wait for lock to get unlocked (change from 1 to 0)
        while(*m);

        // then: use processor support to try and atomically lock (set back to 1)
    } while (__sync_lock_test_and_set(m, 1));
}

void mutex_unlock(mutex* m) {
    // release lock
    __sync_lock_release(m);
}

void semaphore_inc(semaphore* s) {
    __sync_add_and_fetch(s, 1);
}

void semaphore_dec(semaphore* s) {
    i32 val;
    do
    {
        // wait if/while the semaphore is at 0 or below
        while ((val = *s) <= 0);
    } while (!__sync_bool_compare_and_swap(s, val, val-1));
}