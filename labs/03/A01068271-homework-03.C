// Alumno: Erick Oseguera Salinas
// Matricula: A01068271

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <errno>

#define MAX_COMMAND_LENGTH 100
#define MAX_INPUT_LENGTH 1024

void cus_ls() {
    struct dirent *entry;
    DIR *dp = opendir(".");
    if (dp == NULL) {
        perror("No se puede abrir el directorio.");
        return;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }
    closedir(dp);
}

void cus_pwd() {
    char path[PATH_MAX];
    if (getcwd(path, sizeof(path)) != NULL) {
        printf("%s\n", path);
    } else {
        perror("getcwd() error");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_INPUT_LENGTH];
    int status;

    while (1) {
        printf("osh> "); // Muestra el indicador "osh>"
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Quitamos el espacio después del comando
        input[strcspn(input, "\n")] = 0;

        // Convertimos los input en tokens para poder pasarlos a execvp
        char *token = strtok(input, " ");
        int i = 0;
        // Separamos los argumentos
        while (token != NULL) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            printf("Saliendo del programa...\n");
            break;
        } else if (strcmp(args[0], "ls") == 0) {
            printf("osh> ls\n");
            cus_ls();
        } else if (strcmp(args[0], "pwd") == 0) {
            printf("osh> pwd\n");
            cus_pwd();
        } else {
            // Hacemos un fork del hijo
            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                execvp(args[0], args);
                printf("No se encontro el comando\n");
                exit(1);
            } else if (pid < 0) {
                // Fork fallido si el ID es negativo
                printf("Fork failed\n");
                exit(1);
            } else {
                // Proceso padre
                wait(NULL);
            }
        }
    }

    return 0;
}
