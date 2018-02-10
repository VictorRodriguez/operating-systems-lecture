all:
	gcc simple-thread-timer.c -o simple-thread-timer -lpthread
	gcc simple-thread.c -o simple-thread -lpthread
	gcc simple-thread-benchmark.c -o simple-thread-benchmark -lpthread
	gcc mutex-thread.c -o mutex-thread -lpthread
	gcc thread-benchmark-syscall.c -o thread-benchmark-syscall -lpthread
clean:
	rm -rf simple-thread-timer
	rm -rf simple-thread
	rm -rf simple-thread-benchmark
	rm -rf mutex-thread
	rm -rf thread-benchmark-syscall
