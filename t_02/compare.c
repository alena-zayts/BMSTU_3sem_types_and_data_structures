#include "compare.h"
#define X 5000

//сравнение эффективности различных алгоритмов и подходов
int compare(void)
{
    FILE *f;
    int n = 0;
    int rc = OK;
    book_struct book_arr[AMOUNT];
    memset(&book_arr, 0, sizeof(book_struct));
    book_struct temp;
    memset(&temp, 0, sizeof(book_struct));
    int key_arr[AMOUNT][2] = { 0 };
    struct timeval tv_start, tv_stop;
    int64_t time_main_bubble = 0, time_key_bubble = 0;
    int64_t time_main_quick = 0, time_key_quick = 0;

    //sort_main_bubble
    f = fopen("5000_books.txt", "r");
    if (f)
    {
        rc = input_from_file(f, book_arr, &n);
        n = X;
        if (rc == OK)
        {
            fill_key_arr(book_arr, key_arr, n);
            printf("Start counting time for sort_main_bubble\n");
            gettimeofday(&tv_start, NULL);
            sort_books_bubble(book_arr, n);
            gettimeofday(&tv_stop, NULL);
            time_main_bubble = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                   (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            return ERRCOMPARE;
        fclose(f);
    }
    else
       return ERRCOMPARE;


    //sort_main_quick
    f = fopen("5000_books.txt", "r");
    if (f)
    {
        rc = input_from_file(f, book_arr, &n);
        n = X;
        if (rc == OK)
        {
            fill_key_arr(book_arr, key_arr, n);
            printf("Start counting time for sort_main_quick\n");
            gettimeofday(&tv_start, NULL);
            qsort(book_arr, n, sizeof(book_struct), struct_cmp);
            gettimeofday(&tv_stop, NULL);
            time_main_quick = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +\
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            return ERRCOMPARE;
        fclose(f);
    }
    else
       return ERRCOMPARE;

    //sort_key_bubble
    f = fopen("5000_books.txt", "r");
    if (f)
    {
        rc = input_from_file(f, book_arr, &n);
        n = X;
        if (rc == OK)
        {
            fill_key_arr(book_arr, key_arr, n);
            printf("Start counting time for sort_key_bubble\n");
            gettimeofday(&tv_start, NULL);
            sort_keys_bubble(key_arr, n);
            for (int i = 0; i < n; i++)
                book_arr[key_arr[i][0]] = temp;
            gettimeofday(&tv_stop, NULL);
            time_key_bubble = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +\
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            return ERRCOMPARE;
        fclose(f);
    }
    else
        return ERRCOMPARE;

    //sort_key_quick
    f = fopen("5000_books.txt", "r");
    if (f)
    {
        n = X;
        rc = input_from_file(f, book_arr, &n);
        if (rc == OK)
        {
            fill_key_arr(book_arr, key_arr, n);
            printf("Start counting time for sort_key_sort\n");
            gettimeofday(&tv_start, NULL);
            qsort(key_arr, n , sizeof(int[2]), int2_cmp);
            for (int i = 0; i < n; i++)
                book_arr[key_arr[i][0]] = temp;
            gettimeofday(&tv_stop, NULL);
            time_key_quick = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +\
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            return ERRCOMPARE;
        fclose(f);
    }
    else
        return ERRCOMPARE;

    show_compare(time_main_bubble, time_key_bubble, time_main_quick, time_key_quick);
    return OK;
}

//вывод таблицы сравнения эффективности различных алгоритмов и подходов
void show_compare(int64_t time_main_bubble, int64_t time_key_bubble, int64_t time_main_quick, int64_t time_key_quick)
{
    printf("\nMeasurements were performed on a list of %d records\n\n", X);
    int mem_main = sizeof(book_struct) * X;
    int mem_keys = sizeof(int[2]) * X;

    printf("-------------------------------------------------------------------\n");
    printf("            |  using literature list   |      using key table     |\n");
    printf("------------|--------------------------|--------------------------|\n");
    printf("memory      |  %6d bytes (100.00%%)  | %6d bytes (%3.2f%%)   |\n",
           mem_main, (mem_main + mem_keys), (float) (mem_main + mem_keys)*100/mem_main);
    printf("------------|--------------------------|--------------------------|\n");
    printf("time bubble |  %6I64u usec (100.00%%)   |  %6I64u usec (%3.2f%%)    |\n",
           time_main_bubble, time_key_bubble, (float) (time_key_bubble * 100)/time_main_bubble);
    printf("time quick  |   %6I64u usec (%3.2f%%)    |  %6I64u usec (%3.2f%%)     |\n",
           time_main_quick,(float) (time_main_quick * 100)/time_main_bubble,
           time_key_quick, (float) (time_key_quick * 100)/time_main_bubble);
    printf("-------------------------------------------------------------------\n");
}

