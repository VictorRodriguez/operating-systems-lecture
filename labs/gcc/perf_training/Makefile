all:
	gcc simple-math-bench.c -o simple-math-bench
	gcc builtin_cpu_supports.c -o builtin_cpu_supports
	gcc add.c -o add
	gcc -O3 add_avx2.c -o add_avx2 -march=haswell
	gcc -O3 add_aligned.c -o add_aligned -march=haswell
debug:
	gcc -g -O0 simple-math-bench.c -o simple-math-bench
	gcc -O0 -g sleep_example.c -o sleep_example
sse:
	gcc -O3 simple-math-bench.c -o simple-math-bench
avx:
	gcc -O3 -mavx simple-math-bench.c -o simple-math-bench
avx2:
	gcc -O3 -mavx2 simple-math-bench.c -o simple-math-bench
fma:
	gcc fma.c -o fma
	gcc -march=haswell fma_optimized.c -o fma_optimized
clean:
	rm -rf perf*
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
