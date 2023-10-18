#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];
    int should_run = 1;

    while (should_run) {
        printf("MiTerminal> ");
        fgets(command, sizeof(command), stdin);

        // Elimina el carácter de nueva línea al final del comando
        size_t length = strlen(command);
        if (length > 0 && command[length - 1] == '\n') {
            command[length - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            printf("Saliendo de MiTerminal...\n");
            break;
        }

        pid_t child_pid = fork();

        if (child_pid == 0) {
            // Proceso hijo
            char* args[] = {"/bin/sh", "-c", command, NULL};
            execv("/bin/sh", args);
            perror("Error al ejecutar el comando");
            exit(1);
        } else if (child_pid < 0) {
            perror("Error al realizar el fork");
        } else {
            // Proceso padre
            int status;
            waitpid(child_pid, &status, 0);
        }
    }

    return 0;
}
