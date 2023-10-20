#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int opcion;
    int pid;

    do {

        printf("Menú:\n");
        printf("1. Opción 1\n");
        printf("2. Opción 2\n");
        printf("3. Opción 3\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");


        scanf("%d", &opcion);


        switch (opcion) {
            case 1:
                pid = fork();
                if (pid == 0) {

                    execlp("/bin/ls","ls",NULL);
                } else if (pid > 0) {

                    wait(NULL);
                } else {
                    printf("Error al crear el proceso hijo.\n");
                }
                break;
            case 2:
                pid = fork();
                if (pid == 0) {

                    execlp("/bin/pwd","pwd",NULL);
                } else if (pid > 0) {

                    wait(NULL);
                } else {
                    printf("Error al crear el proceso hijo.\n");
                }
                break;
            case 3:
                pid = fork();
                if (pid == 0) {

                    execlp("/bin/date","date",NULL);
                } else if (pid > 0) {

                    wait(NULL);
                } else {
                    printf("Error al crear el proceso hijo.\n");
                }
                break;
            case 4:
                printf("Saliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("Opción no válida. Por favor, selecciona una opción válida.\n");
        }

    } while (opcion != 4);

   return 0;
}
            
