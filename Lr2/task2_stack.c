#include <stdio.h>
void test_arrays(){
int array1[1000];
int array2[1000] = {1};

array1[10] = 10;

printf("array1[0] = %d\n", array1[0]);
printf("array2[0] = %d\n", array2[0]);

}

int main() {
printf("Hello, world!\n");
test_arrays();
return 0;
}
