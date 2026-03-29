#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
char *ptr = NULL;

for (int i = 0; i < 3; i++){
if (!ptr){
ptr = malloc(16);
}
strcpy(ptr, "hello");
printf("iteration %d: %s\n", i, ptr);

free(ptr);
ptr = NULL;
}
return 0;
}
