#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50
#define EPS 0.001

int equal(float a, float b){
return (a - b < EPS && b - a < EPS);
}

void find1D(float a[], int n, float x){
int i, found = 0;
for (i = 0; i < n; i++){
if (equal(a[i], x)){
printf("Index: %d\n", i);
found = 1;
}
}
if (!found){
printf ("No matches\n");
}
}
void find2D(float a[][MAX], int rows, int cols, float x){
int i, j, found = 0;
for (i = 0; i < rows; i++){
for (j = 0; j < cols; j++){
if (equal(a[i][j], x)){
printf("Index: (%d,%d)\n", i, j);
found = 1;
}
}
}
if (!found){
printf("No matches\n");
}
}
int main() {
int mode;
float x;
srand(time(NULL));

printf("1 - 1D array    \n 2 - 2D array   \nChoose:");
scanf("%d", &mode);

printf ("Enter number to find:");
scanf ("%f", &x);

if (mode == 1){
int n, i;
float a[MAX];

printf ("Enter size:");
scanf("%d", &n);
for (i = 0; i < n; i++){
a[i] = (float)rand() / RAND_MAX * 10;
printf("a[%d] = %.2f\n", i, a[i]);
}
find1D(a, n, x);
}
else{
int rows, cols, i, j;
float a[MAX][MAX];

printf("Enter rows and cols:");
scanf ("%d %d", &rows, &cols);

for (i = 0; i < rows; i++){
for(j = 0; j < cols; j++) {
a[i][j] = (float)rand()/RAND_MAX * 10;
printf("a[%d][%d] = %.2f\n", i, j, a[i][j]);
}
}
printf ("\n");
find2D (a, rows, cols, x);
}
return 0;
}
