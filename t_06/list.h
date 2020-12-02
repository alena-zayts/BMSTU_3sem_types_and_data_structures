#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

#include "main_header.h"

typedef struct list
{
    int value; //значение
    struct list *next; //указатель на следующий элемент
} list_t;

int list_insert(list_t *arr, int value);
int list_cmp(int value, list_t list);
int list_occupation(list_t *arr, int size);
void free_list_arr(list_t *arr, int size);

#endif // LIST_H
