#include "main_header.h"
#include "show_info.h"
#include "inputs.h"
#include "outputs.h"
#include "deletes.h"
#include "find.h"
#include "sort.h"
#include "compare.h"

int main(void)
{
    FILE *f;
    int rc = OK;

    int n = 0;
    book_struct book_arr[AMOUNT];
    memset(&book_arr, 0, sizeof(book_struct));
    int key_arr[AMOUNT][2] = { 0 };

    char command[COMMANDLEN];

    setbuf(stdout, NULL);
    show_main_information();
    show_commands();

    //commands execution until exit
    while (1)
    {
        //input command
        printf("\n$ ");
        fflush(stdin);
        if ((fgets(command, COMMANDLEN + 1, stdin) != NULL))
        {
            if (command[strlen(command) - 1] == '\n')
                command[strlen(command) - 1] = '\0';

            //commands execution

            // show information about the program and a list of possible commands
            if ((strcmp(command, "help") == 0))
            {
                show_main_information();
                show_commands();
                continue;
            }

            // show the information about the range of input values
            if ((strcmp(command, "how") == 0))
            {
                show_main_information();
                continue;
            }

            //show the amount of records in the existing literature list
            if ((strcmp(command, "amount") == 0))
            {
                printf("The existing list of literature contains %d records\n", n);
                continue;
            }

            //clean the existing in the program list of literature and key table
            if ((strcmp(command, "clean") == 0))
            {
                if (n == 0)
                    printf("ERROR: don't have an existing list of literature yet\n");
                else
                    n = 0;
                continue;
            }

            // delete records by a value of author surname
            if (!(strcmp(command, "delete")))
            {
                if (n == 0)
                    printf("ERROR: don't have an existing list of literature yet\n");
                else
                {
                    rc = delte_by_surname(book_arr, key_arr, &n);
                    if (rc > 0)
                        printf("Deleted %d records. %d records are left in the list\n", rc, n);
                    else if (rc == 0)
                        printf("ERROR: no one match was found\n");
                }
                continue;
            }

            //import the prepared list of literature from file literature.txt
            if (!(strcmp(command, "input_prepared")))
            {
                if (n != 0)
                    printf("ERROR: first clean the existing in the program\n"
                           "list of literature and key table by command \"clean\"\n");
                else
                {
                    f = fopen("literature.txt", "r");
                    if (f)
                    {
                        rc = input_from_file(f, book_arr, &n);
                        if (rc == OK)
                        {
                            fill_key_arr(book_arr, key_arr, n);
                            printf("Successfully read %d elements of list\n", n);
                        }
                        else
                            n = 0;
                        fclose(f);
                    }
                    else
                        printf("ERROR: couldn't open literature.txt\n");
                }
                continue;
            }

            // input your own list of literature
            if (!(strcmp(command, "input_my")))
            {
                if (n != 0)
                    printf("ERROR: first clean the existing in the program\n"
                           "list of literature and key table by command \"clean\"\n");
                else
                {
                    rc = input_my(book_arr, key_arr, &n);
                    if (rc == OK)
                        printf("%d records were successfully added\n", n);
                    else
                        n = 0;
                }
                continue;
            }

            //add one book to the end of the existing list of literature
            if (!(strcmp(command, "input_one")))
            {
                if (n == 0)
                    printf("ERROR: don't have an existing list of literature yet\n");
                else
                {
                    rc = add_one(book_arr, key_arr, n);
                    if (rc == OK)
                    {
                        n++;
                        printf("This record was successfully added\n");
                    }
                }
                continue;
            }

            //show a comparative table of the efficiency of using
            //different sorting algoriythms and approaches
            if (!(strcmp(command, "show_compare")))
            {
                rc = compare();
                if (rc != OK)
                    printf("ERROR: couldn't execute \"show_compare\"\n");
                continue;
            }

            //show the list of domestic technical literature on the specified field
            if (!(strcmp(command, "show_tech")))
            {
                if (n == 0)
                    printf("ERROR: the current table of keys is empty\n");
                else
                    show_dom_tech(book_arr, n);
                continue;
            }

            //show the current state of the table of keys
            if (!(strcmp(command, "show_key_table")))
            {
                if (n == 0)
                    printf("ERROR: the current table of keys is empty\n");
                else
                {
                    printf("Current table of keys\n");
                    print_keys(key_arr, n);
                }
                continue;
            }

            //show the current state of the list of literature
            if (!(strcmp(command, "show_main_table")))
            {
                if (n == 0)
                    printf("ERROR: the current list of literature is empty\n");
                else
                {
                    printf("Current list of literature\n");
                    print_books(book_arr, n);
                }
                continue;
            }

            //sort and show the list of literature by inc. of number of pages using "bubble" algorythm
            if (!(strcmp(command, "sort_main_bubble")))
            {
                if (n == 0)
                    printf("ERROR: the current list of literature is empty\n");
                else
                {
                    sort_books_bubble(book_arr, n);
                    fill_key_arr(book_arr, key_arr, n);
                    printf("Current list of literature\n");
                    print_books(book_arr, n);
                }
                continue;
            }

            //sort and show the list of literature by inc. of number of pages using "quick" algorythm
            if (!(strcmp(command, "sort_main_quick")))
            {
                if (n == 0)
                    printf("ERROR: the current list of literature is empty\n");
                else
                {
                    qsort(book_arr, n, sizeof(book_struct), struct_cmp);
                    fill_key_arr(book_arr, key_arr, n);
                    printf("Current list of literature\n");
                    print_books(book_arr, n);
                }
                continue;
            }

            //show the list of literature in sorted form by sorting key table by inc. of
            // number of pages using "bubble" algorythm
            if (!(strcmp(command, "sort_key_bubble")))
            {
                if (n == 0)
                    printf("ERROR: the current list of literature is empty\n");
                else
                {
                    sort_keys_bubble(key_arr, n);
                    printf("Current table of keys\n");
                    print_keys(key_arr, n);
                    printf("form of list of literature\n");
                    print_books_by_keys(book_arr, key_arr, n);
                }
                continue;
            }

            //show the list of literature in sorted form by sorting key table by inc. of
            // number of pages using "quick" algorythm
            if (!(strcmp(command, "sort_key_quick")))
            {
                if (n == 0)
                    printf("ERROR: the current list of literature is empty\n");
                else
                {
                    qsort(key_arr, n, sizeof(int) * 2, int2_cmp);
                    printf("Current table of keys\n");
                    print_keys(key_arr, n);
                    printf("form of list of literature\n");
                    print_books_by_keys(book_arr, key_arr, n);
                }
                continue;
            }

            //exit the program
            if (!(strcmp(command, "exit")))
                break;

            //unknown command
            printf("ERROR: unknown command\n");
            show_commands();
        }
    }
    printf("\nExited the program\n");
    return OK;
}

