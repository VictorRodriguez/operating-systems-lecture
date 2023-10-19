#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

        pid_t pid;
        int n;

        do{
                printf("\nWelcome to cat terminal!\n");

                printf("\nMENU:\n[1] See my files\n[2] Where am I?\n[3] See the date\n[4] See this year's calendar\n[5] Exit");
                printf("\nEnter your choice: ");
                scanf("%d", &n);
                printf("\n");
                switch(n){
                        case 1:
                                pid = fork();
                                if(pid == 0){
                                        execlp("/bin/ls","ls",NULL);
                                }else{
                                        wait(NULL);
                                } 
                                break;
                        case 2:
                                pid = fork();
                                if(pid == 0){
                                        execlp("/bin/pwd","pwd",NULL);
                                }else{
                                        wait(NULL);
                                }
                                break;
                        case 3:
                                pid = fork();
                                if(pid == 0){
                                        execlp("/bin/date","date",NULL);

                                }else{
                                        wait(NULL);
                                }
                                break;
                        case 4:
                                pid = fork();
                                if(pid == 0){
                                        execlp("/bin/cal","cal",NULL);
                                }else{
                                        wait(NULL);
                                }
                                break;
                        case 5:
                                printf("Exiting...\n");
                                break;
                        default:
                                printf("Write a proper option");
                }
        }while(n!=5);
                return 0;
}
