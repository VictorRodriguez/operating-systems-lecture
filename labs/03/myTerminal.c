/*

*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(){
        char instruction[100];
        char stop[] = "stop";
        char ls[] = "ls";
        char date[] = "date";
        char pwd[] = "pwd";
        pid_t pid;
        while(strcmp(instruction, stop) != 0){
                printf("nbrm> ");
                scanf("%s", instruction);
                if(strcmp(instruction, date) == 0 || strcmp(instruction, ls) == 0 || strcmp(instruction, pwd) == 0){
                        pid = fork();
                        if(pid < 0){
                                fprintf(stderr, "Fork Failed");
                                exit(-1);
                        }
                        else if (pid == 0 && strcmp(instruction, ls) == 0){
                                execlp("/bin/ls","ls",NULL);
                        }
                        else if (pid == 0 && strcmp(instruction, date) == 0){
                                execlp("/bin/date","date",NULL);
                        }
                        else if (pid == 0 && strcmp(instruction, pwd) == 0){
                                execlp("/bin/pwd","pwd",NULL);
                        }
                        else{
                                wait(NULL);
                        }
                }
                else if (strcmp(instruction, stop) != 0){
                        printf("nbrm> Wrong command, stop to exit the terminal\n");
                }
        }
        return 0;
}
