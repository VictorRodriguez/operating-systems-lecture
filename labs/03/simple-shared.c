#include <sys/wait.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(){

    /* the identifier for the shared memory segment */
    int segment_id;
    
    /* a pointer to the shared memory segment */
    char *shared_memory;
    
    /* the size (in bytes) of the shared memory segment */ 
    const int size = 4096;
    
    /* allocate a shared memory segment */
    segment_id = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
    
    /* attach the shared memory segment */ 
    shared_memory = (char *) shmat(segment_id, NULL, 0);
    
    /* write a message to the shared memory segment */ 
    sprintf(shared_memory,"Hi there!");

	pid_t pid;

	/* fork a child process */ 
	pid = fork();
	if (pid < 0) {
		/* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		exit (-1) ;
	}
	
	else if (pid == 0) {
		/* child process */
        printf("*%s\n", shared_memory);
	}

	else {
		/* parent process */
		/* parent will wait for the child to complete */ 
		wait(NULL);
		printf("Child Complete\n");

        /* now detach the shared memory segment */ 
        shmdt (shared_memory);
        
        /* now remove the shared memory segment */ 
        shmctl (segment_id, IPC_RMID,NULL);
		
        exit(0);
	}
    
}
