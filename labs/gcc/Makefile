all:
	gcc simple-math-bench.c -o simple-math-bench
	gcc builtin_cpu_supports.c -o builtin_cpu_supports
debug:
	gcc -g -O0 simple-math-bench.c -o simple-math-bench
	gcc -O0 -g sleep_example.c -o sleep_example
sse:
	gcc -O3 simple-math-bench.c -o simple-math-bench
avx:
	gcc -O3 -mavx simple-math-bench.c -o simple-math-bench
avx2:
	gcc -O3 -mavx2 simple-math-bench.c -o simple-math-bench
clean:
	rm -rf simple-math-bench
	rm -rf sleep_example
	rm -rf perf*
	rm -rf builtin_cpu_supports
