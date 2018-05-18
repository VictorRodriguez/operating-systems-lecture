# Performance debug/tuning training

This section helps student to understand perf, glibc , strace and other tools
to better understand how to improve the performance of their code. This
tutorial is based on : 

* https://perf.wiki.kernel.org/index.php/Tutorial


## Prerequisites

Student must use GCC and a Linux system , is impossible to make this in a not
Linux system. If possible use a bare metal system, instead of a VM

## Configurations

If you are over ssh be sure to have this in your enviroment:

```
    export COLORTERM=truecolor
```

It will make perf report works with colors (without them is impossible to work)

## Compile

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


## Execute

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

The perf tool supports a list of measurable events. The tool and underlying
kernel interface can measure events coming from different sources. For
instance, some event are pure kernel counters, in this case they are called
software events. Examples include: context-switches, minor-faults.

Another source of events is the processor itself and its Performance Monitoring
Unit (PMU). It provides a list of events to measure micro-architectural events
such as the number of cycles, instructions retired, L1 cache misses and so on.
Those events are called PMU hardware events or hardware events for short. They
vary with each processor type and model.

PMU hardware events are CPU specific and documented by the CPU vendor. The perf
tool, if linked against the libpfm4 library, provides some short description of
the events. For a listing of PMU hardware events for Intel and AMD processors,
see

Intel PMU event tables: Appendix A of manual here:

* [Intel® 64 and IA-32 Architectures Developer's Manual](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3b-part-2-manual.html)


## perf stat

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
With no events specified, perf stat collects the common events listed above.
Some are software events, such as context-switches, others are generic hardware
events such as cycles. After the hash sign, derived metrics may be presented,
such as 'IPC' (instructions per cycle). You can see see perf list for a full
list of supported events, a nice picture that shows what part of the OS is
measuring is:

    * http://www.brendangregg.com/perf_events/perf_events_map.png

By default, events are measured at both user and kernel levels:

```
perf stat -e cycles ./simple-math-bench -i 10000000

```
You can select which ring to read by: 

* event:u -> user
* event:k -> kernel
* event:h -> monitor hypervisor events on a virtualization environment
* event:H -> monitor host machine on a virtualization environment
* event:G -> monitor guest machine on a virtualization environment

Check https://perf.wiki.kernel.org/index.php/Tutorial for more info about this

You can record multiple events by : 

```
perf stat -e cycles,instructions,cache-misses ./simple-math-bench
```

## perf record

The perf tool can be used to collect profiles on per-thread, per-process and
per-cpu basis.

There are several commands associated with sampling: record, report, annotate.
You must first collect the samples using perf record. This generates an output
file called perf.data. That file can then be analyzed, possibly on another
machine, using the perf report and perf annotate commands.

The perf_events interface allows two modes to express the sampling period:

the number of occurrences of the event (period)
the average rate of samples/sec (frequency)
The perf tool defaults to the average rate. It is set to 1000Hz, or 1000 samples/sec.

In order to profile ./simple-math-bench program we can do this basic command
with perf:

```
perf record ./simple-math-bench -i 10000000

```

If some event event has raw counts more than several hundreds or thousands and
target program runs for more than several milliseconds, you may use perf record
-e event (or perf record -e event:u to not profile kernel code). perf record
usually autotune sample rate to around several kHz (for example if your program
has 100 millions of cycles, perf record may select around every 1 mln cycles as
sample generator), and events with too low raw counter value may not generate
any samples. You also may set event count for every sample with -c option of
perf record, in this example we asked perf record to generate sample after
every 10000 cycles spent in userspace code of program; zero samples will be
generated for program which runs for 8469 cycles:

```
perf record -e cycles:u -c 10000 ./pi-serial-ps

```

## perf report

Samples collected by perf record are saved into a binary file called, by
default, perf.data. The perf report command reads this file and generates a
concise execution profile. By default, samples are sorted by functions with the
most samples first. It is possible to customize the sorting order and therefore
to view the data differently.

```
perf report

Samples: 3K of event 'cycles:uppp', Event count (approx.): 2768860737
Overhead  Command          Shared Object      Symbol
  99.99%  simple-math-ben  simple-math-bench  [.] foo
   0.01%  simple-math-ben  ld-2.27.so         [.] _dl_map_object_deps
   0.00%  simple-math-ben  [unknown]          [.] 0xffffffffb2c009a0
```
The column 'Overhead' indicates the percentage of the overall samples collected
in the corresponding function. The second column reports the process from which
the samples were collected. In per-thread/per-process mode, this is always the
name of the monitored command. But in cpu-wide mode, the command can vary. The
third column shows the name of the ELF image where the samples came from. If a
program is dynamically linked, then this may show the name of a shared library.
When the samples come from the kernel, then the pseudo ELF image name
[kernel.kallsyms] is used. The fourth column indicates the privilege level at
which the sample was taken, i.e. when the program was running when it was
interrupted:

* [.] : user level
* [k]: kernel level
* [g]: guest kernel level (virtualization)
* [u]: guest os user space
* [H]: hypervisor

The final column shows the symbol name. (you need to have debug simbols: gcc -g)

As we can see the foo function is the one that consume 99.99 % of the time of
our application, which make sense when we check the source code.

The perf tool does not know how to extract symbols form compressed kernel
images (vmlinuz). Therefore, users must pass the path of the uncompressed
kernel using the -k option:

```
perf report -k /tmp/vmlinux 
```

Of course, this works only if the kernel is
compiled to with debug symbols.

## perf record (debug code)

If we compile with debug flag : -g

```
make debug
```

We can profile the code by going to : 

    * simple-math-ben -> Annotate foo:

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


## perf record call-graph

To get useful call-graphs build the compiler with -fno-omit-frame-pointer

Enable call-graph recording with -g, this enables call-graph (stack
chain/backtrace) recording.

```
perf record -g ./simple-math-bench -i 1000000

```
or

```
perf record -g --call-graph dwarf ./simple-math-bench -i 1000000

```

More info at :
    * https://gcc.gnu.org/wiki/Perf_Callgraph
    * http://man7.org/linux/man-pages/man1/perf-record.1.html

Example:

```
$ perf record -g --call-graph dwarf ./simple-math-bench -i 100000
Running foo
iterations = 10000000000
 math = a[i] = b[i] + c[i]
Time in foo: 0.064133 seconds
[ perf record: Woken up 9 times to write data ]
[ perf record: Captured and wrote 2.103 MB perf.data (261 samples) ]

  Children      Self  Command          Shared Object      Symbol
+   99.17%    99.17%  simple-math-ben  simple-math-bench  [.] foo
+   99.17%     0.00%  simple-math-ben  simple-math-bench  [.] _start
+   99.17%     0.00%  simple-math-ben  libc-2.27.so       [.] __libc_start_main
-   99.17%     0.00%  simple-math-ben  simple-math-bench  [.] main
     main
     foo
+    0.75%     0.75%  simple-math-ben  [unknown]          [.] 0xffffffffaec00180
     0.06%     0.06%  simple-math-ben  ld-2.27.so         [.] _dl_start
     0.06%     0.00%  simple-math-ben  ld-2.27.so         [.] _start
     0.02%     0.02%  simple-math-ben  [unknown]          [.] 0xffffffffaec009e0

```

## profiling sleep times

This feature shows where and how long a program is sleeping or waiting
something.

The first step is collecting data. We need to collect sched_stat and
sched_switch events. Sched_stat events are not enough, because they are
generated in the context of a task, which wakes up a target task (e.g. releases
a lock). We need the same event but with a call-chain of the target task. This
call-chain can be extracted from a previous sched_switch event.

The second step is merging sched_start and sched_switch events. It can be done
with help of "perf inject -s".


```
$ make debug
$ perf record -e sched:sched_stat_sleep -e sched:sched_switch  -e sched:sched_process_exit -g -o ~/perf.data.raw ./sleep_example
$ perf inject -v -s -i ~/perf.data.raw -o ~/perf.data
$ perf report --stdio --show-total-period -i ~/perf.data
```
important take into consideration that you are profiling kernel space calls so
you need to use  proper sudo or root permissions. Also CONFIG_SCHEDSTATS and
CONFIG_SCHED_TRACER  should be enabled to make kernel collect scheduler
statistics.

* https://lwn.net/Articles/510120/

## perf top

The perf tool can operate in a mode similar to the Linux top tool, printing
sampled functions in real time. The default sampling event is cycles and
default order is descending number of samples per symbol, thus perf top shows
the functions where most of the time is spent. By default, perf top operates in
processor-wide mode, monitoring all online CPUs at both user and kernel levels.
It is possible to monitor only a subset of the CPUS using the -C option.

```
Overhead  Shared Object                    Symbol
  31.87%  [kernel]                         [k] ioread32
   3.85%  [kernel]                         [k] flush_tlb_func_common.constprop.3
   1.94%  [kernel]                         [k] format_decode
   1.92%  [kernel]                         [k] vsnprintf
   1.83%  perf                             [.] rb_next
   1.65%  [kernel]                         [k] kallsyms_expand_symbol.constprop.3
   1.34%  [kernel]                         [k] string
   1.19%  [kernel]                         [k] number
   1.06%  perf                             [.] __symbols__insert
   1.00%  libc-2.27.so                     [.] cfree@GLIBC_2.2.5
   0.97%  libc-2.27.so                     [.] _int_malloc
   0.95%  perf                             [.] rb_insert_color
   0.95%  libc-2.27.so                     [.] __strchr_avx2
   0.86%  libc-2.27.so                     [.] _IO_getdelim
   0.72%  [kernel]                         [k] syscall_return_via_sysret
   0.70%  libglib-2.0.so.0.5400.3          [.] g_main_context_check
   0.64%  perf                             [.] hex2u64
   0.57%  [kernel]                         [k] memcpy_erms
   0.56%  libc-2.27.so                     [.] __strlen_avx2

```
By default, the first column shows the aggregated number of samples since the
beginning of the run. By pressing the 'Z' key, this can be changed to print the
number of samples since the last refresh. Recall that the cycle event counts
CPU cycles when the processor is not in halted state, i.e. not idle. Therefore
this is not equivalent to wall clock time. Furthermore, the event is also
subject to frequency scaling.

When we execute at the same time our code:

```
Samples: 8K of event 'cycles:ppp', Event count (approx.): 2047134691
Overhead  Shared Object                    Symbol
  76.22%  simple-math-bench                [.] foo
  10.45%  [kernel]                         [k] ioread32
   0.87%  [kernel]                         [k] flush_tlb_func_common.constprop.3
   0.29%  perf                             [.] hists__calc_col_len
   0.20%  [e1000e]                         [k] e1000_intr_msi
```

It is also possible to drill down into single functions to see which
instructions have the most samples. To drill down into a specify function,
press the 'enter key ' key and enter the name of the function to annotate:

```
Annotate foo
Zoom into simple-math-bench DSO
Browse map details
Exit
```

You can then prese H -> Go to hottest instruction

```
       │                for (i=0; i<256; i++)
       │60:   movl   $0x0,-0x4(%rbp)
       │    ↓ jmp    93
       │                    a[i] = b[i] + c[i];
  0.24 │69:   mov    -0x4(%rbp),%eax
  4.46 │      cltq
 19.06 │      mov    -0x810(%rbp,%rax,4),%edx
 12.03 │      mov    -0x4(%rbp),%eax
  0.09 │      cltq
 16.04 │      mov    -0xc10(%rbp,%rax,4),%eax
 14.98 │      add    %eax,%edx
  6.82 │      mov    -0x4(%rbp),%eax

```

In this case it is the mov with 19% , this make sense when we find out that is
inside the for loop after the addition of the 2 arrays. 

As we can see perf is a rich tool that can help us to track down buttle necks
and improve the performance of our system 
