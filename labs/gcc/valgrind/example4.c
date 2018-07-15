#include <stdio.h>
#include <stdlib.h>

int main() {
	int *a;
	for (int i = 0; i < 10; i++) {
		a = malloc(100000);
		printf("%p\n", a);
	}
	return 0;
}
