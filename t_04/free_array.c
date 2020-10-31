#include "free_array.h"

/*
Создание массива свободных областей.
Входные данные:
   const int capacity - вместимость массива.
Выходные даннын:
   arr - указатель на созданный массив
*/
free_arr_s *create_free_arr(const int capacity)
{
    free_arr_s *arr = NULL;
    arr = malloc(sizeof(free_arr_s));
    if (arr != NULL)
    {
        arr->capacity = capacity;
        arr->tek= -1;
        arr->arr = NULL;
        arr->arr = malloc((arr->capacity) * sizeof(size_t));
        if ((arr->arr) == NULL)
        {
            free(arr);
            arr = NULL;
        }
    }
    return arr;
}

/*
Вывод массива свободных областей до текущего элемента
Входные данные:
  const free_arr_s arr указатель на массив свободных областей
*/
void output_free_arr(const free_arr_s arr)
{
    if (arr.tek == -1)
        printf("ERROR: array of free areas is emty\n");
    else
        for (int i = 0; i < (arr.tek + 1); i++)
            printf("%zx\n", arr.arr[i]);
    printf("END\n");
}

/*
Высвобождение памяти из под массива свободных областей.
Входные данные:
    free_arr_s *arr указатель на освобождаемый массив
*/
void free_free_arr(free_arr_s *arr)
{
    if (arr != NULL)
    {
        if ((arr->arr) != NULL)
            free(arr->arr);
        free(arr);
    }
}
