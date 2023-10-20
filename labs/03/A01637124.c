/*A01637124 Ana Karen Zetter Márquez*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  int opc;
  do{
    printf("¡Hola! :D Te doy la bienvenida.\n");
    printf("¿Que te gustaria hacer?\n");
    printf("Menu: \n");
    printf("\t1. salir\n");
    printf("\t2. date\n");
    printf("\t3. pwd\n");
    printf("\t4. ls\n");
    printf("¿Cual opcion eliges?\n");
    scanf("%d", &opc);
    switch (opc){
      case 1:
        printf("Saliendo...");
        break;

      case 2:

	    pid = fork();                                          //Fork

	    if (pid < 0) {                                         //Detener en caso de error
		    fprintf(stderr, "Error: No se pudo realizar la operacion Fork.");
		    exit (-1) ;
	    }

    	if(pid == 0){                                   	   //Hijo realiza operación date
            execlp("/bin/date","date",NULL);

        }else{                                                 //Padre espera a que termine el hijo
            wait(NULL);
        }
        break;


      case 3:
	    pid = fork();                                          //Fork

	    if (pid < 0) {                                         //Detener en caso de error
		    fprintf(stderr, "Error: No se pudo realizar la operacion Fork.");
		    exit (-1) ;
	    }

	    else if (pid == 0) {                                   //Hijo realiza operación pwd
		    execlp("/bin/pwd","pwd",NULL);
	    }

	    else {                                                 //Padre espera a que termine el hijo
		    wait(NULL);
	    }
        break;

      case 4:
	    pid = fork();                                          //Fork

	    if (pid < 0) {                                         //Detener en caso de error
		    fprintf(stderr, "Error: No se pudo realizar la operacion Fork.");
		    exit (-1) ;
	    }

	    else if (pid == 0) {                                   //Hijo realiza operación ls
		    execlp("/bin/ls","ls",NULL);
	    }

	    else {                                                 //Padre espera a que termine el hijo
		    wait(NULL);
	    }
        break;

      default:
        break;
    }
  } while(opc != 1);

    return 0;
}