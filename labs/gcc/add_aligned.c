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
#include <immintrin.h>

int main ( int argc, char *argv[] ){

    __m256 a = _mm256_set_ps(1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0);
    __m256 b = _mm256_set_ps(2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0);

    __m256 result;

    for (int j=0;j < 0xFFFFFFF;j++){
        result = _mm256_add_ps(a,b);
    }
    float* f = (float*)&result;
    printf("%f %f %f %f %f %f %f %f\n",
            f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);

    return EXIT_SUCCESS;
}
