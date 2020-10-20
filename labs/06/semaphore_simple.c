/*
 * =====================================================================================
 *
 *       Filename:  semaphore_simple.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/13/2018 10:15:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Victor Rodriguez (), vm.rod25@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t semaphore;

void threadfunc() {
    while (1) {
        sem_wait(&semaphore);
        printf("Hello from da thread!\n");
        sem_post(&semaphore);
        sleep(1);
    }
}

int main(void) {

    // initialize semaphore, only to be used with threads in this process, set value to 1
    sem_init(&semaphore, 0, 1);

    pthread_t *mythread;

    mythread = (pthread_t *)malloc(sizeof(*mythread));

    // start the thread
    printf("Starting thread, semaphore is unlocked.\n");
    pthread_create(mythread, NULL, (void*)threadfunc, NULL);

    getchar();

    sem_wait(&semaphore);
    printf("Semaphore locked.\n");

    // do stuff with whatever is shared between threads
    getchar();

    printf("Semaphore unlocked.\n");
    sem_post(&semaphore);

    getchar();

    return 0;
}
