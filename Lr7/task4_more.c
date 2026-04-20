#include <stdio.h>
#include <stdlib.h>

void wait_enter(void){
printf("\n--- Press Enter to continue ---");
while (getchar() != '\n');
}

int main(int argc, char *argv[]){
if(argc < 2){
printf("Usage: %s <file1> [file2 ...]\n", argv[0]);
return 1;
}

for (int i = 1; i < argc; i++) {
FILE *f = fopen(argv[i], "r");
if (!f){
perror(argv[i]);
continue;
}
printf("\n=== %s ===\n", argv[i]);

char line[1024];
int count = 0;
while(fgets(line, sizeof(line), f) != NULL){
printf("%s", line);
count++;

if (count % 20 == 0) {
wait_enter();
}
}
fclose(f);
}
return 0;
}
