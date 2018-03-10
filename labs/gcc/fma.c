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

  for(int i=0; i<8; i++) {
    d[i] = a[i] * b[i];
    d[i] = d[i] + c[i];
  }
}


int main ( int argc, char *argv[] ){

    float a[8] = {1,1,1,1,1,1,1,1};
    float b[8] = {2,2,2,2,2,2,2,2};
    float c[8] = {3,3,3,3,3,3,3,3};
    float d[8];
   
    for (int j=0;j < 0xFFFFFFF;j++){
        multiply_and_add(a,b,c,d);
    }

    for (int i=0; i< sizeof(d)/sizeof(float) ; i++){
        printf("%f\n",d[i]);
    }
    return EXIT_SUCCESS;
}
