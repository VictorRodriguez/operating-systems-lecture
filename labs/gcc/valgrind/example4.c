#include <stdio.h>
#include <stdlib.h>

int main() {
	int *a;
    int i;
	for (i = 0; i < 10; i++) {
		a = malloc(100000);
		printf("%ls\n", a);
	}
	return 0;
}
