#include <stdio.h>
#include <stdlib.h>

int main(void){
FILE *in = popen("ls", "r");
if (in == NULL) {
perror("popen rwho");
return 1;
}

FILE *out = popen("more", "w");
if (out == NULL){
perror("popep more");
pclose(in);
return 1;
}
char buffer[256];
while (fgets(buffer, sizeof(buffer), in) != NULL){
fputs(buffer, out);
}

pclose(in);
pclose(out);
return 0;
}
