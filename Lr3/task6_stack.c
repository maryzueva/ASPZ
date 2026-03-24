#include <stdio.h>
void recurse (int n){
char buffer[1024];
printf("Recursion depth: %d\n", n);
buffer[0] = n % 256;
recurse(n+1);
}
int main(){
recurse(1);
return 0;
}
