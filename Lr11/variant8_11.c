#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define ALT_STACK_SIZE (64 * 1024)

static stack_t alt_stack;
static volatile sig_atomic_t stop_program = 0;

void signal_handler(int signo)
{
char local_var;

int on_alt_stack =
((char *)&local_var >= (char *)alt_stack.ss_sp) &&
((char *)&local_var <  (char *)alt_stack.ss_sp + alt_stack.ss_size);

if (signo == SIGINT) {
write(STDOUT_FILENO, "\nReceived SIGINT signal\n",
strlen("\nReceived SIGINT signal\n"));
}
else if (signo == SIGTERM) {
write(STDOUT_FILENO, "\nReceived SIGTERM signal\n",
strlen("\nReceived SIGTERM signal\n"));
}

if (on_alt_stack) {
write(STDOUT_FILENO,
"Signal handler is running on the alternative stack: YES\n",
strlen("Signal handler is running on the alternative stack: YES\n"));
}
else {
write(STDOUT_FILENO,
"Signal handler is running on the alternative stack: NO\n",
strlen("Signal handler is running on the alternative stack: NO\n"));
}

stop_program = 1;
}

int main(void)
{
struct sigaction sa;

alt_stack.ss_sp = malloc(ALT_STACK_SIZE);
if (alt_stack.ss_sp == NULL) {
perror("malloc");
return 1;
}

alt_stack.ss_size = ALT_STACK_SIZE;
alt_stack.ss_flags = 0;

if (sigaltstack(&alt_stack, NULL) == -1) {
perror("sigaltstack");
free(alt_stack.ss_sp);
return 1;
}

memset(&sa, 0, sizeof(sa));
sa.sa_handler = signal_handler;
sigemptyset(&sa.sa_mask);
sa.sa_flags = SA_ONSTACK;

if (sigaction(SIGINT, &sa, NULL) == -1) {
perror("sigaction SIGINT");
free(alt_stack.ss_sp);
return 1;
}

if (sigaction(SIGTERM, &sa, NULL) == -1) {
perror("sigaction SIGTERM");
free(alt_stack.ss_sp);
return 1;
}

printf("Program started.\n");
printf("Process PID: %d\n", getpid());
printf("Alternative stack was created using sigaltstack.\n");
printf("Press Ctrl+C or run from another terminal: kill -TERM %d\n", getpid());

while (!stop_program) {
printf("Program is running...\n");
sleep(2);
}

printf("Program is shutting down correctly after receiving a signal.\n");

alt_stack.ss_flags = SS_DISABLE;
sigaltstack(&alt_stack, NULL);

free(alt_stack.ss_sp);

return 0;
}