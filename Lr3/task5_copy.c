#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void file_limit(int sig){
printf ("File size limit exceeded\n");
exit(1);
}

int main (int argc, char *argv[]){
FILE *src, *dst;
int ch;

signal(SIGXFSZ, file_limit);

if (argc != 3){
printf("Program need two arguments\n");
return 1;
}

src = fopen(argv[1], "r");
if(src == NULL){
printf("Cannot open file %s for readung\n", argv[1]);
return 1;
}

dst = fopen(argv[2], "w");
if (dst == NULL){
printf("Cannot open file %s for writing\n", argv[2]);
fclose(src);
return 1;
}
while ((ch = fgetc(src)) != EOF) {
if (fputc(ch, dst) == EOF){
printf("File size limit exceeded\n");
fclose(src);
fclose(dst);
return 1;
}
}
fclose(src);
fclose(dst);

printf("File copied successfully\n");
return 0;
}



