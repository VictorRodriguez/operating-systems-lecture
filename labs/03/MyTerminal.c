#include <stdio.h> //Input y output
#include <string.h> //Uso de strings
#include <unistd.h> //Manejo de sistema operativo
#include <sys/wait.h> //Llama a wait del sistema

int main()
{
    char cwd[1024]; //Char que guarda el working directory
    getcwd(cwd, sizeof(cwd)); //Guardamos nuestro working directory

    while(1) //Loop infinito
    {
        char command[256]; //Guardaremos el comando aqui
        char *arguments[256]; //Array de apuntadores a los argumentos del comando
        int argcounter = 0; //contador de argumentos

        printf("Shell Diego Vargas: "); //Mensaje indicando espera de input
        fgets(command, sizeof(command), stdin); //Recibimos el comando del standard input y lo pasamos a command
        command[strlen(command) - 1] = '\0';  //removemos el indicador de salto de linea y lo cambiamos por un null

        char *tok = strtok(command," ");  //Indicamos de donde sacar los tokens

        while(tok != NULL) //Siempre que tok no sea Null
        {
            arguments[argcounter] = tok; //Pasamos el token actual
            argcounter++; //Aumentamos el contador de tokens
            tok = strtok(NULL, " "); //Continuamos sacando tokens
        }
        arguments[argcounter] = NULL; //Indicamos el final del array de string

        if(strcmp(arguments[0], "exit") == 0) //Si se mando el comando exit
        {
            return 0; //Salimos del shell
        }
        
        pid_t id = fork(); //Creador de nuevo proceso

        if(id == 0) //Si el Id del proceso es 0
        {
            execvp(arguments[0], arguments); //Ejecutamos el proceso indicado
        }
        else
        {
            wait(NULL); //Espera a que termine el hijo
        }
    }
    return 0; //Return de final
}
