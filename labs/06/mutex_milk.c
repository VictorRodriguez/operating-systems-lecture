/*
*   Cesar Augusto Garcia Perez
*   COW ASCII taken from: http://www.chris.com/ascii/index.php?art=animals/cows
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

/*
*   Defines shell coloring
*/
#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define PURPLE   "\x1b[35m"
#define BWHITE   "\x1b[1;97m"
#define RESET    "\x1b[0m"

pthread_mutex_t mutex;                          /* mutex instance               */
int stock = 10;                                 /* amount of elements in stock  */
int cashier = 4;                                /* number of cashiers to use    */

void sellmilk(intptr_t *t_id){
    intptr_t t_id2 = (intptr_t) t_id;
    stock--;
    printf(PURPLE "Thread %zd SOLD!\n" RESET, t_id2);
}

/*
*   Calls sellmilk(), and activate/desactivate mutex whenever there is someone selling
*/
void *threadfunc(void *i){
    intptr_t t_id = (intptr_t) i;
    printf(">>Inside thread %zd\n", t_id);
    
    LOOP:printf(">>" BWHITE "%zd " RESET "Trying to access!\n", t_id);
    pthread_mutex_lock(&mutex);
    printf(RED "BLOCK BY %zd\n" RESET, t_id);
    if(stock>0){
        sellmilk((intptr_t *)t_id);
        printf(GREEN "UNBLOCK BY %zd\n" RESET, t_id);
        printf("\t\t\t STOCK-> %d\n", stock);
        pthread_mutex_unlock(&mutex);
        goto LOOP;
    }else{
        pthread_mutex_unlock(&mutex);
        printf(GREEN "UNBLOCK BY %zd\n" RESET, t_id);
        pthread_exit(NULL);
    }
}

int main(void){
    pthread_mutex_init(&mutex, NULL);                               /* Initialize mutex with no attr, see more in man pthread_mutex_destoy */
    printf(">>Mutex created at &->%p\n", (void *) &mutex);
    printf("\t\t\t STOCK-> %d\n", stock);
    pthread_t thread[cashier];                                      /* Creates array of cashiers                                            */

    int i;
    
    /*
    *   Create the threads up to cashier
    */
    for(i = 0; i < cashier; i++){
        pthread_create(&thread[i], NULL, threadfunc, (void *) (intptr_t) (i+1));
    }
    
    /*
    *   Main() waits for threads to be completed
    */
    for(i = 0; i < cashier; i++){
        pthread_join(thread[i], NULL);
    }

    printf("\nCOWS EXHAUSTED\n"
           "NO MORE MILK FOR YOU\n");

    printf("\n"
"            /~~~~~\\        /~~~~~\\ \n"
"           |    (~'        ~~~)   | \n"
"            \\    \\__________/    / \n"
"            /~::::::::         ~\\ \n"
" /~~~~~~~-_| ::::::::             |_-~~~~~~~\\ \n"
"\\ ======= /|  ::A::;      A     :|\\ ====== / \n"
" ~-_____-~ |  _----------------_::| ~-____-~ \n"
"           |/~                  ~\\| \n"
"           /                      \\ \n" 
"          (        ()    ()        ) \n"
"           `\\                   ./' \n"
"             ~-_______________-~     \n"
"                   /~~~~\\           \n"
"                  |      |           \n"
"                  |      |           \n"
"                 (________)          \n"
"                  by jurci              \n");
}
