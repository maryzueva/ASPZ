#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void test_device(const char *name){
int fd = open(name, O_RDONLY);
if (fd == -1){
perror(name);
return;
}

printf("===Testing %s ===\n", name);

off_t pos1 = lseek(fd, 0, SEEK_CUR);
printf("Initial position: %lld\n", (long long)pos1);

off_t pos2 = lseek(fd, 10, SEEK_SET);
if (pos2 == -1){
perror("lseek SEEK_SET");
close(fd);
return;
}

printf("After lseek(fd, 10, SEEK_SET): %lld\n", (long long)pos2);

off_t pos3 = lseek(fd, 5, SEEK_CUR);
if (pos3 == -1){
perror("lseek SEEK_CUR");
close(fd);
return;
}

printf("After lseek(fd, 5, SEEK_CUR): %lld\n", (long long)pos3);

unsigned char buf[8];
memset(buf, 0xAA, sizeof(buf));

ssize_t r = read(fd, buf, sizeof(buf));
printf("read() returned: %zd\n", r);

if (r > 0){
printf("Bytes read: ");
for (int i = 0; i < r; i++){
printf("%u ", buf[i]);
}

printf("\n");
}
printf("\n");
close(fd);
}

int main(){

test_device("/dev/null");
test_device("/dev/zero");
return 0;
}
