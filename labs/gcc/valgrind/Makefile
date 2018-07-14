all:
	gcc -Wall -pedantic -g example1.c -o example
	gcc -Wall -pedantic -g example2.c -o example2
clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f

