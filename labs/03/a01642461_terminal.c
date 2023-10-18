// Autor: Karen Corona Espinoza
// Tarea 1.5 Simple Terminal (fork/exec)

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

// cat 

#define STDOUT 1

typedef int File;

void cat(int argc, char const *argv[]) {
	File fileOrigin;
	ssize_t readSize;
	const int bufSize = 512;
	char buffer[bufSize];
	open(const char* path, int flags);
	if ((fileOrigin = syscall(SYS_open, argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, "file open failed, error = %s\n", errno);
		exit(1);
	}

	while ((readSize = syscall(SYS_read, fileOrigin, &buffer, bufSize)) > 0) {
		if (syscall(SYS_write, STDOUT, &buffer, readSize) < 0) {
			fprintf(stderr, "write to stdout failed, error = %s\n", errno);
			exit(1);
		}
	}

	close(fileOrigin);
}

// ls

void ls(const char *path) {
    DIR *dirStream = opendir(path);
    if (dirStream == NULL) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    printf("Archivos del directorio: '%s':\n", path);

    struct dirEnt *curDir;
    while ((curDir = readdir(dirStream))) {
        printf("%s\n", curDir->d_name);
    }
    closedir(dirStream);
}


// pwd

char* pwd() {
    static char currentWD[FILENAME_MAX];
    if (getcwd(currentWD, FILENAME_MAX) == NULL) {
        perror("ERROR");
        exit(EXIT_FAILURE);
    }
    return currentWD;
}

// main
int main(){
    printf("¿Qué acción quieres realizar?\n " );
    printf("Escribe 1 para 'ls', 2 para 'cat' y 3 para 'pwd' ");

    int numero;
    scanf("%d", &numero);
    if (numero==1){
        ls(pwd());
    }
    else if(numero == 2){
        cat();
    }
    else if(numero == 3){
        pwd();
    }
    else{
        printf("No se reconoce el comando");
    }
    return 0;

}
