all:
	@echo $(CFLAGS)
	gcc add.c -o add
	gcc -O3 -march=haswell add.c -o add-march-haswell
	gcc -O3 -march=skylake-avx512 add.c -o add-march-skylake-avx512
	gcc -O3 -march=icelake-server add.c -o add-march-icelake-server
	gcc -O3 -march=haswell add_intrinsic.c -o add_intrinsic-avx2

clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
