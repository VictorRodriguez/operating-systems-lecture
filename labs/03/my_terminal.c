#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_INPUT_SIZE 500

int gato(int argc, char *argv[]){
    FILE archivo;
    ssize_t rSize;
    const int bufSize = 512;
    char buffer[bufSize];

    if ((archivo = syscall(SYS_open, argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "Error abriendo el archivo, el error es = %s\n", errno);
        exit(1);
    }

    while ((rSize = syscall(SYS_read, archivo, &buffer, bufSize)) > 0){
        if (syscall(SYS_write, STDOUT, &buffer, rSize) < 0){
        fprintf(stderr, "Error escribiendo al stdout, error = %s\n", errno);
        exit(1);
        }
    }
    close(archivo);
    return 0;
}

int main(){
    char input[MAX_INPUT_SIZE];
    while (1){
    printf("Intento de Terminal > ");
    fgets(input, MAX_INPUT_SIZE, stdin);

    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "ls") == 0){
        DIR *dir = opendir(".");
        if (dir == NULL){
            perror("opendir");
            exit(1);
        }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL){
        printf("%S\n", entry->d_name);
    }
    closedir(dir);
    } else if (strcmp(input, "pwd") == 0){
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL){
            printf("%s\n", cwd);
        } else{
            perror("getcwd");
            exit(1);
        }
    } else if (strstr(input, "cat") == input){
        char *archivo = input + 4;
        char *argv[] = {"cat", archivo, NULL};
        gato(2, argv);
    }else if (strcmp(input, "clear") == 0){
        system("clear");
    } else if (strcmp(input, "exit") == 0){
        break;
    } else{
        printf("Comando no reconocido: %s\n", input);
    }
  }
  return 0;
}