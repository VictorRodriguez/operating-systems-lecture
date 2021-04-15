#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

    int var = 5;

	pid_t ret;

	printf("Main Process PID = %d\n", getpid());
	/* fork a child process */
	ret = fork();

    if (ret ==0 ){
        //im inside the child
        printf(" >> ret = %d\n",ret);
    }
        else{
        printf(" ret = %d\n",ret);
        }

	if (ret < 0) {
		/* error occurred */
		fprintf(stderr, "Fork Failed");
		exit (-1) ;
	}

	else if (ret == 0) {
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

