#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp_int(const void *a, const void *b){
int x = *(const int *)a;
int y = *(const int *)b;
return x - y;
}

void fill_random(int *a, int n){
for (int i = 0; i < n; i++) a[i] = rand() % 100000;
}

void fill_sorted(int *a, int n){
for (int i = 0; i < n; i++) a[i] = i;
}

void fill_reverse(int *a, int n){
for (int i = 0; i < n; i++) a[i] = n - i;
}

void fill_equal(int *a, int n){
for (int i = 0; i < n; i++) a[i] = 1;
}

void fill_almost_sorted(int *a, int n){
for (int i = 0; i < n; i++) a[i] = i;
if(n > 10){
a[n / 2] = -1;
a[n / 3] = 999999;
}
}

int is_sorted(int *a, int n){
for(int i = 1; i < n; i++){
if(a[i - 1] > a[i]) return 0;
}
return 1;
}

double measure_sort_time(int *a, int n){
clock_t start = clock();
qsort(a, n, sizeof(int), cmp_int);
clock_t end = clock();
return (double)(end - start) / CLOCKS_PER_SEC;
}

void run_case(const char *name, void (*fill)(int *, int), int n){
int *a = malloc(n * sizeof(int));
fill(a, n);

double t = measure_sort_time(a, n);

printf("%-15s time = %.6f sec, sorted = %s\n", name, t, is_sorted(a, n) ? "yes" : "no");

free(a);
}

void run_tests(){
int t1[] = {5, 4, 3, 2, 1};
int t2[] = {1, 2, 3, 4, 5};
int t3[] = {3, 1, 2, 3, 1, 2};
int t4[] = {7};
int t5[] = {10, -2, 0, 8, 8, 3};

qsort(t1, 5, sizeof(int), cmp_int);
qsort(t2, 5, sizeof(int), cmp_int);
qsort(t3, 6, sizeof(int), cmp_int);
qsort(t4, 1, sizeof(int), cmp_int);
qsort(t5, 6, sizeof(int), cmp_int);

printf("\nTests:\n");
printf("Test 1: %s\n", is_sorted(t1, 5) ? "PASS" : "FAIL");
printf("Test 2: %s\n", is_sorted(t2, 5) ? "PASS" : "FAIL");
printf("Test 3: %s\n", is_sorted(t3, 6) ? "PASS" : "FAIL");
printf("Test 4: %s\n", is_sorted(t4, 1) ? "PASS" : "FAIL");
printf("Test 5: %s\n", is_sorted(t5, 6) ? "PASS" : "FAIL");
}

int main() {
srand(time(NULL));

int n = 50000;

printf("Experiment for qsort, n = %d\n\n", n);

run_case("random", fill_random, n);
run_case("sorted", fill_sorted, n);
run_case("reverse", fill_reverse, n);
run_case("equal", fill_equal, n);
run_case("almost sorted", fill_almost_sorted, n);

run_tests();

return 0;
}
