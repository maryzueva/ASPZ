#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void list_files (const char *path){
DIR *dir = opendir(path);
if (!dir) return;

struct dirent *entry;
char fullpath[1024];
struct stat st;

while ((entry = readdir(dir)) != NULL) {
if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
continue;
}
snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
if (stat(fullpath, &st) == -1){
continue;
}
printf("%s\n", fullpath);

if (S_ISDIR(st.st_mode)){
list_files(fullpath);
}
}
closedir(dir);
}
int main(void){
list_files(".");
return 0;
}
