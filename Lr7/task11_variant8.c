#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_TASKS 100
#define MAX_CMD 256

typedef struct{

int hour;
int minute;
char command[MAX_CMD];
int done;
} Task;

int load_tasks(const char *filename, Task tasks[]){
FILE *f = fopen(filename, "r");
if (f == NULL){
perror("fopen");
return -1;
}
int count = 0;

while (count < MAX_TASKS &&
	fscanf(f, "%d:%d %[^\n]", &tasks[count].hour, &tasks[count].minute, tasks[count].command) == 3){
tasks[count].done = 0;
count++;
}
fclose(f);
return count;
}

int main(void){
Task tasks[MAX_TASKS];
int count = load_tasks("schedule.txt", tasks);

if (count <= 0){
printf("No tasks loaded.\n");
return 1;
}
printf("Mini cron started. Press Ctrl+C to stop.\n");

int last_day = -1;

while (1) {
time_t now = time(NULL);
struct tm *t = localtime(&now);

printf("Now: %02d:%02d:%02d\n", t->tm_hour, t->tm_min, t->tm_sec);

if(t->tm_mday != last_day){
last_day = t->tm_mday;
for(int i = 0; i < count; i++){
tasks[i].done = 0;
}
}
for (int i = 0; i < count; i++){
if (tasks[i].done == 0 &&
    tasks[i].hour == t->tm_hour &&
    tasks[i].minute == t->tm_min){
printf("Running: %02d:%02d -> %s\n", tasks[i].hour, tasks[i].minute, tasks[i].command);
system(tasks[i].command);
tasks[i].done = 1;
}
}
sleep(5);
}
return 0;
}
