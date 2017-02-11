/**************************

The fork call basically makes a duplicate of the current process, 
identical in almost every way 

The new process (child) gets a different process ID (PID) and has the the 
PID of the old process (parent) as its parent PID (PPID). Because the two 
processes are now running exactly the same code, they can tell which is which 
by the return code of fork: 
	
	The child gets 0
	The parent gets the PID of the child.

The exec call is a way to basically replace the entire current process with a 
new program. It loads the program into the current process space and runs it 
from the entry point.

IE: 

+--------+
| pid=7  |
| ppid=4 |
| bash   |
+--------+
    |
    | calls fork
    V
+--------+             +--------+
| pid=7  |    forks    | pid=22 |
| ppid=4 | ----------> | ppid=7 |
| bash   |             | bash   |
+--------+             +--------+
    |                      |
    | waits for pid 22     | calls exec to run ls
    |                      V
    |                  +--------+
    |                  | pid=22 |
    |                  | ppid=7 |
    |                  | ls     |
    V                  +--------+
+--------+                 |
| pid=7  |                 | exits
| ppid=4 | <---------------+
| bash   |
+--------+
    |
    | continues
    V
 
 *************************/


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

	/* fork a child process */ 
	pid = fork();
	if (pid < 0) {
		/* error occurred */ 
		fprintf(stderr, "Fork Failed"); 
		exit (-1) ;
	}
	
	else if (pid == 0) {
		/* child process */
		execlp("/bin/pwd","pwd",NULL); 
	}

	else {
		/* parent process */
		/* parent will wait for the child to complete */ 
		wait(NULL);
		printf("Child Complete\n");
		exit(0);
	}
}

