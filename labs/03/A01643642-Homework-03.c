#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    while(1){
        // hacemos un fork para crear un proceso hijo que ejecutará el programa
        pid_t pid = fork();
        if (pid == 0){
            // le pedimos al usuario que ingrese el comando a ejecutar
            char command[100];
            printf("Ivan'Shell %% ");
            fgets(command, 100, stdin);
            command[strlen(command) - 1] = '\0';

            //separamos el string que contiene el comando, en un arreglo de strings separados por espacios
            char *args[10];
            char *token = strtok(command, " ");
            int i = 0;
            while (token != NULL){
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            args[i] = NULL;

            //ejecutamos el comando ingresado
            execvp(args[0], args);
        }
        else {
            // el proceso padre espera a que el hijo termine de ejecutar el comando y asi seguir corriendo el programa
            wait(NULL);
        }
    }
}
