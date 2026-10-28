#include <stdio.h>
#include <stdlib.h>

int main(void) {
    /* 1. Локальна змінна на стеку */

    int stack_var = 42;

    /* 2. Виділення пам'яті в купі під 3 елементи (calloc обнуляє пам'ять) */

    int *heap_array = (int *)calloc(3, sizeof(int));
    if (heap_array == NULL) {
        fprintf(stderr, "Помилка: calloc не зміг виділити пам'ять\n");
        return 1;
    }
    for (int i = 0; i < 3; i++) {
        heap_array[i] = (i + 1) * 10;
    }

    /* 3. Адреси: змінна на стеку, сам вказівник (теж на стеку), блок у купі */

    printf("=== Початковий стан (3 елементи) ===\n");
    printf("Змінна stack_var            (Stack): %p\n", (void *)&stack_var);
    printf("Вказівник heap_array        (Stack): %p\n", (void *)&heap_array);
    printf("Масив heap_array (3 елем.)  (Heap) : %p\n", (void *)heap_array);
    printf("Значення: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", heap_array[i]);
    }
    printf("\n\n");

    /* 4. Збільшуємо масив до 5 елементів через realloc */

    int *tmp = (int *)realloc(heap_array, 5 * sizeof(int));
    if (tmp == NULL) {
        fprintf(stderr, "Помилка: realloc не зміг змінити розмір\n");
        free(heap_array); /* старий блок ще валідний, його треба звільнити */
        return 1;
    }
    heap_array = tmp;

    /* Нові елементи після realloc НЕ ініціалізовані - записуємо значення */

    heap_array[3] = 40;
    heap_array[4] = 50;

    printf("=== Після realloc (5 елементів) ===\n");
    printf("Змінна stack_var            (Stack): %p\n", (void *)&stack_var);
    printf("Вказівник heap_array        (Stack): %p\n", (void *)&heap_array);
    printf("Масив heap_array (5 елем.)  (Heap) : %p\n", (void *)heap_array);
    printf("Значення: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", heap_array[i]);
    }
    printf("\n\n");

    /* 5. Звільнення пам'яті */

    free(heap_array);
    heap_array = NULL; 
    printf("Пам'ять звільнено.\n");

    return 0;
}




