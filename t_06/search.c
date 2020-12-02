#include "search.h"

int search_tree(int to_find, tree_node root)
{
    int i = 0;
    tree_node *p = &root;

    while (p != NULL)
    {
        i++;
        if (p->value == to_find)
            return i;

        if (p->value > to_find)
            p = p->right;
        else
            p = p->left;
    }
    return NOT_FOUND;
}

double search_tree_av(tree_node root, int *numbers, unsigned long flen)
{
    uint64_t time = tick();
    for (unsigned long i = 0; i < flen; ++i)
    {
        search_tree(numbers[i], root);
    }
    time = tick() - time;

    return (double)time / flen;
}

int search_hashtable(int to_find, list_t *hash_list, int n, int (*hash)(int, int))
{
    int code = list_cmp(to_find, hash_list[hash(to_find, n)]);
    if (code > 0)
        return code;

    return NOT_FOUND;
}

double search_hashtable_av(list_t *hash_list, int n, int (*hash)(int, int),
                           int *numbers, unsigned long flen)
{
    uint64_t time = tick();
    for (unsigned long i = 0; i < flen; ++i)
    {
        search_hashtable(numbers[i], hash_list, n, hash);
    }
    time = tick() - time;

    return (double)time / flen;
}

int search_file(int to_find, FILE *f)
{
    rewind(f);

    int i = 0;
    int buf;

    while (fscanf(f, "%d\n", &buf) == 1)
    {
        i++;
        if (to_find == buf)
            return i;
    }

    return NOT_FOUND;
}

double search_file_av(FILE *f, int *numberss, unsigned long flen)
{
    uint64_t time = tick();
    for (unsigned long i = 0; i < flen; ++i)
    {
        search_file(numberss[i], f);
    }
    time = tick() - time;

    return (double)time / flen;
}
