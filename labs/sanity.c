#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define ARRAY_LEN 30000

static struct timeval tm1;

static inline void start() {
    gettimeofday(&tm1, NULL);
}

static inline void stop() {
    struct timeval tm2;
    gettimeofday(&tm2, NULL);
    unsigned long long t = 1000 * (tm2.tv_sec - tm1.tv_sec) +\
                           (tm2.tv_usec - tm1.tv_usec) / 1000;
    printf("%llu ms\n", t);
}

void bubble_sort (int *a, int n) {
    int i, t, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
    }
}

void sort_array() {
    printf("Bubble sorting array of %d elements\n", ARRAY_LEN);
    int data[ARRAY_LEN], i;
    for(i=0; i<ARRAY_LEN; ++i){
        data[i] = rand();
    }
    bubble_sort(data, ARRAY_LEN);
}

int main(){
    start();
    sort_array();
    stop();
    return 0;
}
