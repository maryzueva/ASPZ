#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define MAX 100
#define LEN 256

int main(void){
DIR *dir;
struct dirent *entry;
struct stat st;

char dirs[MAX][LEN];
int count = 0;

dir = opendir(".");
if (dir == NULL){
perror("opendir");
return 1;
}

while((entry = readdir(dir)) != NULL){
if (stat(entry->d_name, &st) == -1){
continue;
}
if(S_ISDIR(st.st_mode) &&
strcmp(entry->d_name, ".") != 0 &&
strcmp(entry->d_name, "..") != 0){

strcpy(dirs[count], entry->d_name);
count++;
}
}
closedir(dir);

for (int i = 0; i < count - 1; i++){
for (int j = i + 1; j < count; j++){
if (strcmp(dirs[i], dirs[j]) > 0){
char temp[LEN];
strcpy(temp, dirs[i]);
strcpy(dirs[i], dirs[j]);
strcpy(dirs[j], temp);
}
}
}

printf("Directories:\n");
for (int i = 0; i < count; i++){
printf("%s\n", dirs[i]);
}
return 0;
}
