#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

	int parent_pid = getpid();

    printf("parent PID %d\n",parent_pid);

    pid_t pid;

	/* fork a child process */ 
	pid= fork();

    //printf("pid = %d\n", pid);
	if (pid < 0) {
		/* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		exit (-1) ;
	}
	
	else if (pid == 0) {


	    int kid_pid = getpid();
        printf("kid 1 PID %d\n",kid_pid);

		/* child process */
        execlp("/bin/echo","echo","'hola'",NULL); 

	}

	/* fork a child process */ 
	pid= fork();
        
    if (pid < 0) {
        /* error occurred */ 
        fprintf(stderr, "Fork Failed"); 
        exit (-1) ;
    }
    
    else if (pid == 0) {

        int kid_kid_pid = getpid();
        printf("kid 2 PID %d\n",kid_kid_pid);
		/* child process */
        execlp("/bin/ls","ls",NULL); 

    }

    /* parent process */
    /* parent will wait for the child to complete */ 

    wait(NULL);
    printf("Child Complete\n");
    exit(0);
}

