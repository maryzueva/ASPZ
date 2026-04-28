#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_access(const char *filename){
printf("\nChecking access to %s:\n", filename);

if (access(filename, R_OK) == 0){
printf("Read access is allowed\n");
}
else{
printf("Read access is denied\n");
}
if (access(filename, W_OK) == 0){
printf("Write access is allowed\n");
}
else{
printf("Write access is denied\n");
}
}

int main() {
FILE *f = fopen("temp_access.txt", "w");
if (f == NULL){
perror("fopen");
return 1;
}

fprintf(f, "Temporary file for checking permissions.\n");
fclose(f);

printf("The file was created by a regular user.\n");
system("ls -l temp_access.txt");

printf("\nChanging owner tto root and permissions to 600:\n");
system("sudo chown root:root temp_access.txt");
system("sudo chmod 600 temp_access.txt");
system("ls -l temp_access.txt");

check_access("temp_access.txt");

printf("\nChanging permissions to 666:\n");
system("sudo chmod 666 temp_access.txt");
system("ls -l temp_access.txt");

check_access("temp_access.txt");

system("sudo rm -f temp_access.txt");

return 0;
}
