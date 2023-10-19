#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>



int main(){

    char ls[]="ls";
    char date[]="date";
    char pwd[]="pwd";

    pid_t pid;

    printf("Buenas tardes para acceder a las opciones siguentes, porfavor escribe la opcion que desee \n");
    
    while (1) {
      printf("ls, date, pwd \n");
      char opciones[6] ;
      scanf("%s",opciones); 
      if (strcmp(opciones, ls) == 0) {
	      pid = fork();
	      if(pid<0){
          fprintf(stderr, "Fork failed");
	      }

        else if (pid==0){
          execlp("/bin/ls", "ls", NULL);
          
        }
        else{
          wait(NULL);
        }
      }
   
      else if (strcmp(opciones, date) == 0)
      {
        pid = fork();
	      if(pid<0){
          fprintf(stderr, "Fork failed");
	      }

        else if (pid==0){
          execlp("/bin/date","date",NULL);
        }
        else{
          wait(NULL);
        }
      }

      

      else if (strcmp(opciones, pwd) == 0)
  
      {
        pid = fork();
	      if(pid<0){
          fprintf(stderr, "Fork failed");
	      }

        else if (pid==0){
          execlp("/bin/pwd","pwd",NULL);
        }
        else{
          wait(NULL);
        }

        

      }

      else if (strcmp(opciones, "exit") == 0)
      {
        break;
      }
      else{
        printf("Error introdusca de manera correcta lo que desee. \n");
        pid = fork();
	      if(pid<0){
          fprintf(stderr, "Fork failed");
	      }
        
    
      };
      
    
}
return 0;
}
