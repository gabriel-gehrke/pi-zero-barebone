#pragma once
#include <stdbool.h>
#include "common.h"

#define MUTEX_INIT 1
#define SEMAPHORE_INIT(x) x

/*
 * A mutex acts as a lock, which can be used to synchronize threads/processes.
 * It has two states:
 * 
 * 0: unlocked
 * 1: locked
 */
typedef volatile bool mutex;

// Used to lock a mutex. If the mutex is already locked, this method will block until the mutex becomes unlocked and locks it automatically. 
void mutex_lock(mutex* m);
// Used to unlock a mutex. If the mutex isn't locked, nothing happens.
void mutex_unlock(mutex* m);


typedef volatile i32 semaphore;

void semaphore_inc(semaphore* s);
void semaphore_dec(semaphore* s);