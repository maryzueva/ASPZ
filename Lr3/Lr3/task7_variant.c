# include <stdio.h>
#include <stdlib.h>
int main(){
FILE *files[10000];
int count =0;
char filename[50];
while (count<10000){
sprintf(filename, "file_%d.txt", count);
files[count] = fopen(filename, "w");
if (files[count]==NULL){
printf("Cannot open more files\n");
printf("Opened files: %d\n", count);
break;
}
count ++;
}
for(int i=0; i<count; i++){
fclose (files[i]);
}
return 0;
}
