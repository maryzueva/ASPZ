#include <stdio.h>

int main() {

int i = 1;
i = i++ + ++i;
printf("i = %d\n", i);
return 0;
}
