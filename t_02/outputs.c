#include "outputs.h"

//вывод одной записи
void print_book(book_struct book)
{
    printf("|%25s", book.author);
    printf("|%25s", book.name);
    printf("|%25s", book.pub);
    printf("|%4d", book.pages);
    printf("|%1d", book.type_l);
    if (book.type_l == 1)
    {
        printf("||%15s", book.type_l_inf.tech.field);
        printf("|%1d", book.type_l_inf.tech.origin);
        printf("|%4d|\n", book.type_l_inf.tech.year);
    }
    if (book.type_l == 2)
        printf("||%1d|\n", book.type_l_inf.fict);
    if (book.type_l == 3)
        printf("||%1d|\n", book.type_l_inf.child);
}

//вывод основной таблицы
void print_books(book_struct book_arr[], int n)
{
    printf("|i |                   author|                     name|         publishing house|page|t||\n");
    for (int i = 0; i < n; i++)
    {
        printf("|%2d", i);
        print_book(book_arr[i]);
    }
}

//вывод табицы ключей
void print_keys(int key_arr[][2], int n)
{
    printf("|i |i main table |num of pages|\n");
    for (int i = 0; i < n; i++)
    {
        printf("|%2d", i);
        printf("|%13d", key_arr[i][0]);
        printf("|%12d|\n", key_arr[i][1]);
    }
}

//вывод основной таблицы по порядку, указанному в таблице ключей
void print_books_by_keys(book_struct book_arr[], int key_arr[][2], int n)
{
    printf("|i |                   author|                     name|         publishing house|page|t||\n");
    for (int i = 0; i < n; i++)
    {
        printf("|%2d", key_arr[i][0]);
        print_book(book_arr[key_arr[i][0]]);
    }
}
