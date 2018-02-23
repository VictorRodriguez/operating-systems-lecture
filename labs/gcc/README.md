# Power and performance training

This section helps student to understand perf, glibc , strace and other tools
to better understand how to improve the performance of their code


### Prerequisites

Student must use GCC and a Linux system , is impossible to make this in a not
Linux system. If possible use a bare metal system, instead of a VM

### Compile

A step by step series of examples that tell you have to get a development env running

* default:

Taking all default CFLAGS from system

```
make
```

* debug:

Remove all optimization flags and add -g for glibc debug

```
make debug
```

* SIMD: 

We can build for SSE/AVX/AVX2 flags and compare perforamnce 

```
make sse
make avx
make avx2
```


### Execute

```
./simple-math-bench -i 10000000

Running foo
iterations = 100000000000000
 math = a[i] = b[i] + c[i]
Time in foo: 1.049781 seconds
```


### perf: Linux profiling with performance counters

Performance counters for Linux are a new kernel-based subsystem that provide a
framework for all things performance analysis. It covers hardware level
(CPU/PMU, Performance Monitoring Unit) features and software features (software
counters, tracepoints) as well.

So, let’s imagine you want to know exactly how many CPU instructions happen
when you run ls. It turns out that your CPU stores information about this kind
of thing! And perf can tell you. Here’s what the answer looks like, from perf
stat.

```
perf stat ls

Makefile  perf.data  perf.data.old  README.md  sanity.c  simple-math-bench  simple-math-bench.c

 Performance counter stats for 'ls':

          0.700573      task-clock:u (msec)       #    0.291 CPUs utilized
                 0      context-switches:u        #    0.000 K/sec
                 0      cpu-migrations:u          #    0.000 K/sec
               105      page-faults:u             #    0.150 M/sec
           778,087      cycles:u                  #    1.111 GHz
           829,960      instructions:u            #    1.07  insn per cycle
           163,886      branches:u                #  233.931 M/sec
             9,991      branch-misses:u           #    6.10% of all branches

       0.002403853 seconds time elapsed

```

Consider now the example we have: 

```
$ perf stat ./simple-math-bench -i 10000000
Running foo
iterations = 100000000000000
 math = a[i] = b[i] + c[i]
Time in foo: 0.958425 seconds

 Performance counter stats for './simple-math-bench -i 10000000':

        959.747325      task-clock:u (msec)       #    1.000 CPUs utilized
                 0      context-switches:u        #    0.000 K/sec
                 0      cpu-migrations:u          #    0.000 K/sec
                52      page-faults:u             #    0.054 K/sec
     2,770,126,481      cycles:u                  #    2.886 GHz
     5,190,181,333      instructions:u            #    1.87  insn per cycle
     2,580,040,652      branches:u                # 2688.250 M/sec
        10,003,992      branch-misses:u           #    0.39% of all branches

       0.960023734 seconds time elapsed

```

This is super neat information, and there’s a lot more (see perf list).

In order to profile ./simple-math-bench program we can do this with perf:

```
perf record ./simple-math-bench -i 10000000

perf report

Samples: 3K of event 'cycles:uppp', Event count (approx.): 2768860737
Overhead  Command          Shared Object      Symbol
  99.99%  simple-math-ben  simple-math-bench  [.] foo
   0.01%  simple-math-ben  ld-2.27.so         [.] _dl_map_object_deps
   0.00%  simple-math-ben  [unknown]          [.] 0xffffffffb2c009a0
```

As we can see the foo function is the one that consume 99.99 % of the time of
our application, which make sense when we check the source code.

If we compile with debug flag : -g 

```
make debug
```

simple-math-ben -> Annotate foo: 

We can see the exact code in simple-math-bench.c that is spending most of the %
of the CPU usage: 

```
Percent│      mov    -0xc18(%rbp),%rax
       │      imul   -0xc18(%rbp),%rax
       │      mov    %rax,%rsi
       │      mov    $0x4008c4,%edi
       │      mov    $0x0,%eax
       │    → callq  printf@plt
       │        printf(" math = a[i] = b[i] + c[i]\n");
       │      mov    $0x4008d7,%edi
       │    → callq  puts@plt
       │        for (j=0;j<iter;j++)
       │      movl   $0x0,-0x8(%rbp)
       │    ↓ jmp    b2
       │            for (j=0;j<iter;j++)
       │57:   movl   $0x0,-0x8(%rbp)
       │    ↓ jmp    a0
       │                for (i=0; i<256; i++)
       │60:   movl   $0x0,-0x4(%rbp)
       │    ↓ jmp    93
       │                    a[i] = b[i] + c[i];
  0.36 │69:   mov    -0x4(%rbp),%eax
  4.54 │      cltq
 19.04 │      mov    -0x810(%rbp,%rax,4),%edx
 11.30 │      mov    -0x4(%rbp),%eax
  0.08 │      cltq
 16.43 │      mov    -0xc10(%rbp,%rax,4),%eax
 14.93 │      add    %eax,%edx
  6.95 │      mov    -0x4(%rbp),%eax
  0.16 │      cltq
  0.59 │      mov    %edx,-0x410(%rbp,%rax,4)
       │                for (i=0; i<256; i++)
  6.99 │      addl   $0x1,-0x4(%rbp)
  0.67 │93:   cmpl   $0xff,-0x4(%rbp)
 17.81 │    ↑ jle    69

```

we can see that the add instruction is consuming %14 of the function time,
which make sense due to the logic of the code.
