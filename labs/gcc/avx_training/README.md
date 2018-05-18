# AVX intrinsic training


CPU architectures often gain interesting new instructions as they evolve, but
application developers often find it difficult to take advantage of those
instructions. Reluctance to lose backward-compatibility is one of the main
roadblocks slowing developers from using advancements in newer computing
architectures. This section try to teach how to use the intrinsics of AVX
technology in immintrin.h library. From AVX2  to AVX 512 technology.

The benefits of using the new architecture's technologies are compelling enough
to outweigh integration challenges. Math-heavy code, for example, can be
significantly optimized by turning on the Intel Advanced Vector Extensions
(AVX). The second version of AVX (AVX2), which was introduced in the
4th-generation Intel Core processor family also known as "Haswell", is one
option. The benefits of AVX2 are well-understood in scientific computing
fields. The use of AVX2 in the OpenBLAS library can give a project like the R
language a boost of up to 2x faster execution; it can also yield significant
improvement in Python scientific libraries. These performance improvements are
gained by doubling the number of floating-point operations per second (FLOPS)
using 256-bit integer instructions, floating-point fused multiply-add
instructions, and gather operations. More info and sources at [LWN
article](https://lwn.net/Articles/691932/)

But how to use these instructions in simple math applications? and how do they
look internally? How do they improve the performance ? 

Lets start with a sinmple code: add.c

```C
    for (int x=0; x<MAX; x++){
        for (int i=0; i<256; i++){
            a[i] = b[i] + c[i];
        }
    }
```

This is a good candidate for SIMD optimization. 

Ussing the AVX technology it coudl be translated to : add_avx2.c

```C
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
```
In my case this is the diference for each case : 


```
$ make
-g -O3 -feliminate-unused-debug-types -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=32 -Wformat -Wformat-security -Wl,--copy-dt-needed-entries -m64 -fasynchronous-unwind-tables -Wp,-D_REENTRANT -ftree-loop-distribute-patterns -Wl,-z -Wl,now -Wl,-z -Wl,relro -fno-semantic-interposition -ffat-lto-objects -fno-signed-zeros -fno-trapping-math -fassociative-math -Wl,-sort-common -Wl,--enable-new-dtags
gcc add.c -o add
gcc -O3 -march=haswell add.c -o add-flag-haswell
gcc -O3 -march=haswell add_avx2.c -o add-intrinsic

$ time ./add
result=3

real	0m11.865s
user	0m11.855s
sys	0m0.000s

$ time ./add-flag-haswell
result=3

real	0m7.572s
user	0m7.565s
sys	0m0.001s

$ time ./add-intrinsic
result=3.000000

real	0m0.001s
user	0m0.000s
sys	0m0.001s
```
