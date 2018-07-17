all:
	gcc example.c -o example
	gcc example1.c -o example1
	gcc example2.c -o example2
	gcc example3.c -o example3
	gcc example4.c -o example4
	gcc memcheck_example.c -o memcheck_example

check:

	valgrind --leak-check=full ./example
	valgrind --leak-check=full ./example1
	valgrind --leak-check=full ./example2
	valgrind --leak-check=full ./example3
	valgrind --leak-check=full ./example4
	valgrind --leak-check=full ./memcheck_example


clean:
	@find . -type f -executable -exec sh -c "file -i '{}' | grep -q 'x-executable; charset=binary'" \; -print | xargs rm -f

