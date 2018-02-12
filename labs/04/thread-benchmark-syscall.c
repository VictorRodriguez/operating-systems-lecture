#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>

#define STDOUT         1
#define NUM_THREADS    5
#define TIMEOUT        10

typedef int File;
File fileOrigin;
ssize_t readSize;
const int bufSize = 512;
char buffer[bufSize];
const char *test_file = "/dev/null";

double total_time=0;

void timer() {
    sleep(TIMEOUT);
	printf("Average time used in syscalls: %f\n",total_time/NUM_THREADS);
    exit(0);
}

void *call_syscall()
{

     
     clock_t start, end;
     double cpu_time_used;
     
     start = clock();
//TODO make this in a loop to streas syscalls
//    while(1){
	    if ((fileOrigin = syscall(SYS_open,test_file, O_RDONLY)) < 0) {
		fprintf(stderr, "file open failed, error = %s\n", errno);
		exit(1);
	    }
    	while ((readSize = syscall(SYS_read, fileOrigin, &buffer, bufSize)) > 0) {
	    	if (syscall(SYS_write, STDOUT, &buffer, readSize) < 0) {
			fprintf(stderr, "write to stdout failed, error = %s\n", errno);
			exit(1);
		    }
	    }
	close(fileOrigin);
 //   }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    total_time +=cpu_time_used;
	printf("Time used in syscalls: %f\n",cpu_time_used);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];

    int rc;
    long t;

    for(t=0;t<NUM_THREADS;t++){
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL,call_syscall,NULL);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_t timer_thread;
    rc = pthread_create(&timer_thread,NULL,timer,NULL);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }

    pthread_exit(NULL);
}

