#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char user_input[20];
    printf("Bienvenido a la terminal pro de Linux!\n");
    printf("Por favor, introduzca el comando a utilizar = ");
    scanf("%s", user_input);

    char directorio[] = "/bin/";
    strcat(directorio, user_input);
    pid_t p_fork;
    //printf("Original process ID = %d\n", getpid());
    p_fork = fork();  // Fork the process

    if(p_fork < 0){  // Something went wrong
        fprintf(stderr, "An error has occured!");
        exit(-1);
    }
    else if(p_fork == 0){  // Child section
        //printf("Child created succesfully \n");
        printf("Parent PID = %d\n\n", getppid());
        execlp(directorio, user_input, NULL);
    }else{
        wait(NULL);
        exit(0);
    }