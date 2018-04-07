#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void help_function(char *bin_name){

    printf ( "%s <number of blocks>\n",bin_name);
    printf ( "each block is = 1kb\n" );
}

int main( int argc, char *argv[] ) {
    char *str,*p;
    unsigned int secs = 30;
    unsigned int timer;
    int block = 100;
   
    if( argc == 2 ) {
        if (strcmp("-h", argv[1]) == 0){
            help_function(argv[0]);
            return 0;
        }else{
        block = strtol(argv[1], &p, 10);
        }
    }
    
    printf("PID = %d\n",getpid());
    
    for(int i = 0 ; i < block; i++){
        str = (char *) malloc(1024);
    }
    
    strcpy(str, "simple_test");
    
    printf("Reserving %d Kb of memory\n", block);
    printf("Value of String = %s\n", str);
    printf("Address = %u\n", str);
    
    timer = time(0) + secs;
    
    printf("Waiting for %d seconds\n", secs);
    while (time(0) < timer);
        
    free(str);
    return(0);
}
