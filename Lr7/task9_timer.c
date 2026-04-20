#include <stdio.h>
#include <time.h>

int main(void){
struct timespec start, end;
long long elapsed_ms;

clock_gettime(CLOCK_MONOTONIC, &start);

volatile long long sum = 0;

for (long long i = 0; i < 100000000; i++){
sum += i;
}
clock_gettime(CLOCK_MONOTONIC, &end);

elapsed_ms = (end.tv_sec - start.tv_sec) * 1000LL +
	     (end.tv_nsec - start.tv_nsec) / 1000000LL;

printf("Execution time: %lld ms\n", elapsed_ms);
return 0;
}
