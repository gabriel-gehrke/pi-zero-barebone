#include "../include/mutex.h"
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#define ARR_SIZE 100
#define THREADS 8
#define ARR_ACCESSES 1000000

static void* modify_array(void* args);
static void* modify_array_synced(void* args);

static void arr_check_integrity();
static void arr_init();
static void launch_threads(void* (*f) (void*));


static int array[ARR_SIZE];
static semaphore sem = SEMAPHORE_COUNTDOWNLATCH_INIT(THREADS);
static mutex arrlock = MUTEX_INIT;


int main() {
    // no synchronization
    printf("Accessing the Array without synchronization (%d accesses):\n\n", ARR_ACCESSES);
    arr_init();
    launch_threads(modify_array);
    arr_check_integrity();
    printf("\n\n");

    // synchronization
    printf("Accessing the Array WITH synchronization (%d accesses):\n\n", ARR_ACCESSES);
    arr_init();
    launch_threads(modify_array_synced);
    arr_check_integrity();
    printf("\n\n");

}

void arr_init() {
    for (int i = 0; i < ARR_SIZE; i++) {
        array[i] = i;
    }
}

void arr_check_integrity() {
    for (int i = 0; i < ARR_SIZE; i++) {
        for (int j = i + 1; j < ARR_SIZE; j++) {
            if (array[i] == array[j]) {
                printf("Duplicates found! :(\n");
                return;
            }
        }
    }
    printf("No duplicates! :)\n");
}

void launch_threads(void* (*f) (void*)) {
    // reset semaphore
    sem = SEMAPHORE_COUNTDOWNLATCH_INIT(THREADS);

    // start timer
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, 0);

    pthread_attr_t config;
    pthread_attr_init(&config);
    pthread_attr_setdetachstate(&config, PTHREAD_CREATE_DETACHED);
    for (int i = 0; i < THREADS; i++) {
        pthread_t pid;
        pthread_create(&pid, NULL, f, NULL);
    }

    // wait for all threads
    semaphore_dec(&sem);

    // end timer
    gettimeofday(&end, 0);

    double elapsed = ((double)end.tv_sec + end.tv_usec / 1000000.0) - ((double)start.tv_sec + start.tv_usec / 1000000.0);
    long accesses_per_second = (long) ((THREADS * ARR_ACCESSES) / elapsed);
    printf("all threads terminated in ~%f\n", elapsed);
    printf("that's approximately %ld accesses per second!\n", accesses_per_second);

}

void* modify_array(void* args) {
    printf("thread started...\n");
    int temp;
    for (int i = 0; i < ARR_ACCESSES; i++) {
        int i1 = rand() % ARR_SIZE;
        int i2 = rand() % ARR_SIZE;
        temp = array[i1];
        array[i1] = array[i2];
        array[i2] = temp;
    }

    printf("thread done... (s: %d)\n", sem);
    semaphore_inc(&sem);    
}

void* modify_array_synced(void* args) {
    printf("thread started...\n");
    int temp;
    for (int i = 0; i < ARR_ACCESSES; i++) {
        int i1 = rand() % ARR_SIZE;
        int i2 = rand() % ARR_SIZE;

        mutex_lock(&arrlock);
        temp = array[i1];
        array[i1] = array[i2];
        array[i2] = temp;
        mutex_unlock(&arrlock);
    }

    printf("thread done... (s: %d)\n", sem);
    semaphore_inc(&sem);    
}

