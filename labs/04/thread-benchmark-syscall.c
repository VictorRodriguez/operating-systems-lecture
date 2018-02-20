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
#define TIMEOUT        5
#define BUFSIZE        512

double total_time=0;
//TODO improve with mutex or something better
int count =0;

void *timer() {
    sleep(TIMEOUT);
	printf("Average time used in syscalls: %f seconds\n",(total_time/NUM_THREADS)/count);
    exit(0);
}

void *call_syscall()
{

     
    typedef int File;
    ssize_t readSize;
    const char *test_file = "/dev/null";
    File fileOrigin;
    char buffer[BUFSIZE];

    clock_t start, end;
    double cpu_time_used;

    //TODO make this in a loop to streas syscalls
    while(1){
        ++count;
        start = clock();

	    if ((fileOrigin = syscall(SYS_open,test_file, O_RDONLY)) < 0) {
		fprintf(stderr, "file open failed, error = %s\n", errno);
		exit(1);
	    }
    	while ((readSize = syscall(SYS_read, fileOrigin, &buffer, BUFSIZE)) > 0) {
	    	if (syscall(SYS_write, STDOUT, &buffer, readSize) < 0) {
			fprintf(stderr, "write to stdout failed, error = %s\n", errno);
			exit(1);
		    }
	    }
        close(fileOrigin);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        //printf("%f\n",cpu_time_used);
        total_time +=cpu_time_used;
        end = clock();
    }
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

