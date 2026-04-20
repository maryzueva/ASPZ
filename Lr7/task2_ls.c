#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void print_p (mode_t mode){
printf((mode & S_IRUSR) ? "r" : "-");
printf((mode & S_IWUSR) ? "w" : "-");
printf((mode & S_IXUSR) ? "x" : "-");
printf((mode & S_IRGRP) ? "r" : "-");
printf((mode & S_IWGRP) ? "w" : "-");
printf((mode & S_IXGRP) ? "x" : "-");
printf((mode & S_IROTH) ? "r" : "-");
printf((mode & S_IWOTH) ? "w" : "-");
printf((mode & S_IXOTH) ? "x" : "-");
}

int main(void){

DIR *dir;
struct dirent *entry;
struct stat st;

dir = opendir(".");
if (dir == NULL){
perror("opendir");
return 1;
}

while ((entry = readdir(dir)) != NULL){
if (stat(entry->d_name, &st) == -1){
perror("stat");
continue;
}
print_p(st.st_mode);
printf(" %s\n", entry->d_name);
}
closedir(dir);
return 0;
}
