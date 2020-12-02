#include "main_header.h"
#include "io.h"
#include "tick.h"
#include "file.h"
#include "tree.h"
#include "list.h"
#include "hash.h"
#include "search.h"
#include "tick.h"

int main(int argc, char *argv[])
{
    welcome();
    //checking
    if (argc != 2)
    {
        printf("ERROR! Expected: app.exe file_name.txt. Finishing...\n");
        return ERRPARAM;
    }

    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
    {
        printf("ERROR! Can't open file. Finishing...\n");
        return ERRFILE;
    }

    if (fgetc(f) == EOF)
    {
        printf("ERROR! File is empty. Finishing...\n");
        return ERRFILE;
    }
    rewind(f);

    long amount;
    int *numbers = file_read(f, &amount);
    if (numbers == NULL)
        return ERRFILE;

    //start

    tree_node *root = NULL;

    uint64_t time = tick();

    tree_create(&root, f);
    time = tick() - time;

    printf("BINARY SEARCH TREE BASED ON FILE:\n");
    tree_print(root, 0);
    printf("Tree was built by = %llu ticks.\n\n" , time);

    int unique;
    time = tick();
    root = tree_balance(root, &unique);
    time = tick() - time;
    printf("BINARY SEARCH TREE AFTER BALANCING:\n");
    tree_print(root, 0);
    printf("Tree was balanced by = %llu ticks.\n\n" , time);

    int n = next_simple(file_amount(f));
    list_t *hash_list = calloc(n, sizeof(list_t));
    if (!hash_list)
    {
        printf("MEMORY ERROR!\n");
        return ERRMEM;
    }

    int cmpr, desired_cmpr;
    int (*hash)(int, int);

    time = tick();
    del_hash(123456, n);
    time = tick() - time;
    printf("Generating hash by remainder of division by %d: %llu.\n", n, time);

    time = tick();
    square_mid_hash(123456, 10);
    time = tick() - time;
    printf("Generating hash by mid square:            %llu.\n", time);

    hash = &del_hash;
    time = tick();
    cmpr = hash_create_table(&hash_list, n, f, hash);
    time = tick() - time;

    printf("\nHASH-TABLE BASED ON REMAINDER OF DIVISION:\n");
    hash_print_table(hash_list, n);
    printf("maximum amount of comparisons: %d.\n", cmpr);
    printf("Table was built by = %llu ticks.\n\n" , time);

    printf("Input maximum amount of comparisons in hash-table (>=1):\n");
    fflush(stdin);
    while ((scanf("%d", &desired_cmpr) != 1) || (desired_cmpr < 1))
    {
        printf("Incorrect value! Try again:\n");
        fflush(stdin);
    }

    if ((cmpr) > desired_cmpr)
    {
        //while ((cmpr) > desired_cmpr)
        {
            printf("rebuilding...\n");
            free_list_arr(hash_list, n);
            n = next_simple(n);
            hash_list = calloc(n, sizeof(list_t));
            if (!hash_list)
                printf("MEMORY ERROR! Finishing...\n");

            hash = &square_mid_hash;
            time = tick();
            cmpr = hash_create_table(&hash_list, n, f, hash);
            time = tick() - time;
        }
        printf("\nHASH-TABLE BASED ON MID SQUARE:\n");
        hash_print_table(hash_list, n);
        printf("Maximum amount of comparisons %d.\n", cmpr);
        printf("Table was built by = %llu ticks.\n\n" , time);
    }
    else
        printf("Don't need to rebuild the table\n");

    int to_find;
    printf("\nInput the number to find:\n");
    fflush(stdin);
    while (scanf("%d", &to_find) != 1)
    {
        printf("Incorrect value! Try again:\n");
        fflush(stdin);
    }

    int depth = 0;
    int vrtxs = 0;
    int cmprs = 0;
    tree_node *root2 = NULL;
    int found;
    tree_create(&root2, f);
    time = tick();
    found = search_tree(to_find, *root2);
    time = tick() - time;
    tree_depth(root2, &vrtxs, &cmprs, depth);
    printf("\nSEARCH IN BINARY SEARCCH TREE\n");
    if (found > 0)
    {
        printf("Number %d was found by:        %llu ticks.\n"
               "Average search time:           %lf ticks.\n"
               "Memory usage:                  %llu bytes.\n"
               "Amount of comparisons:         %d.\n"
               "Average amount of comparisons: %f.\n",
               to_find, time, search_tree_av(*root2, numbers, amount),
               unique * sizeof(tree_node), found,
               (double)cmprs / vrtxs);
    }
    else
    {
        printf("Number %d was not found.\n", to_find);
    }
    tree_free(root2);

    depth = 0;
    vrtxs = 0;
    cmprs = 0;
    time = tick();
    found = search_tree(to_find, *root);
    time = tick() - time;
    tree_depth(root, &vrtxs, &cmprs, depth);
    printf("\nSEARCH IN BALANCED BINARY SEARCCH TREE\n");
    if (found > 0)
    {
        printf("Number %d was found by:        %llu ticks.\n"
               "Average search time:           %lf ticks.\n"
               "Memory usage:                  %llu bytes.\n"
               "Amount of comparisons:         %d.\n"
               "Average amount of comparisons: %f.\n",
               to_find, time, search_tree_av(*root2, numbers, amount),
               unique * sizeof(tree_node), found,
               (double)cmprs / vrtxs);
    }
    else
    {
        printf("Number %d was not found.\n", to_find);
    }
    tree_free(root);

    time = tick();
    found = search_hashtable(to_find, hash_list, n, hash);
    time = tick() - time;
    printf("\nSEARCH IN HASH-TABLE\n");
    if (found > 0)
    {
        printf("Number %d was found by:        %llu ticks.\n"
               "Average search time:           %lf ticks.\n"
               "Memory usage:                  %llu bytes.\n"
               "Amount of comparisons:         %d.\n"
               "Average amount of comparisons: %f.\n",
               to_find, time / 4, search_hashtable_av(hash_list, n, hash, numbers, amount),
               (n + unique - list_occupation(hash_list, n)) * sizeof(list_t) + sizeof(list_t *), found,
               (double)(1 + desired_cmpr) / 2);
    }
    else
    {
        printf("Number %d was not found.\n", to_find);
    }
    free_list_arr(hash_list, n);

    time = tick();
    found = search_file(to_find, f);
    time = tick() - time;
    printf("\nSEARCH IN FILE\n");
    if (found > 0)
    {
        printf("Number %d was found by:        %llu ticks.\n"
               "Average search time:           %lf ticks.\n"
               "Memory usage:                  %d bytes.\n"
               "Amount of comparisons:         %d.\n"
               "Average amount of comparisons: %f.\n",
               to_find, time, search_file_av(f, numbers, amount),
               file_bytes(f), found, (double)file_amount(f) / 2);
    }
    else
    {
        printf("Number %d was not found.\n", to_find);
    }

    fclose(f);

    return OK;
}
