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

#define MAX_COMMAND_LENGTH 100
#define MAX_INPUT_SIZE 1024

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
    char input[MAX_INPUT_SIZE];
    while (1) {
        printf("MiTerminal> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Saliendo de MiTerminal...\n");
            break;
        }

        pid_t child_pid = fork();
        if (child_pid == 0) {
            // Proceso hijo
            if (strstr(input, "cat ") == input) {
                char *archOrigen = input + 4;
                char *argv[] = {"cat", archOrigen, NULL};
                execvp("cat", argv);
                perror("Error al ejecutar el comando");
                exit(1);
            } else if (strcmp(input, "ls") == 0) {
                cus_ls();
            } else if (strcmp(input, "pwd") == 0) {
                cus_pwd();
            } else {
                execl("/bin/sh", "/bin/sh", "-c", input, (char *)0);
                perror("Error al ejecutar el comando");
                exit(1);
            }
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
