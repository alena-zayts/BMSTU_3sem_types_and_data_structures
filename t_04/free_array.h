#ifndef FREE_ARRAY_H
#define FREE_ARRAY_H

#include "main_header.h"

//массив свободных областей
typedef struct
{
    size_t *arr; //указатель на массив адресов
    int capacity; //вместимость массива
    int tek; //текущий свободный элемент
} free_arr_s;

free_arr_s *create_free_arr(const int capacity);

void output_free_arr(const free_arr_s arr);

void free_free_arr(free_arr_s *arr);

#endif // FREE_ARRAY_H
