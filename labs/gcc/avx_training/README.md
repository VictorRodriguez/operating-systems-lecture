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

Lets start with a sinmple code: 





