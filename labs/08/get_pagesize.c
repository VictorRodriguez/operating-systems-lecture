#include <unistd.h>
#include <stdio.h>

int main(){
	long sz = sysconf(_SC_PAGESIZE);
	printf("Page size %ld\n",sz);
	return 0;
}
