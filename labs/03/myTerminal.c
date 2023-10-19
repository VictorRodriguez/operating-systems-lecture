/*
Noé Benjamín Rosales Medina
A00227290
Tarea 1.5 Simple Terminal (fork/exec)
19/10/2023
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(){
        // Variables declaration
        char command[100];
        char stop[] = "stop";
        char ls[] = "ls";
        char date[] = "date";
        char pwd[] = "pwd";
        pid_t pid;

        while(strcmp(command, stop) != 0){
                printf("nbrm> ");
                scanf("%s", command);
                if(strcmp(command, date) == 0 || strcmp(command, ls) == 0 || strcmp(command, pwd) == 0){
                        // Fork a child process
                        pid = fork();
                        if(pid < 0){
                                // Error ocurred
                                fprintf(stderr, "Fork Failed");
                                exit(-1);
                        }
                        else if (pid == 0 && strcmp(command, ls) == 0){
                                // Child process for ls
                                execlp("/bin/ls","ls",NULL);
                        }
                        else if (pid == 0 && strcmp(command, date) == 0){
                                // Child process for date
                                execlp("/bin/date","date",NULL);
                        }
                        else if (pid == 0 && strcmp(command, pwd) == 0){
                                // Child process for pwd
                                execlp("/bin/pwd","pwd",NULL);
                        }
                        else{
                                // Parent waits for the child to complete its process
                                wait(NULL);
                        }
                }
                else if (strcmp(command, stop) != 0){
                        // Any other command
                        printf("nbrm> Wrong command, stop to exit the terminal\n");
                }
        }
        return 0;
}
