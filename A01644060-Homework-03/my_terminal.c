/**
 * Simple shell interface program.
 * 
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* 80 chars per line, per command */
#define STDIN 0
#define STDOUT 1

typedef int Process;
typedef char* String;

//String* split(String str, char separator);

int main(void) {
    char args[256];
    int should_run = 1;
    const char sh[] = "~ ";
    String* splitted;

    while (should_run){
        //Imprime "~ "
        write(STDOUT, sh, sizeof(sh));
        
        //Recibe el string
        if(fgets(args, sizeof(args), stdin) == NULL) {
            perror("Error reading input");
            exit(1);
        }

        //Le quita el "\n"
        size_t len = strlen(args);
        if (len > 0 && args[len - 1] == '\n') {
            args[len - 1] = '\0';
        }

        //Checa si es un comando que la consola puede hacer
        if (strcmp(args, "exit") == 0) break;

        if (strcmp(args, "ls") == 0){
            system("ls");
        }

        else if (strcmp(args, "pwd") == 0){
            system("pwd");
        }

        //En caso de que no se cumpla
        else{
            Process pid = fork();
            if(pid < 0){
                fprintf(stderr, "Error forking, errno = %d\n", errno);
                return 1;
            }

            else if (pid == 0) {
                exit(1);
            }

            else{
                wait(NULL);
            }
        }
    }

    return 0;
}

