#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCOM 1000
#define MAXLIST 100

void mi_cat(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char c;
        while ((c = fgetc(file)) != EOF) {
            putchar(c);
        }
        fclose(file);
    } else {
        printf("Error: No se pudo abrir el archivo '%s'\n", filename);
    }
}

void mi_ls(const char *dir_path) {
    struct dirent *entry;
    DIR *directory = opendir(dir_path);

    if (directory) {
        while ((entry = readdir(directory)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(directory);
    } else {
        printf("Error: No se pudo abrir el directorio '%s'\n", dir_path);
    }
}

void mi_pwd() {
    char directorio[1024];
    if (getcwd(directorio, sizeof(directorio)) != NULL) {
        printf("Directorio actual: %s\n", directorio);
    } else {
        printf("Error al obtener el directorio actual\n");
    }
}

int main() {
    char inputString[MAXCOM];
    char *parsedArgs[MAXLIST];
    int execFlag = 0;

    while (1) {
        printf("\nMenu de Comandos:\n");
        printf("1. mi_cat (nombre_del_archivo)\n");
        printf("2. mi_ls (directorio)\n");
        printf("3. mi_pwd\n");
        printf("0. Salir\n");
        printf("Ingrese su opción: ");

        if (fgets(inputString, sizeof(inputString), stdin) == NULL) {
            printf("Error al leer la entrada.\n");
            continue;
        }

        inputString[strlen(inputString) - 1] = '\0'; // Elimina el salto de línea.

        if (strcmp(inputString, "0") == 0) {
            printf("Saliendo del programa...\n");
            break;
        } else if (strncmp(inputString, "mi_cat ", 7) == 0) {
            mi_cat(inputString + 7);
        } else if (strncmp(inputString, "mi_ls ", 6) == 0) {
            mi_ls(inputString + 6);
        } else if (strcmp(inputString, "mi_pwd") == 0) {
            mi_pwd();
        } else {
            printf("Comando no reconocido: %s\n", inputString);
        }
    }

    return 0;
}
