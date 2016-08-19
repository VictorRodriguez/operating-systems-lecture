#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>


int main (){

    int rc;

    rc = syscall(SYS_chmod, "/etc/passwd", 0444);

    if (rc == -1){
        fprintf(stderr, "chmod failed, errno = %d\n", errno);
    }
}
