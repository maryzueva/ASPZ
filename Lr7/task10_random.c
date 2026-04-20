#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rand_0_1(void){
return (double)rand() / (double)RAND_MAX;
}

double rand_0_n(double n){
return rand_0_1() * n;
}

int main(void){
srand((unsigned int)time(NULL));

printf("Random numbers [0.0, 0.1]:\n");
for (int i = 0; i < 5; i++){
printf("%.6f\n", rand_0_1());
}

double n;
printf("\nEnter n: ");
scanf("%lf", &n);

printf("Random numbers [0.0, %.2f]:\n", n);
for (int i = 0; i < 5; i++){
printf("%.6f\n", rand_0_n(n));
}
return 0;
}
