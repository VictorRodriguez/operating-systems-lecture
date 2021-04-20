all:
	gcc -lpthread  race_condition_semaphores.c -o race_condition_semaphores
	gcc -lpthread  race_condition.c -o race_condition
	gcc -lpthread  peterson.c -o peterson
	gcc -lpthread philosopher.c -o philosopher
	g++ -DUSE_SPINLOCK -Wall -pthread spin_mutex.c -o spin_mutex
	gcc client.c -o client -pthread
	gcc server.c -o server -pthread

clean:
	rm -rf race_condition
	rm -rf race_condition_semaphores
	rm -rf peterson
	rm -rf spin_lock
	rm -rf client
	rm -rf philosopher philosopher_simple
