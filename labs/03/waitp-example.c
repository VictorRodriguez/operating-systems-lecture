#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t p = fork();
    if ( p == -1 ) {
        perror("fork failed");
        return EXIT_FAILURE;
    }
    else if ( p == 0 ) {
        execl("/bin/sh", "bin/sh", "-c", "./failing", "NULL");
        return EXIT_FAILURE;
    }

    int status;
    if ( waitpid(p, &status, 0) == -1 ) {
        perror("waitpid failed");
        return EXIT_FAILURE;
    }

    if ( WIFEXITED(status) ) {
        const int es = WEXITSTATUS(status);
        printf("exit status was %d\n", es);
    }

    return EXIT_SUCCESS;
}
