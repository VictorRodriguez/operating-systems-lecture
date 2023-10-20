#include <stdio.h>
#include <string.h> 
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h> 

int main() {
    char command[50];
    int status;

    while (1) {
        printf("osh> ");
        fgets(command, 50, stdin);

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        pid_t id = fork();

        if (id == -1) { 
            exit(EXIT_FAILURE);
        } else if (id == 0) {
            execlp(command, command, NULL);
            exit(EXIT_FAILURE);
        } else {
            waitpid(id, &status, 0);
        }
    }

    return 0;
}