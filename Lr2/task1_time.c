#include <stdio.h>
#include <time.h>

int main(){
printf ("Research time_t\n");
printf ("sizeof(time_t) = %zu byte\n", sizeof(time_t));

time_t now = time(NULL);
printf ("date: %s", ctime(&now));

if (sizeof(time_t) == 4) {
printf("Possible problem Y2038\n");
}
else {
printf("64-bit time_t, problem unlikely\n");
}
return 0;
}
