#include <stdio.h>
int main() {
int x = 0;
int y = (x++ == 0) + (x++ == 1);
printf("x = %d, y = %d\n", x, y);
return 0;
}
