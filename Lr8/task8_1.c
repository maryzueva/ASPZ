#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {
int pipefd[2];
if (pipe(pipefd) == -1){
perror("pipe");
return 1;
}

int flags = fcntl(pipefd[1], F_GETFL);
if (flags == -1) {
perror("fcntl get");
return 1;
}

if (fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK) == -1){
perror("fcntl set");
return 1;
}

int pipe_size = fcntl(pipefd[1], F_GETPIPE_SZ);
if(pipe_size == -1){
perror("F_GETPIPE_SZ");
return 1;
}

printf("Pipe size: %d bytes\n", pipe_size);

int first_size = pipe_size - 1000;
char *first = malloc(first_size);
memset(first, 'A', first_size);

ssize_t count1 = write(pipefd[1], first, first_size);
printf("First write: requested = %d, written = %zd\n", first_size, count1);

int second_size = 5000;
char *second = malloc(second_size);
memset(second, 'B', second_size);

ssize_t count2 = write(pipefd[1], second, second_size);
printf("Second write: requested = %d, written = %zd\n", second_size, count2);

if (count2 >= 0 && count2 != second_size){
printf("Partial write happened.\n");
}
else if(count2 == -1){
perror("second write");
}
free(first);
free(second);
close(pipefd[0]);
close(pipefd[1]);
return 0;
}
