#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main() {
printf("sizeof(size_t) = %zu bytes\n", sizeof(size_t));
printf("SIZE_MAX = %zu\n", (size_t)SIZE_MAX);

void *p = malloc(SIZE_MAX);
if (p == NULL){
perror("malloc(SIZE_MAX)");
}
else{
printf("malloc succeeded unexpectedly: %p\n", p);
free(p);
}
return 0;
}
