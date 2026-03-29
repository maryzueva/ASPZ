#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
char *ptr = malloc(16);
if(ptr == NULL){
return 1;
}
for(int i = 0; i < 16; i++){
ptr[i] = 'A';
}

printf("old ptr = %p\n", ptr);

char *tmp = realloc(ptr, (size_t) - 1);

if (!tmp){

printf("realloc failed, old block is still valid\n");
printf("ptr still = %p\n", ptr);
free(ptr);
}
else{
printf("realloc succeeded: %p\n", tmp);
free(tmp);
}
return 0;
}
