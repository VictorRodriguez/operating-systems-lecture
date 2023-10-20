#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 100

void executeCommand(char *command);

int main() {
    char input[MAX_INPUT_LENGTH];
    printf("Bienvenido a la terminal usa los siguientes comandos ls, date, pwd y escribe exit para salirte.\n");
    while (1) {
        printf("uwu> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strcmp(input, "ls") == 0) {
            executeCommand("ls");
        } else if (strcmp(input, "date") == 0) {
            executeCommand("date");
        } else if (strcmp(input, "pwd") == 0) {
            executeCommand("pwd");
        } else {
            printf("Comando no reconocido: %s\n", input);
        }
    }

    return 0;
}

void executeCommand(char *command) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Proceso hijo
        execlp(command, command, NULL);
        perror("Exec failed");
        exit(1);
    } else {
        // Proceso padre
        wait(NULL);
    }
}
