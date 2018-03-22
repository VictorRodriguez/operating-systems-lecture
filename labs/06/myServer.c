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

int main(int argc, char **argv)
{
  int milk = atoi(argv[1]);
  int ch;
  int shmid;
  key_t key;
  int *shm,*s;
  sem_t *mutex;
  printf("Initialized the server with %d gallons of milk. Awaiting transactions...\n", milk);
  //name the shared memory segment
  key = 1000;

  //create & initialize semaphore
  mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
  if(mutex == SEM_FAILED)
    {
      perror("unable to create semaphore");
      sem_unlink(SEM_NAME);
      exit(-1);
    }

  //create the shared memory segment with this key
  shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
  if(shmid<0)
    {
      perror("failure in shmget");
      exit(-1);
    }

  //attach this segment to virtual memory
  shm = shmat(shmid,NULL,0);

  //start writing into memory
  s = shm;
  sem_wait(mutex);
  *s = milk;
  sem_post(mutex);

  //the below loop could be replaced by binary semaphore
  while(*shm != '*')
    {
      sleep(1);
    }
  printf("All gallons of milk have been sold. Closing server...\n");
  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(shmid, IPC_RMID, 0);
  exit(0);
}
