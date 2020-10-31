#include "inputs.h"

//ввод из файла
int input_from_file(FILE *f, book_struct book_arr[], int *n)
{
    int i = 0;
    for (; !feof(f); i++)
    {
        if (i == AMOUNT)
        {
            printf("ERROR: too many records (> %d) were found in file", AMOUNT);
            return TOOMANY;
        }

        if (fgets(book_arr[i].author, AUTHORLEN + 1, f) == NULL)
        {
            printf("ERROR in values in file literature.txt: %d record, author surname\n", i);
            return ERRVALUE;
        }
        else if (book_arr[i].author[strlen(book_arr[i].author) - 1] == '\n')
            book_arr[i].author[strlen(book_arr[i].author) - 1] = '\0';

        if (fgets(book_arr[i].name, NAMELEN + 1, f) == NULL)
        {
            printf("ERROR in values in file literature.txt: %d record, book name\n", i);
            return ERRVALUE;
        }
        else if (book_arr[i].name[strlen(book_arr[i].name) - 1] == '\n')
            book_arr[i].name[strlen(book_arr[i].name) - 1] = '\0';

        if (fgets(book_arr[i].pub, PUBLEN + 1, f) == NULL)
        {
            printf("ERROR in values in file literature.txt: %d record, publishing house\n", i);
            return ERRVALUE;
        }
        else if (book_arr[i].pub[strlen(book_arr[i].pub) - 1] == '\n')
                    book_arr[i].pub[strlen(book_arr[i].pub) - 1] = '\0';

        if (fscanf(f, "%d\n", &(book_arr[i].pages)) != 1 || (book_arr[i].pages < MINPAGE)
               || (book_arr[i].pages > MAXPAGE))
        {
            printf("ERROR in values in file literature.txt: %d record, amount of pages\n", i);
            return ERRVALUE;
        }

        if ((fscanf(f, "%d\n", &(book_arr[i].type_l)) != 1)
                || (book_arr[i].type_l < 1)
                || (book_arr[i].type_l > 3))
        {
            printf("ERROR in values in file literature.txt: %d record, type of literature\n", i);
            return ERRVALUE;
        }

        if (book_arr[i].type_l == 1) //technical
        {
            if (fgets(book_arr[i].type_l_inf.tech.field, FIELDLEN + 1, f) == NULL)
            {
                printf("ERROR in values in file literature.txt: %d record, field\n", i);
                return ERRVALUE;
            }
            else if (book_arr[i].type_l_inf.tech.field[strlen(book_arr[i].type_l_inf.tech.field) - 1] == '\n')
                        book_arr[i].type_l_inf.tech.field[strlen(book_arr[i].type_l_inf.tech.field) - 1] = '\0';

            if ((fscanf(f, "%d\n", &(book_arr[i].type_l_inf.tech.origin)) != 1)
                    || (book_arr[i].type_l < 1)
                    || (book_arr[i].type_l > 2))
            {
                printf("ERROR in values in file literature.txt: %d record, origin\n", i);
                return ERRVALUE;
            }

            if ((fscanf(f, "%d\n", &(book_arr[i].type_l_inf.tech.year)) != 1)
                || (book_arr[i].type_l_inf.tech.year < MINYEAR)
                || (book_arr[i].type_l_inf.tech.year > MAXYEAR))
            {
                printf("ERROR in values in file literature.txt: %d record, year\n", i);
                return ERRVALUE;
            }
        }
        if (book_arr[i].type_l == 2) //fictional
            if ((fscanf(f, "%d\n", &(book_arr[i].type_l_inf.fict)) != 1)
                    || (book_arr[i].type_l_inf.fict < 1)
                    || (book_arr[i].type_l_inf.fict > 3))
            {
                printf("ERROR in values in file literature.txt: %d record, type of fictional\n", i);
                return ERRVALUE;
            }
        if (book_arr[i].type_l == 3) //childish
            if ((fscanf(f, "%d\n", &(book_arr[i].type_l_inf.child)) != 1)
                || (book_arr[i].type_l_inf.fict < 1)
                || (book_arr[i].type_l_inf.fict > 2))
            {
                printf("ERROR in values in file literature.txt: %d record, type of childish\n", i);
                return ERRVALUE;
            }
    }
    if (i > 0)
    {
        *n = i;
        return OK;
    }
    else
    {
        printf("ERROR: file literature.txt is empty\n");
        return ERREMPTY;
    }
}

//добавление в таблицу одной записи
int add_one(book_struct book_arr[], int key_arr[][2], int n)
{
    if (n == AMOUNT)
    {
        printf("ERROR: will get more than %d records\n", AMOUNT);
        return TOOMANY;
    }
    printf("Input author surname (up to %d symbols): ", AUTHORLEN);
    fflush(stdin);
    if (fgets(book_arr[n].author, AUTHORLEN + 2, stdin) == NULL)
    {
        printf("ERROR: couldn't read author surname\n");
        return ERRVALUE;
    }
    if (book_arr[n].author[0] == '\n')
    {
        printf("ERROR: couldn't read author surname\n");
        return ERRVALUE;
    }
    else if (book_arr[n].author[strlen(book_arr[n].author) - 1] == '\n')
        book_arr[n].author[strlen(book_arr[n].author) - 1] = '\0';
    else
    {
        printf("ERROR: couldn't read author surname\n");
        return ERRVALUE;
    }
    printf("Input book name (up to %d symbols): ", NAMELEN);
    fflush(stdin);
    if (fgets(book_arr[n].name, NAMELEN + 2, stdin) == NULL)
    {
        printf("ERROR: couldn't read book name\n");
        return ERRVALUE;
    }
    if (book_arr[n].name[0] == '\n')
    {
        printf("ERROR: couldn't read book name\n");
        return ERRVALUE;
    }
    else if (book_arr[n].name[strlen(book_arr[n].name) - 1] == '\n')
        book_arr[n].name[strlen(book_arr[n].name) - 1] = '\0';
    else
    {
        printf("ERROR: couldn't read book name\n");
        return ERRVALUE;
    }

    printf("Input publishing house (up to %d symbols): ", PUBLEN);
    fflush(stdin);
    if (fgets(book_arr[n].pub, PUBLEN + 2, stdin) == NULL)
    {
        printf("ERROR: couldn't read publishing house\n");
        return ERRVALUE;
    }
    if (book_arr[n].pub[0] == '\n')
    {
        printf("ERROR: couldn't read publishing house\n");
        return ERRVALUE;
    }
    else if (book_arr[n].pub[strlen(book_arr[n].pub) - 1] == '\n')
                book_arr[n].pub[strlen(book_arr[n].pub) - 1] = '\0';
    else
    {
        printf("ERROR: couldn't read publishing house\n");
        return ERRVALUE;
    }

    printf("Input number of pages (from %d to %d): ", MINPAGE, MAXPAGE);
    fflush(stdin);
    if (fscanf(stdin, "%d", &(book_arr[n].pages)) != 1 || (book_arr[n].pages < MINPAGE)
           || (book_arr[n].pages > MAXPAGE) || ('\n' != getchar()))
    {
        printf("ERROR: couldn't read amount of pages\n");
        return ERRVALUE;
    }

    printf("1 - technical, 2 - fiction, 3 - childish\n");
    printf("Input type of literature (1 or 2 or 3): ");
    fflush(stdin);
    if ((fscanf(stdin, "%d", &(book_arr[n].type_l)) != 1)
            || (book_arr[n].type_l < 1)
            || (book_arr[n].type_l > 3) || ('\n' != getchar()))
    {
        printf("ERROR: couldn't read type of literature\n");
        return ERRVALUE;
    }

    if (book_arr[n].type_l == 1) //technical
    {
        printf("Input field (up to %d symbols): ", FIELDLEN);
        fflush(stdin);
        if (fgets(book_arr[n].type_l_inf.tech.field, FIELDLEN + 2, stdin) == NULL)
        {
            printf("ERROR: couldn't read field\n");
            return ERRVALUE;
        }
        if (book_arr[n].type_l_inf.tech.field[0] == '\n')
        {
            printf("ERROR: couldn't read field\n");
            return ERRVALUE;
        }
        else if (book_arr[n].type_l_inf.tech.field[strlen(book_arr[n].type_l_inf.tech.field) - 1] == '\n')
            book_arr[n].type_l_inf.tech.field[strlen(book_arr[n].type_l_inf.tech.field) - 1] = '\0';
        else
        {
            printf("ERROR: couldn't read field\n");
            return ERRVALUE;
        }

        printf("1 - domestic, 2 - translated\n");
        printf("Input origin (1 or 2): ");
        fflush(stdin);
        if ((fscanf(stdin, "%d", &(book_arr[n].type_l_inf.tech.origin)) != 1)
                || (book_arr[n].type_l_inf.tech.origin < 1)
                || (book_arr[n].type_l_inf.tech.origin > 2) || ('\n' != getchar()))
        {
            printf("ERROR: couldn't read origin\n");
            return ERRVALUE;
        }

        printf("Input year of publishing (from %d to %d): ", MINYEAR, MAXYEAR);
        fflush(stdin);
        if ((fscanf(stdin, "%d", &(book_arr[n].type_l_inf.tech.year)) != 1)
            || (book_arr[n].type_l_inf.tech.year < MINYEAR)
            || (book_arr[n].type_l_inf.tech.year > MAXYEAR) || ('\n' != getchar()))
        {
            printf("ERROR: couldn't read year\n");
            return ERRVALUE;
        }
    }
    if (book_arr[n].type_l == 2) //fictional
    {
        printf("1 - novel, 2 - play, 3 - poems\n");
        printf("Input type of fictional literature (1 or 2 or 3): ");
        fflush(stdin);
        if ((fscanf(stdin, "%d", &(book_arr[n].type_l_inf.fict)) != 1)
                || (book_arr[n].type_l_inf.fict < 1)
                || (book_arr[n].type_l_inf.fict > 3) || ('\n' != getchar()))
        {
            printf("ERROR: couldn't read type of fictional\n");
            return ERRVALUE;
        }
    }
    if (book_arr[n].type_l == 3) //childish
    {
        printf("1 - fairytale, 2 - poems\n");
        printf("Input type of childish literature (1 or 2): ");
        fflush(stdin);
        if ((fscanf(stdin, "%d", &(book_arr[n].type_l_inf.child)) != 1)
            || (book_arr[n].type_l_inf.child < 1)
            || (book_arr[n].type_l_inf.child > 2) || ('\n' != getchar()))
        {
            printf("ERROR: couldn't read type of childish\n");
            return ERRVALUE;
        }
    }
    key_arr[n][0] = n;
    key_arr[n][1] = book_arr[n].pages;
    return OK;
}

//ввод собственного списка литературы
int input_my(book_struct book_arr[], int key_arr[][2], int *n)
{
    int rc;
    printf("How many records will be in your list (up to %d)?\n", AMOUNT);
    if ((scanf("%d", n) != 1) || (*n < 1) || (*n > AMOUNT) || (getchar() != '\n'))
    {
        printf("ERROR: incorrect amount\n");
        return TOOMANY;
    }
    for (int i = 0; i < *n; i++)
    {
        rc = add_one(book_arr, key_arr, i);
        if (rc == ERRVALUE)
        {
            printf("This record wasn't added. Try to input it one more time\n");
            i--;
        }
        else
            printf("\nThis record was successfully added\n");
    }
    return OK;
}

//заполнение таблицы ключей
void fill_key_arr(book_struct book_arr[], int key_arr[][2], int n)
{
    for (int i = 0; i < n; i++)
    {
        key_arr[i][0] = i;
        key_arr[i][1] = book_arr[i].pages;
    }
}

