#include "sort.h"

//сортировка таблицы ключей методом пузырька
void sort_keys_bubble(int key_arr[][2], int n)
{
    int temp[2];
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (key_arr[j][1] > key_arr[j + 1][1])
            {
                temp[0] = key_arr[j][0];
                temp[1] = key_arr[j][1];
                key_arr[j][0] = key_arr[j + 1][0];
                key_arr[j][1] = key_arr[j + 1][1];
                key_arr[j + 1][0] = temp[0];
                key_arr[j + 1][1] = temp[1];
            }
        }
    }
}

//сортировка основной таблицы методом пузырька
void sort_books_bubble(book_struct book_arr[], int n)
{
    book_struct temp;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (book_arr[j].pages > book_arr[j + 1].pages)
            {
                temp = book_arr[j];
                book_arr[j] = book_arr[j + 1];
                book_arr[j + 1] = temp;
            }
        }
    }
}

//сравнение для записей в таблице ключей
int int2_cmp(const void *val1, const void *val2)
{
    int *x = (int *) val1;
    int *y = (int *) val2;
    return ((*(x + 1) - (*(y + 1))));
}

//сравнение для записей в основной таблице
int struct_cmp(const void *val1, const void *val2)
{
    book_struct *x = (book_struct *) val1;
    book_struct *y = (book_struct *) val2;
    return ((x->pages) - (y->pages));
}
