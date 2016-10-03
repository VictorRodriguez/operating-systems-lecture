all:
	gcc -lpthread  race_condition_semaphores.c -o race_condition_semaphores
	gcc -lpthread  race_condition.c -o race_condition
	gcc -lpthread  peterson.c -o peterson
	
	g++ -DUSE_SPINLOCK -Wall -pthread spin_lock.c -o spin_lock
	gcc client.c -o client -pthread
	gcc server.c -o server -pthread

clean:
	rm -rf race_condition
	rm -rf race_condition_semaphores
	rm -rf peterson
	rm -rf spin_lock
