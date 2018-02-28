#include <unistd.h>
#include <stdio.h>

int main ( int argc, char *argv[] ){

    int a=0;
    for (int i = 0 ; i < 10000000 ; i++)
        a = i*i;

    sleep(3);
    printf("%d\n",a);
    return 0;
}
