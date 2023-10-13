//Alejandro Moncada Espinosa - A01638343

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

void ls() {
    struct dirent *entry;
    DIR *ls = opendir(".");
    if (ls == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(ls))) {
        printf("%s\n", entry->d_name);
    }
    closedir(ls);
}

void pwd() {
    char pwd[1024];
    if (getcwd(pwd, sizeof(pwd)) != NULL) {
        printf("%s\n", pwd);
    } else {
        perror("getcwd");
    }
}

void cat(const char *archivo) {
    FILE *file = fopen(archivo, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
    printf("\n");
}

void clear() {
    system("cls || clear");
}

int main() {
    char input[100];
    clear();
    printf("\n");

    while (1) {
        printf("UltimaTerminal> ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';

        if (strcmp(input, "ls") == 0) {
            ls();
        } else if (strcmp(input, "pwd") == 0) {
            pwd();
        } else if (strstr(input, "cat") == input) {
            const char *archivo = input + 4;
            cat(archivo);
        } else if (strcmp(input, "clear") == 0) {
            clear();
        } else if (strcmp(input, "exit") == 0) {
            printf("Saliendo de UltimaTerminal...\n\n");
            break;
        } else {
            printf("Comando %s no reconocido.\n", input);
        }
        printf("\n");
    }
    return 0;
}
