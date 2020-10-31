#include "deletes.h"

//очистка таблицы ключей
void clean_key_arr(int key_arr[][2])
{
    for (int i = 0; i < AMOUNT; i++)
    {
        key_arr[i][0] = 0;
        key_arr[i][1] = 0;
    }
}

//удалить записи по значению фамилии автора
int delte_by_surname(book_struct book_arr[], int key_arr[][2], int *n)
{
    int deleted = 0;
    char author[AUTHORLEN + 1] = { 0 };

    printf("Input author surname (up to %d symbols): ", AUTHORLEN);
    fflush(stdin);
    if (fgets(author, AUTHORLEN + 2, stdin) == NULL)
    {
        printf("ERROR: couldn't read author surname\n");
        return ERRVALUE;
    }
    if (author[0] == '\n')
    {
        printf("ERROR: couldn't read author surname\n");
        return ERRVALUE;
    }
    else if (author[strlen(author) - 1] == '\n')
        author[strlen(author) - 1] = '\0';
    else
    {
        printf("ERROR: couldn't read author surname\n");
        return ERRVALUE;
    }

    for (int i = 0; i < (*n); i++)
    {
        if (!strncmp(author, book_arr[i].author, AUTHORLEN))
        {
            deleted++;
            (*n)--;
            for (int j = i; j < (*n); j++)
            {
                book_arr[j] = book_arr[j + 1];
                key_arr[j][1] = key_arr[j + 1][1];
            }
            i--;
        }
    }
    return deleted;
}
