all:
	gcc simple-fork.c -o simple-fork
	gcc simple-shell.c -o simple-shell
	gcc shm-posix-consumer.c -o simple-consumer
	gcc -std=c99 -D_XOPEN_SOURCE=500 shm-posix-producer.c -o simple-producer

clean: 
	rm -rf simple-fork
	rm -rf simple-shell
