#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG "In function %20s; &localvar = %p\n"

static void bar_is_now_closed(void){
int localvar = 5;
printf(MSG, __func__, (void*)&localvar);
printf("\nNow blocking on pause()...\n");
pause();
}

static void bar(void){
int localvar = 5;
printf(MSG, __func__, (void*)&localvar);
bar_is_now_closed();
}

static void foo(void){
int localvar = 5;
printf(MSG, __func__, (void*)&localvar);
bar();
}

int main(void){
int localvar = 5;
printf("PID = %d\n", getpid());
printf(MSG, __func__, (void*)&localvar);
foo();
exit(EXIT_SUCCESS);
}


