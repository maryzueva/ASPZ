#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
int data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
int buffer[4];

int fd = open("numbers.bin", O_CREAT | O_RDWR | O_TRUNC, 0644);
if (fd == -1){
perror("open");
return 1;
}
if (write(fd, data, sizeof(data)) == -1){
perror("write");
close(fd);
return 1;
}

if (lseek(fd, 3 * sizeof(int), SEEK_SET) == -1){
perror("lseek");
close(fd);
return 1;
}

if (read(fd, buffer, sizeof(buffer)) == -1){
perror("read");
close(fd);
return 1;
}

printf("Buffer after read: ");
for (int i = 0; i < 4; i++){
printf("%d", buffer[i]);
}
printf("\n");

close(fd);
return 0;
}
