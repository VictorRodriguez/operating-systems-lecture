#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    char *token;
    int i;

    printf("./my_terminal\n");

    while (1) {
        printf("osh> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            exit(0);
        }

        // Eliminar el salto de línea al final
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Tokenizar la entrada
        i = 0;
        token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Si el comando es "exit", salir del bucle
        if (strcmp(args[0], "exit") == 0) {
            exit(0);
        }

        // Crear un proceso hijo para ejecutar el comando
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            exit(1);
        } else if (pid == 0) {
            // Proceso hijo
            execvp(args[0], args);
            perror("Error al ejecutar el comando");
            exit(1);
        } else {
            // Proceso padre espera a que el hijo termine
            wait(NULL);
        }
    }

    return 0;
}

