#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
if (argc != 3){
printf("Usage: %s <word> <file>\n", argv[0]);
return 1;
}
FILE *f = fopen(argv[2], "r");
if (!f){
perror("fopen");
return 1;
}
char line[1024];
while (fgets(line, sizeof(line), f) != NULL){
if (strstr(line, argv[1])!= NULL) {
printf("%s", line);
}
}
fclose(f);
return 0;
}
