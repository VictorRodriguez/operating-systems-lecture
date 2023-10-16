#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_INPUT_LENGTH];
    int status;
   
    while (1) {
        printf("Ingrese el comando: ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Quitamos el espacio despues del comando
        input[strcspn(input, "\n")] = 0;

        // Convertimos los input en token para poder pasarlos al execvp
        char *token = strtok(input, " ");
        int i = 0;
        // Separamos los argumentos
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        // Hacemos un fork del hijo
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            //args[0] = "ls";
            //args[1] = "null";
            execvp(args[0], args);
            printf("No se encontro el comando\n");
            exit(1);
        } else if (pid < 0) {
            // Fork fallido si el id es negativo
            printf("Fork failed\n");
            exit(1);
        } else {
            // Proceso padre
            wait(NULL);
        }
    }

    return 0;
}
