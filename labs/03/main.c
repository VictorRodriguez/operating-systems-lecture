
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define MAX_SIZE_CMD 128
#define MAX_SIZE_ARG 32
#define TRUE 1


int main() {
    // Se asigna el número máximo de caracteres para el comando ingresado por el usuario
    char cmd[MAX_SIZE_CMD];
    // Se asigna el número máximo de argumentos para el comando ingresado por el usuario
    char *argv[MAX_SIZE_ARG];
    // Se asigna un contador para los argumentos
    char i = 0;
    // Se inicializa un puntero de caracteres para guardar los argumentos
    char *ptr;

    while (TRUE) {
        // Imprime el prompt indicando que el shell esta listo para recibir comandos
        printf("Super Shell >>> ");

        // Lee el comando ingresado por el usuario
        fgets(cmd, MAX_SIZE_CMD, stdin);

        // Elimina el salto de linea del final del comando, si el comando no esta vacio
        // y si el ultimo caracter es un salto de linea
        if ((strlen(cmd) > 0) && (cmd[strlen(cmd) - 1] == '\n')) {
            cmd[strlen(cmd) - 1] = '\0';
        }

        // Si el comando esta vacio, se ignora
        if (!strcmp("", cmd)) {
            continue;
        }
        // Si el comando es "exit", se termina el shell
        if (!strcmp("exit", cmd)) {
            break;
        }

        // Se usa strtok para separar el comando en argumentos y usando como
        // delimitador el espacio
        ptr = strtok(cmd, " ");
        // Mientras no se llegue al final del comando, se guardan los argumentos
        // en el arreglo argv
        while (ptr != NULL) {
            argv[i++] = ptr;
            ptr = strtok(NULL, " ");
        }

        i = 0;

        // Se ejecuta el comando ingresado por el usuario, a través de un
        // proceso hijo
        pid_t pid = fork();
        // Si el proceso hijo no se pudo crear, se imprime un mensaje de error
        if (pid < 0) {
            printf("Error creando el proceso hijo\n");
        // Si el proceso hijo se pudo crear, se ejecuta el comando ingresado
        } else if (pid == 0) {
            execvp(argv[0], argv);
            // Libera el espacio de memoria asignado para el comando y los argumentos
        // El proceso padre espera a que el proceso hijo termine de ejecutarse
        } else {
            wait(NULL);
        }

        free(ptr);
    }

    return 0;
}
