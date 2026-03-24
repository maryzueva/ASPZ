#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
FILE *file;
int dice;

srand(time(NULL));

file = fopen("dice_results.txt", "w");

if (file == NULL) {
printf("Cannot open file for writing\n");
return 1;
}

printf("Starting dice simulation...\n");

for (int i = 0; i < 1000000; i++) {
dice = rand() % 6 + 1;

if (fprintf(file, "%d\n", dice) < 0) {
printf("File size limit reached\n");
break;
}
fflush(file);
}
fclose(file);

printf("Program finished\n");
return 0;
}
