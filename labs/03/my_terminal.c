#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_LINE 80 // 80 chars per line, per command

int main() {
    // Entrada del usuario
    char args[MAX_LINE/2 + 1];  // Línea de comandos (of 80) tiene máximo de 40 caracteres
    int should_run = 1; // Determina cuando salir del programa
    char* command; // Array de comandos ingresados por el usuario

    // Programa inicial
    while (should_run) {
        printf("spiegel>"); // Imprimir el prompt
        fgets(args, sizeof(args), stdin); // Leer el comando del usuario y almacenarlo en args

        // Elimina el carácter de nueva línea '\n' de la entrada del usuario
        args[strlen(args)-1] = '\0';

        // Si el usuario escribe exit, termina
        if (strcmp(args, "exit") == 0) {
            should_run = 0;
        }

        // Fork un proceso del hijo
        pid_t pid = fork();

        // Error al crear el fork
        if (pid < 0) {
            fprintf(stderr, "Fork Failed");
            exit (-1) ;
        }

        // Se logró crear un hijo 
        else if (pid == 0) {
            // Proceso del hijo (Terminal como tal)
            // El proceso hijo ejecutará el comando ingresado por el usuario
            char* token = strtok(args, " ");
            char* arguments[MAX_LINE/2 + 1];
            int i = 0;
            while (token != NULL) {
                arguments[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            arguments[i] = NULL;

            // Ejecuta el comando con los argumentos divididos
            execvp(arguments[0], arguments);

            // En caso de que execvp falle, muestra un mensaje de error
            // perror("Error en execvp");
            exit(1); // Termina el proceso hijo con un código de error 
        }

        // Proceso del padre
        else {
            // Padre espera a que el proceso del hijo termine y termina el programa
            wait(NULL);
        }
    }
    return 0;
}
