#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

int fd;
int c = 0;

printf ("Start opening files...\n");

for (int i = 0; i < 1000; i++){

fd = open("/dev/null", O_RDONLY);

if (fd == -1) {
perror("open failed");
printf("Limit reached at iteration %d\n", i);
break;
}
c++;
}
printf("Total opened files: %d\n", c);
return 0;
}
