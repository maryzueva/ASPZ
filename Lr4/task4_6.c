#include <stdio.h>
#include <stdlib.h>

int main() {

void *p1 = realloc(NULL, 100);
printf("realloc(NULL, 100) = %p\n", p1);

void *p2 = malloc(100);
printf("realloc(100) = %p\n", p2);

void *p3 = realloc(p1, 0);
printf("realloc(p2, 0) = %p\n", p3);

free(p1);

return 0;
}
