all:
	gcc simple-math-bench.c -o simple-math-bench
debug:
	gcc -g -O0 simple-math-bench.c -o simple-math-bench
sse:
	gcc -O3 simple-math-bench.c -o simple-math-bench
avx:
	gcc -O3 -mavx simple-math-bench.c -o simple-math-bench
avx2:
	gcc -O3 -mavx2 simple-math-bench.c -o simple-math-bench
clean:
	rm -rf simple-math-bench
	rm -rf perf*
