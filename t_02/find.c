#include "find.h"

//вывести список отечественной технической литературы по указанной отрасли
void show_dom_tech(book_struct book_arr[], int n)
{
    int flag = 0;
    char field[FIELDLEN + 1] = { 0 };

    printf("Input field (up to %d symbols): ", FIELDLEN);
    fflush(stdin);
    if (fgets(field, FIELDLEN + 2, stdin) == NULL)
    {
        printf("ERROR: couldn't read field\n");
        return;
    }
    if (field[0] == '\n')
    {
        printf("ERROR: couldn't read field\n");
        return;
    }
    else if (field[strlen(field) - 1] == '\n')
        field[strlen(field) - 1] = '\0';
    else
    {
        printf("ERROR: couldn't read field\n");
        return;
    }
    {
        if (field[strlen(field) - 1] == '\n')
            field[strlen(field) - 1] = '\0';

        for (int i = 0; i < n; i++)
        {
            if ((book_arr[i].type_l == 1) &&
                    !(strcmp(book_arr[i].type_l_inf.tech.field, field)) &&
                    (book_arr[i].type_l_inf.tech.origin == 1))
            {
                print_book(book_arr[i]);
                flag = 1;
            }
        }
        if (flag == 0)
            printf("ERROR: no such books found\n");
    }
}
