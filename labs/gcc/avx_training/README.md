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
## BUILD INSTRUCTIONS

```
$ make

```

## RUN

For the addition code using compiler flags we can specify the delay in micro seconds:

```
$ ./add -h
-h : Help
-d <delay> : Delay in useconds

$ ./add -d 100
Loops: 1000000
Delay per function: 0.0001 in seconds
Total time: 2.29071 seconds to execute
foo() took 2.29071e-06 seconds in avg to execute

or 

$ ./add-march-haswell -d 100

or 

$ ./add_intrinsic-avx2 -d 100

```
The number of loops is in add.h


For more examples please refer this good tutorial:
https://www.codeproject.com/Articles/874396/Crunching-Numbers-with-AVX-and-AVX

And Intel® 64 and IA-32 Architectures Software Developer’s Manual

