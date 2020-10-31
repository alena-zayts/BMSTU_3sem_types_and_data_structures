#include "stack_operations.h"

/*
Поиск убывающих подпоследовательностей в последовательности
в стеке в виде массива
Входные данные:
    stack_arr_s *stack - стек
Выходные данные:
    Количество убывающих подпоследовательностей
*/

int dec_order_arr(stack_arr_s *stack)
{
    uint64_t time;
    int el;
    pop_stack_arr(stack, &el, &time);
    int count = 0;
    int *arr;
    int new_el;
    int i;

    while (!is_empty_stack_arr(stack))
    {
        arr = malloc((stack->capacity) * sizeof(int));
        pop_stack_arr(stack, &new_el, &time);

        arr[0] = el;
        i = 1;

        while (new_el > el)
        {
            arr[i] = new_el;
            i++;
            el = new_el;
            if (!is_empty_stack_arr(stack))
                pop_stack_arr(stack, &new_el, &time);
        }
        el = new_el;

        if (i != 1)
        {
            count++;
            for (int j = 0; j < i; j++)
                printf("%d ", arr[j]);
            printf("\n");

        }
        free(arr);
    }
    return count;
}

/*
Поиск убывающих подпоследовательностей в последовательности
в стеке в виде списка
Входные данные:
    stack_list_s **root - указатель на корень стека
    free_arr_s *fmem массив свободных областей
Выходные данные:
    Количество убывающих подпоследовательностей
*/
int dec_order_list(stack_list_s **root, free_arr_s *fmem)
{
    uint64_t time;
    int el;
    pop_stack_list(root, fmem, &el, &time);
    int count = 0;

    while (!is_empty_stack_list(*root))
    {
        int *arr = malloc(fmem->capacity * sizeof(int));
        int new_el;
        pop_stack_list(root, fmem, &new_el, &time);

        arr[0] = el;
        int i = 1;

        while (new_el > el)
        {
            arr[i] = new_el;
            i++;
            el = new_el;
            if (!is_empty_stack_list(*root))
                pop_stack_list(root, fmem, &new_el, &time);
        }
        el = new_el;

        if (i != 1)
        {
            count++;

            for (int j = 0; j < i; ++j)
                printf("%d ", arr[j]);
            printf("\n");
        }

        free(arr);
    }

    return count;
}


