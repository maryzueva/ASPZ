# Лабораторна робота №2  
## Дослідження пам’яті процесу та стеку викликів у Linux
---

## Мета роботи

Ознайомитися зі структурою пам’яті процесу в операційній системі Linux,  
дослідити сегменти виконуваного файлу, розглянути механізм роботи стеку викликів функцій,  
а також проаналізувати роботу часу в системі та проблему **Y2038**.

---

## Компіляція та запуск
```
gcc file.c -o program
./program
```
--- 

# Завдання task1_time
## Дослідження типу `time_t`

### Умова завдання

Необхідно написати програму, яка визначає:

- розмір типу `time_t`
- поточний час системи
- чи може виникнути проблема **Y2038**

---

## Код програми

```c
#include <stdio.h>
#include <time.h>

int main(){

printf("Research time_t\n");

printf("sizeof(time_t) = %zu byte\n", sizeof(time_t));

time_t now = time(NULL);

printf("date: %s", ctime(&now));

if (sizeof(time_t) == 4){
printf("Possible problem Y2038\n");
}
else{
printf("64-bit time_t, problem unlikely\n");
}

return 0;
}
```
## Результат роботи 
<img width="563" height="149" alt="image" src="https://github.com/user-attachments/assets/6ead1022-6e82-4bde-b0e1-38b278162eaf" />

---
# Завдання task2_bss
Дослідження глобальних змінних та сегмента BSS

## Умова завдання

Необхідно створити програму з глобальним масивом без ініціалізації та дослідити його значення при запуску програми.
---

## Код програми
```c
#include <stdio.h>

int big_array[1000];

int main(){

printf("Hello, world!\n");

printf("big_array[0] = %d\n", big_array[0]);

return 0;
}
```
## Результат роботи 
<img width="548" height="111" alt="image" src="https://github.com/user-attachments/assets/d507f313-e0a9-4543-831c-aeb1a48325ca" />

---
Глобальний масив big_array не має явної ініціалізації, тому він автоматично ініціалізується нулями.

Такі змінні зберігаються у сегменті BSS (Block Started by Symbol), який призначений для неініціалізованих глобальних та статичних змінних.
---
# Завдання task2_data
Дослідження ініціалізованих глобальних змінних

## Умова завдання

Необхідно створити глобальний масив з ініціалізацією та дослідити його значення.
---
## Код програми
```c
#include <stdio.h>

int big_array[1000] = {1};

int main(){

printf("Hello, world!\n");

printf("big_array[0] = %d\n", big_array[0]);

return 0;
}
```
## Результат роботи 

<img width="568" height="104" alt="image" src="https://github.com/user-attachments/assets/ad3d6d5b-39f9-439b-96f6-c778ccaadc35" />

---
Глобальний масив ініціалізується значенням {1}, тобто:

перший елемент дорівнює 1

всі інші автоматично дорівнюють 0

Такі змінні зберігаються у сегменті Data.

---
# Завдання task2_hello
Базова структура програми на C
## Умова завдання

Створити найпростішу програму, яка виводить повідомлення на екран.

## Код програми
```c
#include <stdio.h>

int main(){

printf("Hello world\n");

return 0;
}
```
Це базова структура будь-якої програми на мові C:

функція main() — точка входу

printf() — вивід на екран
---
## Результат роботи 

<img width="578" height="108" alt="image" src="https://github.com/user-attachments/assets/1ece0faf-ab45-4fa6-adc0-0f1a8c5d20ac" />


---
# Завдання task2_stack
Дослідження локальних масивів (Stack)
---
##  Умова завдання

Необхідно створити функцію з локальними масивами та дослідити їх значення при виконанні програми.
---

## Код програми
```c
#include <stdio.h>

void test_arrays(){

int array1[1000];
int array2[1000] = {1};

array1[10] = 10;

printf("array1[0] = %d\n", array1[0]);
printf("array2[0] = %d\n", array2[0]);

}

int main(){

printf("Hello, world!\n");

test_arrays();

return 0;
}
```
## Результат роботи 
<img width="650" height="123" alt="image" src="https://github.com/user-attachments/assets/0520b488-7a0c-49a2-8c9f-cc9e39c297fb" />

---
array1 — неініціалізований масив, містить випадкові значення (сміття)

array2 — ініціалізований, перший елемент дорівнює 1, інші — 0

обидва масиви знаходяться у стеку (stack)

---
# Завдання task3_memory
Дослідження розміщення пам’яті процесу
---
## Умова завдання

Необхідно дослідити розміщення різних типів змінних у пам’яті процесу.

## Код програми
```c
#include <stdio.h>
#include <stdlib.h>

int global_init = 100;
int global_uninit;

static int static_init = 200;
static int static_uninit;

void fun(){
printf("This is function example\n");
}

int main(){

int local_var = 10;
int *heap_var = malloc(sizeof(int));

if (heap_var == NULL){
printf("Memory allocation error\n");
return 1;
}

*heap_var = 300;

printf("Memory layout\n");

printf("Adress of main:                  %p\n", (void*)main);
printf("Adress of function example:      %p\n", (void*)fun);

printf("Adress of global_init:           %p\n", (void*)&global_init);
printf("Adress of global_uninit:         %p\n", (void*)&global_uninit);

printf("Adress of static_init:           %p\n", (void*)&static_init);
printf("Adress of static_uninit:         %p\n", (void*)&static_uninit);

printf("Adress of local_var:             %p\n", (void*)&local_var);
printf("Adress of heap_var value:        %p\n", (void*)heap_var);
printf("Adress of heap_var pointer:      %p\n", (void*)&heap_var);

free(heap_var);

return 0;
}
```
## Результат роботи 
<img width="598" height="263" alt="image" src="https://github.com/user-attachments/assets/25c8ef36-3cf2-4f5c-b7a7-42c9195016e4" />

---
У програмі досліджуються різні сегменти пам’яті:

Code segment — функції (main, fun)

Data segment — ініціалізовані змінні

BSS — неініціалізовані змінні

Stack — локальні змінні

Heap — динамічна пам’ять (malloc)
---

# Завдання task4_trace
Дослідження стеку викликів функцій
## Умова завдання

Необхідно дослідити роботу стеку викликів функцій та зміну адрес локальних змінних.

## Код програми
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG "In function %20s; &localvar = %p\n"

static void bar_is_now_closed(void){

int localvar = 5;

printf(MSG, __func__, (void*)&localvar);

printf("\nNow blocking on pause()...\n");

pause();
}

static void bar(void){

int localvar = 5;

printf(MSG, __func__, (void*)&localvar);

bar_is_now_closed();
}

static void foo(void){

int localvar = 5;

printf(MSG, __func__, (void*)&localvar);

bar();
}

int main(void){

int localvar = 5;

printf("PID = %d\n", getpid());

printf(MSG, __func__, (void*)&localvar);

foo();

exit(EXIT_SUCCESS);
}
```
## Виконання завдання

Якщо використовується Ubuntu Server без графічного інтерфейсу, для роботи з процесами необхідно використовувати кілька віртуальних консолей.

Перехід до іншої консолі
Для відкриття другої консолі:
```
Ctrl + Alt + F2
```
Після цього потрібно виконати вхід у систему:
```
login: _____
password: ********
```
Повернення до основної консолі
Для повернення до першої консолі:
```
Ctrl + Alt + F1
```
У Linux існує можливість роботи з кількома віртуальними консолями одночасно.

Це дозволяє:

запускати програму в одній консолі

аналізувати її виконання в іншій

досліджувати пам’ять процесу (наприклад через ps, top, /proc)

<img width="646" height="218" alt="image" src="https://github.com/user-attachments/assets/9e7abaf1-00af-41bc-b46f-1b01362b5f9f" />

<img width="646" height="218" alt="image" src="https://github.com/user-attachments/assets/b8fc556c-2c3b-4acc-b3d6-b6100f300506" />

<img width="991" height="429" alt="image" src="https://github.com/user-attachments/assets/10f2326f-0408-4c39-9675-87b6d4f700b6" />
## Встановити gdb

У другому терміналі введи:
```
sudo apt update
sudo apt install gdb
```
Ubuntu запитає:
Do you want to continue? [Y/n]
натисни: Y

<img width="959" height="190" alt="image" src="https://github.com/user-attachments/assets/b018c93e-566f-4ffd-b587-61e203ab9d45" />

<img width="834" height="366" alt="image" src="https://github.com/user-attachments/assets/d829c376-9463-47eb-a7dc-46a255414a4b" />

---
## Результат роботи 
<img width="983" height="403" alt="image" src="https://github.com/user-attachments/assets/454d5f3e-8110-4377-aba4-c751c4fd1309" />

кожна функція має власну область у стеку

адреси локальних змінних змінюються при викликах

стек росте при виклику функцій і зменшується при поверненні
---
# Завдання 5
---
## Умова завдання
Відомо, що при виклику процедур і поверненні з них процесор використовує стек.Чи можна в такій схемі обійтися без лічильника команд (IP), використовуючи замість нього вершину стека? Обґрунтуйте свою відповідь та наведіть приклади.
---
## Відповідь

Ні, повністю обійтися без лічильника команд (IP), використовуючи лише стек, неможливо. Лічильник команд — це спеціальний регістр процесора, який постійно вказує на наступну інструкцію, що має виконуватися, і автоматично змінюється після кожної операції. Саме він забезпечує послідовне виконання програми. Стек же використовується лише під час виклику функцій: при виклику в нього зберігається адреса повернення, а при завершенні функції ця адреса дістається зі стеку і записується назад у IP. Тобто стек лише тимчасово зберігає значення лічильника команд, але не керує виконанням програми постійно. Крім того, багато інструкцій, таких як умовні та безумовні переходи (наприклад, if, loop, jmp), змінюють IP напряму без використання стеку. Також на початку виконання програми стек взагалі може бути порожнім, тому не можна отримати адресу першої інструкції зі стеку. Отже, стек не може замінити лічильник команд, оскільки він виконує лише допоміжну функцію, а основне керування виконанням програми здійснюється саме через IP.
---
# Завдання task6_buffer
Дослідження переповнення буфера
## Умова завдання

Необхідно продемонструвати небезпеку переповнення буфера та способи його уникнення.

---
## Код програми
```c
#include <stdio.h>
#include <string.h>

void vulnerable(char *input){

char buffer[10];

printf("Copying string...\n");

strcpy(buffer, input);

printf("Buffer contains: %s\n", buffer);
}

void safe(char *input){

char buffer[10];

printf("Safe copying...\n");

strncpy(buffer, input, sizeof(buffer) - 1);

buffer[sizeof(buffer) - 1] = '\0';

printf("Buffer contains: %s\n", buffer);
}

int main(){

char short_text[] = "Hello";
char long_text[] = "AAAAAAAAAAAAAA";

printf("Vulnerable function\n");
vulnerable(short_text);

printf("Safe function\n");
safe(long_text);

return 0;
}
```
## Результат роботи 
<img width="794" height="262" alt="image" src="https://github.com/user-attachments/assets/e5f0f83b-5fad-4d36-b6d2-8abe61e3d9f3" />

---
strcpy() не перевіряє розмір буфера → можливе переповнення

strncpy() обмежує кількість символів

переповнення буфера може призвести до збоїв або атак

---
# Висновок
У ході виконання лабораторної роботи було комплексно досліджено організацію пам’яті процесу в операційній системі Linux та особливості виконання програм мовою C.

Було розглянуто структуру пам’яті процесу, зокрема сегменти Code, Data, BSS, Stack та Heap, і визначено їх призначення та особливості використання. Експериментально підтверджено, що:

глобальні неініціалізовані змінні розміщуються в сегменті BSS та автоматично ініціалізуються нулями;

ініціалізовані змінні зберігаються в сегменті Data;

локальні змінні розміщуються у стеку та можуть містити невизначені значення без ініціалізації;

динамічна пам’ять виділяється в області Heap.

Також було досліджено роботу стеку викликів функцій, що дозволило зрозуміти механізм передачі керування між функціями та зміну адрес локальних змінних при вкладених викликах.

Окрему увагу приділено типу time_t та проблемі Y2038, що може виникати в 32-бітних системах, а також продемонстровано способи її уникнення.

У процесі роботи було виявлено типові помилки програмування, зокрема:

використання неініціалізованих змінних;

переповнення буфера при роботі з рядками;

неправильне використання динамічної пам’яті.

Було розглянуто методи їх усунення, що підвищує надійність і безпеку програм.




