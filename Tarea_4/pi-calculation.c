/* Adair Ibarra Bautista A01152520
 * REFERENCIAS:
 * https://github.com/michaelballantyne/montecarlo-pi/blob/master/pi.c
 * http://man7.org/linux/man-pages/man3/pthread_attr_init.3.html
 * http://www.qnx.com/developers/docs/6.4.1/neutrino/lib_ref/p/pthread_mutex_lock.html */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long incircle = 0;
long points_per_thread;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *runner() {
    long incircle_thread = 0;

    unsigned int rand_state = rand();
    long i;
    for (i = 0; i < points_per_thread; i++) {
       
        double x = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;
        double y = rand_r(&rand_state) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

        if (x * x + y * y < 1) {
            incircle_thread++;
        }
    }
    

    /* The pthread_mutex_lock() function locks the mutex object referenced by mutex.
     * if one thread has mutex locked, the other thread waits until it's unlocked, before continuing */

    pthread_mutex_lock(&mutex);
    incircle += incircle_thread;
    pthread_mutex_unlock(&mutex);
}


int main(int argc, const char *argv[])
{

    long totalpoints = 300000;
    int thread_count = 5;
    points_per_thread = totalpoints / thread_count;

    pthread_t *threads = malloc(thread_count * sizeof(pthread_t));



    /* The pthread_attr_init() function initializes the thread attributes
     * object pointed to by attr with default attribute values */

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    int i;
    for (i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], &attr, runner, (void *) NULL);
    }


    /* The pthread_join() function suspends execution of the calling thread until
     * the target thread terminates, unless the target thread has already terminated. */


    for (i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    free(threads);

    printf("Pi: %f\n", (4. * (double)incircle) / ((double)points_per_thread * thread_count));

    return 0;
}
