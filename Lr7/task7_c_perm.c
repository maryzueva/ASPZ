#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main(void){
DIR *dir = opendir(".");
if (dir == NULL){
perror("opendir");
return 1;
}

struct dirent *entry;
struct stat st;
char answer;

while ((entry = readdir(dir)) != NULL){
int len = strlen(entry->d_name);

if(len > 2 && strcmp(entry->d_name + len - 2, ".c") == 0){
if(stat(entry->d_name, &st) == -1){
continue;
}
printf("File: %s\n", entry->d_name);
printf("Give others read permission? (y/n): ");
scanf(" %c", &answer);

if (answer == 'y' || answer == 'Y'){
if (chmod(entry->d_name, st.st_mode | S_IROTH) == -1){
perror("chmod");
}
else{
printf("Permission updated for %s\n", entry->d_name);
}
}
}
}
closedir(dir);
return 0;
}
