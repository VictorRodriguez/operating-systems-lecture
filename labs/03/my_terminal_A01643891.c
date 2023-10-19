#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>


int main(){
        int opc=0;
        bool ciclo=true;
        pid_t pid;

        while(ciclo){
                printf("Opciones\n1:ls\n2.pwd\n3:date\n4.exit\nIn: ");
                scanf("%d", &opc);

                switch(opc){
                        case 1:
                                pid = fork();
                                if (pid == 0) {
                                        /* child process */
                                        execlp("/bin/ls","ls",NULL);
                                }else{
                                        /* parent process */
                                        /* parent will wait for the child to complete */
                                        wait(NULL);
                                }
                                 break;
                                 
                        case 2:
                                pid = fork();
                                if (pid == 0) {
                                        /* child process */
                                        execlp("/bin/pwd","pwd",NULL);
                                }else{
                                        /* parent process */
                                        /* parent will wait for the child to complete */
                                        wait(NULL);
                                }
                                break;
                                
                        case 3:
                                pid = fork();
                                if (pid == 0) {
                                        /* child process */
                                        execlp("/bin/date","date",NULL);
                                }else{
                                        /* parent process */
                                        /* parent will wait for the child to complete */
                                        wait(NULL);
                                }
                                break;
                                
                        case 4:
                                ciclo=false;
                                break;
                        default:
                                printf("Opcion no valida\n");
                }
        }

        return 0;
}
