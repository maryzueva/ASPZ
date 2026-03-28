#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

int main(){
char *buffer = malloc(16);
if (buffer == NULL){
perror("malloc");
return 1;
}
strcpy(buffer, "Hello");
printf("Initial data: %s\n", buffer);

size_t huge_size = SIZE_MAX / 2;

buffer = realloc(buffer, huge_size);

if (buffer == NULL){
printf("reallok failed to allocate memory\n");
printf("The old buffer address is lost, the data is also unavailadle\n");
return 1;
}
printf("New buffer: %s\n", buffer);
free(buffer);
return 0;
}
