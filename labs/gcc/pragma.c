#include <stdio.h>
#include <emmintrin.h>
#include <smmintrin.h>

// Example taken from:
// https://gcc.gnu.org/wiki/FunctionSpecificOpt
// READ:
// http://www.info.univ-angers.fr/~richer/ens/l3info/ao/intel_sse4.pdf
// https://software.intel.com/en-us/cpp-compiler-18.0-developer-guide-and-reference-mm256-mpsadbw-epu8
// https://software.intel.com/en-us/articles/motion-estimation-with-intel-streaming-simd-extensions-4-intel-sse4


__attribute__ ((target ("sse4.1")))
int sse4_1_min (__m128i a, __m128i b) {
    return _mm_cvtsi128_si32(_mm_min_epi32 (a,b));
}

int main(){
    printf("min = %d",sse4_1_min(10,4));
    return 0;
}
