#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS    5
#define MAX            100

long result = 0;

void timer(int timer) {
    sleep(timer);
    printf("\nResult = %d\n",result);
    exit(0);
}

void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    // calculating some additions
    for (int count = 0; count < MAX ; count ++){
        result++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];

    int rc;
    long t;
    int timeout = 5;

    for(t=0;t<NUM_THREADS;t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    printf("Time out = %d\n", timeout );
    pthread_t timer_thread;
    rc = pthread_create(&timer_thread,NULL,timer,timeout);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }

    pthread_exit(NULL);
}

