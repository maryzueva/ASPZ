#include <stdio.h>
#include <stdlib.h>

int main() {

void *p = malloc(0);

if (p == NULL) {
printf("malloc(0) returned NULL\n");
}
else{
printf("malloc(0) returned non-NULL pointer: %p\n", p);
}
free(p);
printf("free(p) done\n");

return 0;
}
