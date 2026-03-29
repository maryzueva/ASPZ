#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _GNU_SOURCE

double now_sec() {
struct timespec ts;
clock_gettime(CLOCK_MONOTONIC, &ts);
return ts.tv_sec + ts.tv_nsec / 1e9;
}

void touch_memory (char *p, size_t size){
size_t page = 4096;
volatile unsigned long sum = 0;

for (size_t i = 0; i < size; i += page){
sum += p[i];
}
if (sum == 123456789){
printf("sum = %lu\n", sum);
}
}

int main() {
size_t size = 256UL * 1024 * 1024;

double t1, t2, t3, t4;
char *p1, *p2;

printf("Block size: %zu bytes (256 MB)\n", size);

t1 = now_sec();
p1 = calloc(1, size);
t2 = now_sec();

if(!p1){
perror("calloc");
return 1;
}
touch_memory(p1, size);

t3 = now_sec();
free(p1);
t4 = now_sec();

printf("calloc alloc time: %.6f sec\n", t2-t1);
printf("calloc free time: %.6f sec\n", t4-t3);

// malloc + memset
t1 = now_sec();
p2 = malloc(size);
if(!p2){
perror("malloc");
return 1;
}
memset(p2, 0, size);
t2 = now_sec();

touch_memory(p2, size);

t3 = now_sec();
free(p2);
t4 = now_sec();

printf("malloc+memset alloc time: %.6f sec\n", t2-t1);
printf("malloc+memset free time: %.6f sec\n", t4-t3);

return 0;
}
