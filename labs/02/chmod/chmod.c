#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>

int main (){

    int rc;

    rc = chmod("file.txt", 0777);

    if (rc == -1){
        fprintf(stderr, "chmod failed, errno = %d\n", errno);
    }
}
