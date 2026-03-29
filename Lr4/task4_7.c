#include <stdio.h>
#include <stdlib.h>

struct sbar {
int x;
double y;
};

int main() {

struct sbar *ptr, *newptr;

ptr = calloc(1000, sizeof(struct sbar));
if (!ptr){
perror("calloc");
return 1;
}

newptr = reallocarray(ptr, 500, sizeof(struct sbar));
if (!newptr){
perror("reallocarray");
free(ptr);
return 1;
}

printf("reallocarray succes: %p\n", newptr);
free(newptr);
return 0;
}

