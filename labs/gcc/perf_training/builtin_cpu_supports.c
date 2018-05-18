#include <stdio.h>
#include <immintrin.h>

int main(){

    if (__builtin_cpu_supports ("avx512f")){
       printf("AVX 512 F instructions suuported\n");
    } else if (__builtin_cpu_supports ("avx2")){
        printf("AVX2 instructions suuported\n");
    } else if (__builtin_cpu_supports ("ssse3")){
        printf("SSE instructions suuported\n");
    } else{
        printf("I have no idea :( !!!\n");
    }

    return 0;
}
