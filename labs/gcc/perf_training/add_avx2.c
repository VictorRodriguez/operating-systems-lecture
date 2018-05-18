/*
 * =====================================================================================
 *
 *       Filename:  sort.c
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

float a[256] = {0}; 
float b[256] = {0};
float c[256] = {0};

void foo(){
    __m256 result,B,C;
    for (int x=0; x<MAX; x++){
        for (int i=0; i<256; i+=8){
            B =  _mm256_load_ps(&b[i]);
            C =  _mm256_load_ps(&c[i]);
            result = _mm256_add_ps(B,C);
            for ( int j=0;j<8;j++){
                a[j] = result[j];
            }
        }
    }
    printf ( "%f\n",a[0] );
}


int main(){

    for (int i=0; i<256; i++){
        b[i] = 1.0;
        c[i] = 2.0;

    }
    foo();
    return 0;
}
