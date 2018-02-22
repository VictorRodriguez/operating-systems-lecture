#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

void foo(long iter){
    int i,j,k =0;
    int a[256], b[256], c[256];

    printf("Running foo\n");
    printf("iterations = %lu \n",(iter*iter));
    printf(" math = a[i] = b[i] + c[i]\n");
    for (j=0;j<iter;j++)
        for (j=0;j<iter;j++)
            for (i=0; i<256; i++)
                a[i] = b[i] + c[i];
}

int main (int argc , char **argv){

    int c;
    long iter;
    clock_t start, end;
    double cpu_time_used;

    while ((c = getopt(argc,argv,"i:")) != -1 )
        switch (c){
            case 'i':
                iter = atol(optarg);
                break;
            default:
                abort();
        }

    start = clock();
    foo(iter);
    end =clock();

    cpu_time_used = ((double)(end -start))/ CLOCKS_PER_SEC;
    printf ( "Time in foo: %f seconds\n",cpu_time_used );
    return 0;
}

