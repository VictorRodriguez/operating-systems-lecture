/*
 * =====================================================================================
 *
 *       Filename:  fma.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/10/2018 02:09:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Victor Rodriguez (), vm.rod25@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>

void multiply_and_add(const float* a, const float* b, const float* c, float* d) {  

  for(int i=0; i<1; i++) {
    d[i] = a[i] * b[i];
    d[i] = d[i] + c[i];
  }
}


int main ( int argc, char *argv[] ){

    float a[1],b[1],c[1],d[1];
    a[0] = 1;
    b[0] = 2;
    c[0] = 3;
    multiply_and_add(a,b,c,d);

    for (int i=0; i< sizeof(d)/sizeof(float) ; i++){
        printf("%f\n",d[i]);
    }
    return EXIT_SUCCESS;
}
