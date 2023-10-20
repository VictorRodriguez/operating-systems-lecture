#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int option;
    int pid;

    do {

        printf("Menu:\n");
        printf("1. ls: List directory contents\n");
        printf("2. pwd: Show full path of the current directory\n");
        printf("3. date: Show the system's date and time\n");
        printf("4. Exit the program\n");
        printf("Please select an option: ");

        scanf("%d", &option);

        switch (option) {
          
            //ls
            case 1:
                pid = fork();
              
                if (pid == 0) {
                    execlp("/bin/ls", "ls", NULL);
                  
                } else if (pid > 0) {
                    wait(NULL);
                  
                } else {
                    printf("Error creating the child process.\n");
                }
                break;
           
            //pwd
            case 2:
                pid = fork();
              
                if (pid == 0) {
                    execlp("/bin/pwd", "pwd", NULL);
                  
                } else if (pid > 0) {
                    wait(NULL);
                  
                } else {
                    printf("Error creating the child process.\n");
                }
                break;

            //date
            case 3:
                pid = fork();
                if (pid == 0) {
                    execlp("/bin/date", "date", NULL);
                  
                } else if (pid > 0) {
                    wait(NULL);
                  
                } else {
                    printf("Error creating the child process.\n");
                }
                break;
           
            //exit
            case 4:
                printf("Exiting the program\n");
                break;
            
          
            default:
                printf("Option not valid. Please enter a valid option.\n");
        }

    } while (option != 4);

   return 0;
}
