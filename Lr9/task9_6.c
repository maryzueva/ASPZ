#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check(const char *file){
printf("\nAccess check for %s:\n", file);
printf("Read: %s\n", access(file, R_OK) == 0 ? "allowed" : "denied");
printf("Write: %s\n", access(file, W_OK) == 0 ? "allowed" : "denied");
printf("Execute: %s\n", access(file, X_OK) == 0 ? "allowed" : "denied");
}

int main() {
printf("Home directory files:\n");
system("ls -l ~ | head");

printf("\n/usr/bin files:\n");
system("ls -l /usr/bin | head");

printf("\n/etc files:\n");
system("ls -l /etc | head");

check("/etc/passwd");
check("/etc/shadow");
check("/bin/ls");

printf("\nReading /etc/passwd:\n");
system("head -n 3 /etc/passwd");

printf("\nReading /etc/shadow without sudo:\n");
system("head -n 3 /etc/shadow");

return 0;
}
