#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
DIR *dir = opendir(".");
if (!dir){
perror("opendir");
return 1;
}

struct dirent *entry;
struct stat st;
char answer;

while ((entry = readdir(dir)) != NULL){
if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
continue;
}

if(stat(entry->d_name, &st) == -1){
continue;
}

if(S_ISREG(st.st_mode)){
printf("Delete file %s? (y/n): ", entry->d_name);
scanf(" %c", &answer);

if (answer == 'y' || answer == 'Y'){
if (remove(entry->d_name) == 0){
printf("Deleted: %s\n", entry->d_name);
}
else{
perror("remove");
}
}
}
}
closedir(dir);
return 0;
}
