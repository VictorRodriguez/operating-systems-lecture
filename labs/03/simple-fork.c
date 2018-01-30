#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

    int var = 0; 

	pid_t pid;

	printf("Main Process PID = %d\n", getpid()); 
	/* fork a child process */ 
	pid = fork();

    if (pid ==0 ){
        //im inside the child
        printf(" >>pid = %d\n",pid);
    }
        else{
        printf(" pid = %d\n",pid);
        }

	if (pid < 0) {
		/* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		exit (-1) ;
	}
	
	else if (pid == 0) {
		/* child process */
	    printf(">> Parent PID = %d\n", getppid()); 
		printf(">> Child PID = %d\n", getpid()); 
        var = var +10;
        printf(">>var = %d\n",var);
	}

	else {
		/* parent process */
		/* parent will wait for the child to complete */ 
		wait(NULL);
		printf("Child Complete\n");
	}

    printf("var = %d\n",var);
}

