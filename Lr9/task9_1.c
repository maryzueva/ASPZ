#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>

int main() {
FILE *fp = popen("getent passwd", "r");
if (fp == NULL){
perror("popen");
return 1;
}

uid_t my_uid = getuid();
struct passwd *me = getpwuid(my_uid);

char line[512];
int found = 0;

printf("Current user: %s, UID: %d\n\n", me ? me->pw_name : "unknown", my_uid);

while (fgets(line, sizeof(line), fp)){
char *username = strtok(line, ":");
strtok(NULL, ":");
char *uid_str = strtok(NULL, ":");

if (username && uid_str){
int uid = atoi(uid_str);

if (uid >= 1000 && uid < 60000 && uid != my_uid){
printf("Found another regular user: %s, UID: %d\n", username, uid);
found = 1;
}
}
}
if (!found){
printf("No other regular users were found.\n");
}
pclose(fp);
return 0;
}
