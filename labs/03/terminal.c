#include <stdbool.h>
#include <stdio.h>
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

        printf("axelpadilla: ");
        scanf("%[^\n]%*c", inputStr);

        char *token = strtok(inputStr, " "); 

        while (token != NULL) {
            argv[argc] = token;
            argc++;
            token = strtok(NULL, " ");
        }

        argv[argc++] = NULL;

        if (strcmp(argv[0], "exit") == 0) {
            return 0;
        }

        ret = fork();

        if (ret == 0) {
            execvp(argv[0], argv);
        } else {
            wait(NULL);
        }

    }

    return 0;
}
