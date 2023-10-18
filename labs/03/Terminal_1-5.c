#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char command[10]; //Se declara los caracteres a agregar al commando

    while (1) {
        printf("Opciones:| ls | date | pwd | exit |"); //Se muestra las opciones
        printf("Introduzca comando: ");
        fgets(command, sizeof(command), stdin); //Lee lo que el usuario a escrito
        command[strlen(command) - 1] = '\0'; //Toma el 'Space' como Null

        if (strcmp(command, "ls") == 0) { //Compara el comando para comprobar si es el comando ls
            int pid = fork(); //Crea una copia exacta, es 0 cuando es el hijo
            if (pid == 0) { //Procesa el hijo
                execlp("/bin/ls", "ls", NULL); //Ejecuta ls
            } else if (pid < 0) { //Por si fork falla
                exit(-1);
            } else { //Esto es para que se bloquee el proceso del padre, hasta que el hijo termine
                wait(NULL);
            }
        } else if (strcmp(command, "date") == 0) { //Compara el comando para comprobar si es el comando date
            int pid = fork(); //Crea una copia exacta, es 0 cuando es el hijo
            if (pid == 0) { //Procesa el hijo
                execlp("/bin/date", "date", NULL); //Ejecuta date
            } else if (pid < 0) { //Por si fork falla
                exit(-1);
            } else { //Esto es para que se bloquee el proceso del padre, hasta que el hijo termine
                wait(NULL);
            }
        } else if (strcmp(command, "pwd") == 0) { //Compara el comando para comprobar si es el comando pwd
            int pid = fork(); //Crea una copia exacta, es 0 cuando es el hijo
            if (pid == 0) { //Procesa el hijo
                execlp("/bin/pwd", "pwd", NULL); //Ejecuta pwd
            } else if (pid < 0) { //Por si fork falla
                exit(-1);
            } else { //Esto es para que se bloquee el proceso del padre, hasta que el hijo termine
                wait(NULL);
            }
        } else if (strcmp(command, "exit") == 0) { //Hace un break si se el usuario coloca exit
            break;
        } else { //En caso de no introducir ningun comando anterior
            printf("Comando no valido...\n");
        }
    }
    return 0;
}
