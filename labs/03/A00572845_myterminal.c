#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    while (1) {
        char command[256];
        char *arguments[256];
        int argcounter = 0;

        printf("Terminal de Ernesto Puga, favor de ingresar comando: ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';

        char *tok = strtok(command, " ");

        while (tok != NULL) {
            arguments[argcounter] = tok;
            argcounter++;
            tok = strtok(NULL, " ");
        }
        arguments[argcounter] = NULL;

        if (strcmp(arguments[0], "exit") == 0) {
            return 0;
        }

        pid_t id = fork();

        if (id == 0) {
            execvp(arguments[0], arguments);
            perror("execvp"); 
            return 1;
        } else {
            wait(NULL);
        }
    }
    return 0;
}
