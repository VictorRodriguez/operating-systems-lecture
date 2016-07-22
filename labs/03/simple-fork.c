#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

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
		execlp("/bin/ls","ls",NULL); 
	}

	else {
		/* parent process */
		/* parent will wait for the child to complete */ 
		wait(NULL);
		printf("Child Complete\n");
		exit(0);
	}
}

