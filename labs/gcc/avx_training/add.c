/*
 * =====================================================================================
 *
 *       Filename:  add.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2018 05:28:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Victor Rodriguez (), vm.rod25@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "add.h"

int a[256] = {0}; 
int b[256] = {0};
int c[256] = {0};

void foo(){
        for (int i=0; i<256; i++){
            a[i] = b[i] + c[i];
        }
}


int main(){

    clock_t t;
    double avg_time_taken;
    double time_taken;

    for (int i=0; i<256; i++){
        b[i] = 1;
        c[i] = 2;

    }

    t = clock();
    for (int x=0; x<MAX; x++){
        foo();
    }
    t = clock() - t;
    avg_time_taken = ((double)t)/CLOCKS_PER_SEC/MAX;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    for (int i=0; i<256; i++){
        if (a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            return -1;
    }
    
    printf("Loops: %d\n",MAX);
    printf("Total time: %.9g seconds to execute \n",time_taken);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken);
    return 0;
}
