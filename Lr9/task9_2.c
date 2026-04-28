#include <stdio.h>
#include <stdlib.h>

int main() {
printf("Trying to read /etc/shadow as administrator: \n\n");

system("sudo cat /etc/shadow | head -n 5");

return 0;
}
