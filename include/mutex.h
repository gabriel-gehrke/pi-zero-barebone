/* Author: Gabriel Gehrke */

#pragma once
#include <stdbool.h>
#include "common.h"

#define MUTEX_INIT 0
#define SEMAPHORE_INIT(x) x
#define SEMAPHORE_COUNTDOWNLATCH_INIT(x) -x + 1

/*
 * A mutex acts as a lock, which can be used to synchronize threads/processes.
 * It has two states:
 * 
 * 0: unlocked  (false)
 * 1: locked    (true)
 */
typedef volatile bool mutex;

// Used to lock a mutex. If the mutex is already locked, this method will block until the mutex becomes unlocked. It then locks the mutex automatically. 
void mutex_lock(mutex* m);
// Used to unlock a mutex. If the mutex isn't locked, nothing happens.
void mutex_unlock(mutex* m);
// "tries" to lock the mutex, once. This method returns true if the try was a success and the mutex got locked. Otherwise, false gets retuned.
bool mutex_trylock(mutex* m);

/*
 * A semaphore acts as a boundary, which can be used to synchronize access to certain features/resources.
 * It can be initialized using the SEMAPHORE_INIT(x) initializer, where x is the number of available resources.
 * To acquire access to the resource, semaphore_dec can be used.
 * To release that access, semaphore_inc is used.
 * 
 * If no resource is available, semaphore_dec blocks until at least one resource becomes available.
 * That resource then gets claimed and the method returns.
 * 
 * The current value (no. of available resources) of the semaphore can be read with semaphore_val. 
 */
typedef volatile i32 semaphore;

// increments the semaphore's value atomically by one.
void semaphore_inc(semaphore* s);
// decrement's the semaphore's value atomically by one. If the resulting value would be negative, the method blocks until the semaphore's value is at least one.
void semaphore_dec(semaphore* s);
// reads the semaphore's value
i32 semaphore_val(semaphore* s);