/* Author: Gabriel Gehrke */

#pragma once
#include <stdbool.h>
#include "common.h"

#define MUTEX_INIT (bool)1
#define SEMAPHORE_INIT(x) (i32)x

/*
 * A mutex acts as a lock, which can be used to synchronize threads/processes.
 * It has two states:
 * 
 * 0: unlocked  (false)
 * 1: locked    (true)
 */
typedef volatile bool mutex;

// Used to lock a mutex. If the mutex is already locked, this method will block until the mutex becomes unlocked and locks it automatically. 
void mutex_lock(mutex* m);
// Used to unlock a mutex. If the mutex isn't locked, nothing happens.
void mutex_unlock(mutex* m);

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

void semaphore_inc(semaphore* s);
void semaphore_dec(semaphore* s);
i32 semaphore_val(semaphore* s);