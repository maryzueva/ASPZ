#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main() {
FILE *f;

f = fopen("user_file.txt", "w");
if (f == NULL){
perror("fopen");
return 1;
}

fprintf(f, "File created by a regular user.\n");
fclose(f);

printf("File user_file.txt was created.\n");

system("sudo cp user_file.txt root_copy.txt");
system("sudo chown root:root root_copy.txt");
system("sudo chmod 644 root_copy.txt");

printf("\nPermissions after copying:\n");
system("ls -l user_file.txt root_copy.txt");

printf("\nTrying to modify root_copy.txt:\n");

f = fopen("root_copy.txt", "a");
if (f == NULL){
printf("Failed to modify the file: %s\n", strerror(errno));
}
else{
fprintf(f, "New line from a regular user.\n");
fclose(f);
printf("The file was modified successfully.\n");
}
printf("\nTrying to delete root_copy.txt:\n");

if (remove("root_copy.txt") == 0){
printf("The file was deleted successfully.\n");
}
else{
printf("Failed to delete the file: %s\n", strerror(errno));
}
return 0;
}
