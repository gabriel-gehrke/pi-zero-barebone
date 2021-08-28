#include "../include/mutex.h"

/* MUTEX */

void mutex_lock(mutex* m) {
    do {
        // wait for lock to get unlocked (change from 1 to 0)
        while(*m);

        // then: use processor support to try and atomically lock
    } while (!mutex_trylock(m));
}

void mutex_unlock(mutex* m) {
    // release lock
    __sync_lock_release(m);
}

bool mutex_trylock(mutex* m) {
    // the builtin method returns 0, if the lock was found unlocked (-> is locked now)
    return __sync_lock_test_and_set(m, 1) == 0;
}


/* SEMAPHORE */

void semaphore_inc(semaphore* s) {
    __sync_add_and_fetch(s, 1);
}

void semaphore_dec(semaphore* s) {
    i32 val;
    do {
        // wait if/while the semaphore is at 0 or below
        while ((val = *s) <= 0);
    } while (!__sync_bool_compare_and_swap(s, val, val-1));
}

i32 semaphore_val(semaphore* s) {
    return *s;
}