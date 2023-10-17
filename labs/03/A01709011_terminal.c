#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define OSH_PROMPT "osh> "

void executeCommand(char* cmd) {
    char* args[4];  
    args[0] = "/bin/sh";
    args[1] = "-c";
    args[2] = cmd;
    args[3] = NULL;

    if (fork() == 0) {
        execvp(args[0], args);
        perror("execvp"); 
        exit(1);  
    } else {
        wait(NULL);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    
    while (1) {
        printf(OSH_PROMPT);
        fgets(input, sizeof(input), stdin);
        
        size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strlen(input) > 0) {
            executeCommand(input);
        }
    }

    return 0;
}
