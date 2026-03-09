#include <stdio.h>
#include <string.h>

void vulnerable(char *input){
char buffer[10];

printf("Copying string...\n");

strcpy(buffer, input);
printf("Buffer contains: %s\n", buffer);
}

void safe(char *input){
char buffer[10];

printf("Safe copying...\n");

strncpy(buffer, input, sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';

printf("Buffer contains: %s\n", buffer);
}

int main() {
char short_text[] = "Hello";
char long_text[] = "AAAAAAAAAAAAAA";

printf ("Vulnerable function\n");
vulnerable(short_text);

printf ("Safe function\n");
safe(long_text);

return 0;
}
