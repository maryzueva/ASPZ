#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
int n = -100;
void *p1 = malloc(n);

if (!p1){
printf("malloc(-100) returned NULL\n");
}
else{
printf("malloc(-100) returned %p\n", p1);
free(p1);
}
int xa = 50000;
int xb = 50000;
int num = xa * xb;

printf("xa = %d, xb = %d, num = %d\n", xa, xb, num);

void *p2 = malloc(num);

if(!p2) {
printf("malloc(num) returned NULL\n");
}
else{
printf("malloc(num) returned %p\n", p2);
free(p2);
}
return 0;
}
