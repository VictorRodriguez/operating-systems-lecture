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
#include <sys/time.h>
#include <immintrin.h>

#define MAX 100000000

int a[256] = {0}; 
int b[256] = {0};
int c[256] = {0};

void foo(){
        for (int i=0; i<256; i++){
            a[i] = b[i] + c[i];
        }
}


int main(){

    for (int i=0; i<256; i++){
        b[i] = 1;
        c[i] = 2;

    }

    for (int x=0; x<MAX; x++){
        foo();
    }

    for (int i=0; i<256; i++){
        if (a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            return -1;
    }

    return 0;
}
