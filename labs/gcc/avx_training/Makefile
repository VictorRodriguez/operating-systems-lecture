all:
	@echo $(CFLAGS)
	gcc add.c -o add
	gcc -O3 -march=haswell add.c -o add-flag-haswell
	gcc -O3 -march=haswell add_avx2.c -o add-intrinsic

clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f
