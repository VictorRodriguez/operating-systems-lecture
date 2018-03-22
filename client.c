#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHMSZ 27
char SEM_NAME[]= "vik";
int amount, counter, ch, shmid, *shm, *s;
key_t key;
sem_t *mutex;

int main(int argc, char **argv)
{
  amount = atoi(argv[1]);
  //name the shared memory segment
  key = 1000;

  //create & initialize existing semaphore
  mutex = sem_open(SEM_NAME,0,0644,0);
  if(mutex == SEM_FAILED)
    {
      perror("reader:unable to execute semaphore");
      sem_close(mutex);
      exit(-1);
    }

  //create the shared memory segment with this key
  shmid = shmget(key,SHMSZ,0666);
  if(shmid<0)
    {
      perror("reader:failure in shmget");
      exit(-1);
    }

  //attach this segment to virtual memory
  shm = shmat(shmid,NULL,0);

  //start reading
  s = shm;
  if(*s - amount >= 0) {
	sem_wait(mutex);
    *s = (*s - amount);
	sem_post(mutex);
    printf("%d gallons of milk were sold. There are %d gallons left in stock\n", amount, *s);
  }
  else{
	printf("There is not enough milk to complete this transaction. Please sell %d gallons or less.\n", *s);
	exit(-1);
  }
  counter = *s;
 
  //once done signal exiting of reader:This can be replaced by another semaphore
  if(counter <= 0){
    *shm = '*';
    sem_close(mutex);
    shmctl(shmid, IPC_RMID, 0);
  }
  exit(0);
}
