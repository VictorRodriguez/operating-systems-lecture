// Laboratorio 3 - Crear una terminal (cat, pwd, ls)
// AUTOR: Fernanda Díaz Gutiérrez

// Includes necesarios 

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define BUF_SIZE 512

// 1. CAT (Concatenate)
typedef int File; 
int cat(int argc, char const *argv[]) {
	File fileOrigin;
	ssize_t readSize;
    const int bufSize = BUF_SIZE;
    char buffer[bufSize];
    if ((fileOrigin = syscall(SYS_open, argv[1], O_RDONLY)) < 0) {
        fprintf(stderr, "file open failed, error = %d\n", errno);
        exit(1);
    }
    while ((readSize = syscall(SYS_read, fileOrigin, buffer, bufSize)) > 0) {
        if (syscall(SYS_write, 1, buffer, readSize) < 0) {  // Use 1 for stdout
            fprintf(stderr, "write to stdout failed, error = %d\n", errno);
            exit(1);
        }
    }
    close(fileOrigin);
    return 0;
}


// 2. PWD (Present Working Directory)
char* pwd() {
    static char currentWD[FILENAME_MAX];
    if (getcwd(currentWD, FILENAME_MAX) == NULL) {
        perror("pwd ERROR");
        exit(EXIT_FAILURE);
    }
    return currentWD;
}

// 3. LS (List Files)
void ls(const char *path) {
    DIR *direcStream = opendir(path);
    if (direcStream == NULL) {
        perror("opendir ERROR");
        exit(EXIT_FAILURE);
    }
    printf("The files in the directory are: '%s':\n", path);

    struct dirent *curDir;
    while ((curDir = readdir(direcStream))) {
        printf("%s\n", curDir->d_name);
    }
    closedir(direcStream);
}

int main() {
    printf("Welcome to my interactive terminal\n");
    printf("Please pick an option\n");
    printf("1. CAT\n");
    printf("2. PWD\n");
    printf("3. LS\n");
    int option;
    scanf("%d", &option);
    while (option){
        if(option==1){
            printf("Do you want to see the contents of this current file or other? \n");
            printf("1. CURRENT FILE \n");
            printf("2. OTHER FILE \n");
            int optCat;
            scanf("%d",&optCat);
            if (optCat == 1){
                cat(2, (const char *[]){"./program", "terminal.c"});
                break;
            }
            else if (optCat == 2){
                printf("Enter the file name you want to display: \n");
                char fileName[99];
                scanf("%99s", fileName);
                cat(2, (const char *[]){"./program", fileName});
                break;
            }
        }
        else if(option==2){
            printf("Current working directory: %s\n", pwd());
            break;
        }
        else if(option==3){
            printf("Would you like to list the working directory or any other directory?\n");
            printf("1 = WORKING DIRECTORY \n");
            printf("2 = OTHER DIRECTORY \n");
            int optDir;
            scanf("%d",&optDir);
            if (optDir == 1){
                ls(".");
                break;
            }
            else if (optDir == 2){
                printf("Please provide the path in /path/to/directory form \n");
                char dir[100]; 
                scanf("%99s", dir);
                ls(dir);
                break;
                }
            
        }
        else if(option != 1 || option != 2 || option != 3){
            printf("Not a valid option.\n");
            break;
        }
    }

    return 0;
}
