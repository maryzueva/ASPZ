#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOTAL_LEVELS 3
#define CHILDREN_PER_PROCESS 2

static void create_tree(int level) {
printf("Level %d | PID=%ld | PPID=%ld\n",
level, (long)getpid(), (long)getppid());

if (level >= TOTAL_LEVELS - 1) {
printf("Level %d | PID=%ld finished (leaf)\n",
level, (long)getpid());
return;
}

pid_t children[CHILDREN_PER_PROCESS];

for (int i = 0; i < CHILDREN_PER_PROCESS; i++) {
pid_t pid = fork();

if (pid < 0) {
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0) {
create_tree(level + 1);
exit(EXIT_SUCCESS);
}

children[i] = pid;

printf("Level %d | parent PID=%ld created child %d with PID=%ld\n",
level, (long)getpid(), i + 1, (long)pid);
}

for (int i = 0; i < CHILDREN_PER_PROCESS; i++) {
int status;
pid_t done = waitpid(children[i], &status, 0);

if (done == -1) {
perror("waitpid");
exit(EXIT_FAILURE);
}

if (WIFEXITED(status)) {
printf("Level %d | parent PID=%ld waited child PID=%ld, exit=%d\n",
level,
(long)getpid(),
(long)done,
WEXITSTATUS(status));
}
}

printf("Level %d | PID=%ld finished\n", level, (long)getpid());
}

int main(void) {
setbuf(stdout, NULL);

printf("Process tree: %d levels, each process creates %d children\n",
TOTAL_LEVELS, CHILDREN_PER_PROCESS);

create_tree(0);

return 0;
}
