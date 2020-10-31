#include "stack_list.h"

/*
Создание узла стека в виде списка
Входные данные:
    int data - значение элемента
Выходные данные:
    node - указатель на созданный узел
*/
stack_list_s *create_stack_list_node(const int data)
{
    stack_list_s *node = NULL;
    node = malloc(sizeof(stack_list_s));
    if (node != NULL)
    {
        node->data = data;
        node->ind = 0;
        node->next = NULL;
    }
    return node;
}

/*
Проверка переполнения стека в виде списка
Входные данные:
    stack_list_s *root - указатель на узел - корень
    const int limit - ограничение по размеру
Выходные данные:
    1 если стек полон, иначе - 0
*/
int is_full_stack_list(stack_list_s *root, const int limit)
{
    return root->ind == limit;
}

/*
Проверка пустоты стека в виде списка
Входные данные:
   stack_list_s *root узел - корень
Выходные данные:
   1 если стек пуст, иначе - 0
*/
int is_empty_stack_list(stack_list_s *root)
{
    return !root;
}

/*
Добавление элемента в стек в виде списка
Входные данные:
    stack_list_s **root - указатель на узел - корень
    const int data - добавляемое значение
Выходные данные:
    код ошибки
*/
int push_stack_list(stack_list_s **root, const int data, uint64_t *time)
{
    uint64_t start, stop;

    start = tick();
    stack_list_s *node = create_stack_list_node(data);
    if (node == NULL)
        return ERRMEM;
    if ((*root) != NULL)
        node->ind = ((*root)->ind) + 1;
    else
        node->ind = 0;
    node->next = *root;
    *root = node;
    stop = tick();
    *time = stop - start;
    return OK;
}

/*
Ввод стека в виде списка
Входные данные:
    const int count - количество элементов
    stack_list_s **root - указатель на текущий элемент списка
Выходные данные:
    код ошибки
*/
int input_stack_list(const int count, stack_list_s **root, uint64_t *time)
{
    int el;

    for (int i = 0; i < count; i++)
    {
        if (count > 1)
            printf("Input int element number %d:\n", i+1);
        else
            printf("Input int element to be added:\n");
        fflush(stdin);
        while ((scanf("%d", &el) != 1) || (getchar() != '\n'))
        {
            printf("ERROR: incorrect value of element. Try again:\n");
            fflush(stdin);
        }
        if (push_stack_list(root, el, time))
            return ERRMEM;
    }
    printf("Succesfully input %d elemnts of stack-list\n", count);
    return OK;
}

/*
Вывод стека в виде списка
Входные данные:
    stack_list_s *root стек
Выходные данные:
    код ошибки
*/
int output_stack_list(stack_list_s *root)
{
    if (is_empty_stack_list(root))
        return ERREMPTY;

    int size = root->ind;
    stack_list_s *out = root;
    printf("Value ~ address\n");

    while (size >= 0)
    {
        printf("%d ~ %zx\n", out->data, (size_t)out);
        out = out->next;
        size--;
    }

    return OK;
}

/*
Pop - получение значения элемента и его удаление из стека в виде списка
Входные данные:
    stack_list_s **root указатель на узел
    free_arr_s *fmem - массив свободных областей
    int *el куда записывать элемент
Выходные данные:
    код ошибки
*/

void pop_stack_list(stack_list_s **root, free_arr_s *fmem, int *el, uint64_t *time)
{
    uint64_t start, stop;

    start = tick();
    stack_list_s *temp = *root;
    *root = (*root)->next;
    *el = temp->data;
    fmem->arr[++(fmem->tek)] = (size_t)temp;
    free(temp);
    stop = tick();
    *time = stop - start;
}

/*
Проверить, есть ли адрес корня в массиве свободных областей и удалить его, если так
Входные адреса:
    stack_list_s *root узел стека
    free_arr_s *fmem массив свободных областей
*/
void check_top_stack_list(stack_list_s *root, free_arr_s *fmem)
{
    size_t top = (size_t)root;

    for (int i = 0; i < fmem->tek; i++)
    {
        if (top == fmem->arr[i])
        {
            for (int j = i; j < fmem->tek - 1; ++j)
            {
                size_t temp = fmem->arr[j];
                fmem->arr[j] = fmem->arr[j + 1];
                fmem->arr[j + 1] = temp;
            }
        }
    }
    fmem->tek--;
}

/*
Высвобождение памяти из под стека в виде списка
Входные данные:
    stack_list_s **root - указатель на корень
    free_arr_s *fmem массив свободных областей
*/
void free_stack_list(stack_list_s **root, free_arr_s *fmem)
{
    uint64_t time;
    if (*root != NULL)
    {
        int el;
        while (!is_empty_stack_list(*root))
            pop_stack_list(root, fmem, &el, &time);
    }
}
