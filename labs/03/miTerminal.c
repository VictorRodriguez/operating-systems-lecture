#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 1024

void cat(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error abriendo el archivo");
        return;
    }

    char line[MAX_INPUT_SIZE];
    while (fgets(line, MAX_INPUT_SIZE, file)) {
        printf("%s", line);
    }

    fclose(file);
}

void ls() {
    struct dirent *entry;
    DIR *dp = opendir(".");
    if (dp == NULL) {
        perror("Error abriendo el directorio");
        return;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
}

void pwd() {
    char cwd[MAX_INPUT_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Directorio actual: %s\n", cwd);
    } else {
        perror("Error obteniendo el directorio actual");
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("miTerminal> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';  // Elimina el carácter de nueva línea

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strncmp(input, "cat", 3) == 0) {
            char *filename = input + 4;  // Ignora "cat " en el input
            cat(filename);
        } else if (strcmp(input, "ls") == 0) {
            ls();
        } else if (strcmp(input, "pwd") == 0) {
            pwd();
        } else {
            printf("Comando no reconocido: %s\n", input);
        }
    }

    return 0;
}
