all:
	gcc -c simple.c simple_2.c
	ar -cvq libtest.a simple.o simple_2.o
	ar -t libtest.a
	gcc -o program program.c libtest.a
	gcc -o load_example load_example.c -ldl

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf program
