#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
int pid;

pid = fork();

if (pid < 0){
perror("fork");
return 1;
}
printf("%d\n", pid);

return 0;
}
