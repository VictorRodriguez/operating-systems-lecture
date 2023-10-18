#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
while(1){
    pid_t pid;
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

        char UserInput[256]; // Input que dará el usuario en CLI
        char *Args[11]; // Lista para guardar los argumentos del comando del usuario

        printf("OSH $ ");
        scanf("%[^\n]%*c", UserInput);

        char *tok = strtok(UserInput, " ");
        int count = 0; //Conteo de los argumentos
        while (tok !=NULL){
            Args[count] = tok;
            tok = strtok(NULL, " ");
            count++;
        }
        Args[count] = NULL;

        if(strcmp(Args[0], "salir") == 0){ //Compara el string Args[0] con el string "salir" 
            return 0; //Si son iguales, sale de la terminal, salir es mi argumento de salida
        }

        pid = fork();

        if(pid == 0){
            execvp(Args[0], Args); //Ejecuta el comando proporcionado por el usuario
        }
        else{
            wait(NULL);
        }

}
    return 0;
}
