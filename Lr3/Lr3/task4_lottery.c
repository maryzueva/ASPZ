#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t stop = 0;

void cpu_limit(int sig) {
stop = 1;
}

int unique(int arr[], int size, int num){
for (int i = 0; i < size; i++){
if (arr[i] == num){
return 0;
}
}
return 1;
}

void print_ticket(int nums49[], int nums36[]){
printf("7 of 49: ");
for (int i = 0; i < 7; i++){
printf("%d", nums49[i]);
}

printf("6 of 36: ");
for (int i = 0; i < 6; i++){
printf("%d", nums36[i]);
}
printf("\n");
}

void generate(int arr[], int count, int max){
for(int i = 0; i < count; i++){
int n;
do{
n = rand() % max + 1;
} while (!unique(arr, i, n));
arr[i] = n;
}
}


int main(){
int nums49[7];
int nums36[6];
long counter = 0;

srand(time(NULL));

signal(SIGXCPU, cpu_limit);

printf("Starting lottery simulation...\n");


while (!stop){
generate(nums49, 7, 49);
generate(nums36, 6, 36);

counter++;

if(counter % 1000 == 0){
print_ticket(nums49, nums36);
}
}
printf("\nCPU time limit reached\n");
printf("Generated combinations: %ld\n", counter);
return 0;
}

