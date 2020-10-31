#include "stack_array.h"

/*
Создание стека в виде массива
Входные данные:
   const int capacity - вместимость стека
Выходные данные:
   stack - указатель на созданный стек
*/

stack_arr_s *create_stack_arr(const int capacity)
{
    stack_arr_s *stack = NULL;
    stack = malloc(sizeof(stack_arr_s));
    if (stack != NULL)
    {
        stack->capacity = capacity;
        stack->top = -1;
        stack->arr = NULL;
        stack->arr = malloc((stack->capacity) * sizeof(int));
        if ((stack->arr) == NULL)
        {
            free(stack);
            stack = NULL;
        }
    }
    return stack;
}

/*
Высвобождение памяти из под стека в виде массива
Входные данные::
    stack_arr_s *stack - указатель на стек
*/
void free_stack_arr(stack_arr_s *stack)
{
    if (stack != NULL)
    {
        if ((stack->arr) != NULL)
            free(stack->arr);
        free(stack);
    }
}

/*
Проверка переполнения стека в виде массива
Входные данные:
   stack_arr_s *stack указатель на стек
Выходные данные:
   1 если стек полон, иначе - 0
*/
int is_full_stack_arr(stack_arr_s *stack)
{
    return (stack->top == ((stack->capacity) - 1));
}
/*
Проверка пустоты стека в виде массива
Входные данные:
   stack_arr_s *stack указатель на стек
Выходные данные:
   1 если стек пуст, иначе - 0
*/
int is_empty_stack_arr(stack_arr_s *stack)
{
    return (stack->top == -1);
}

/*
Добавление элемента в стек в виде массива
Входные данные:
    stack_arr_s *stack указатель на стек
    const int data добавляемый элемент
Выходные данные:
    код ошибки
*/
void push_stack_arr(stack_arr_s *stack, const int data, uint64_t *time)
{
    uint64_t start, stop;
    start = tick();
    stack->arr[++stack->top] = data;
    stop = tick();
    *time = stop-start;

}

/*
Ввод стека в виде массива
Входные данные:
    const int count - количество добавляемых элементов
    stack_arr_s *stack - указатель на созданный стек
Выходные данные:
    код ошибки
*/
void input_stack_arr(const int count, stack_arr_s *stack, uint64_t *time)
{
    int el;

    for (int i = 0; i < count; i++)
    {
        if (count > 1)
            printf("Input int element number %d:\n", i + 1);
        else
            printf("Input int element to be added:\n");
        fflush(stdin);
        while ((scanf("%d", &el) != 1) || (getchar() != '\n'))
        {
            printf("ERROR: incorrect value. Try again: ");
            fflush(stdin);
        }
        push_stack_arr(stack, el, time);
    }
    printf("Successfully added %d elements to stack-array\n", count);
}

/*
Вывод стека в виде массива
Входные данные:
    stack_arr_s *stack - указатель на созданный стек
*/
void output_stack_arr(stack_arr_s *stack)
{
    printf("\n");
    for (int i = stack->top; i >= 0; i--)
        printf("%d\n", stack->arr[i]);
}

/*
Pop - получение значения элемента и его удаление из стека в виде массива
Входные данные:
    stack_arr_s *stack указатель на стек
    int *el куда записывать элемент
Выходные данные:
    код ошибки
*/
void pop_stack_arr(stack_arr_s *stack, int *el, uint64_t *time)
{
    uint64_t start, stop;
    start = tick();
    (*el) = stack->arr[stack->top--];
    stop = tick();
    *time = stop-start;
}

