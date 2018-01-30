/* 
 * goodcnt.c - A properly synchronized counter program 
 */
/* $begin goodcnt */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
void *count(void *arg);

/* shared variables */
int niters = 10000000;
volatile unsigned int cnt; /* counter */
sem_t sem;      /* semaphore that protects counter */

int main(int argc, char *argv[]) 
{
    pthread_t tid1, tid2;
    sem_init(&sem, 0, 1);  /* signal = 1 */
    if (argc > 1)
      niters = atoi(argv[1]);
    pthread_create(&tid1, NULL, count, NULL);
    pthread_create(&tid2, NULL, count, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
  
    if (cnt != (unsigned)niters*2)
	printf("BOOM! cnt=%d\n", cnt);
    else
	printf("OK cnt=%d\n", cnt);
    exit(0);
}

/* thread routine */
void *count(void *arg) 
{
    int i;
    for (i = 0; i < niters; i++) {
	sem_wait(&sem);
	cnt++;
	sem_wait(&sem);
    }
    return NULL;
}
/* $end goodcnt */

