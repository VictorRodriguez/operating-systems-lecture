#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t ret;
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    while (true) {
        char inputStr[256];
        char *argv[256];
        int argc = 0;

        printf("luisdaniel: ");
        fgets(inputStr, sizeof(inputStr), stdin);

        char *token = strtok(inputStr, " \n");

        while (token != NULL) {
            argv[argc] = token;
            argc++;
            token = strtok(NULL, " \n");
        }

        argv[argc] = NULL;

        if (argc > 0 && strcmp(argv[0], "exit") == 0) {
            return 0;
        }

        ret = fork();

        if (ret == 0) {
            execvp(argv[0], argv);
            perror("Error en execvp");
            exit(1);
        } else if (ret > 0) {
            wait(NULL);
        } else {
            perror("Error en fork");
        }
    }

    return 0;
}