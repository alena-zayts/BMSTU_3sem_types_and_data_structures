#include "list.h"

int list_insert(list_t *arr, int value)
{
    if (arr->next == NULL)
    {
        arr->next = calloc(1, sizeof(list_t));
        arr->value = value;
        return 1;
    }
    int depth = 1;
    depth += list_insert(arr->next, value);
    return depth;
}

int list_cmp(int value, list_t list)
{
    list_t *list_p = &list;
    int i = 0;

    while (list_p != NULL && list_p->value != 0)
    {
        i++;
        if (value == list_p->value)
            return i;
        list_p = list_p->next;
    }
    return 0;
}

int list_occupation(list_t *arr, int size)
{
    int occupation = 0;
    for (int i = 0; i < size; i++)
        if (arr[i].value != 0)
            occupation++;
    return occupation;
}

static void free_list(list_t *list)
{
    if (list)
    {
        free_list(list->next);
        free(list);
    }
}

void free_list_arr(list_t *arr, int size)
{
    for (int i = 0; i < size; i++)
        free_list(arr[i].next);
    free(arr);
}
