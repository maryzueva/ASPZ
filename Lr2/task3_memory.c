#include <stdio.h>
#include <stdlib.h>

int global_init = 100;
int global_uninit;

static int static_init = 200;
static int static_uninit;

void fun(){
printf ("This is function example\n");
}

int main(){
int local_var = 10;
int *heap_var = malloc(sizeof(int));

if (heap_var == NULL){
printf ("Memory allocation error\n");
return 1;
}

*heap_var = 300;

printf (" Memory layout\n");

printf ("Adress of main:                  %p\n", (void*)main);
printf ("Adress of function example:      %p\n", (void*)fun);

printf ("Adress of global_init:           %p\n", (void*)&global_init);
printf ("Adress of global_uninit:         %p\n", (void*)&global_uninit);

printf ("Adress of static_init:           %p\n", (void*)&static_init);
printf ("Adress of static_uninit:         %p\n", (void*)&static_uninit);

printf("Adress of local_var:             %p\n", (void*)&local_var);
printf("Adress of heap_var value:        %p\n", (void*)heap_var);
printf("Adress of heap_var pointer:      %p\n", (void*)&heap_var);

free(heap_var);
return 0;
}


