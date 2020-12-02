#include "hash.h"

int is_simple(unsigned int num)
{
    for (long long i = 2; i <= sqrt(num); i++)
        if (num % i == 0)
            return 0;
    return 1;
}

unsigned int next_simple(int n)
{
    unsigned int next = n + 1;
    while (!is_simple(next))
    {
        next++;
    }

    return next;
}

//остаток от деления
int del_hash(int value, int n)
{
    return value % n;
}

//Метод середины квадрата
int square_mid_hash(int value, int n)
{
    value *= value;
    long long mid = (value>>2) & 0xffff; //16 срединных бит
    return mid % n;
}


int hash_create_table(list_t **arr, int size, FILE *f, int (*hash)(int, int))
{
    int buf;
    int max_collisions = 0;

    rewind(f);
    while (fscanf(f, "%d", &buf) == 1)
    {
        int cur_collisions = 0;

        if (list_cmp(buf, (*arr)[hash(buf, size)]) == 0)
            cur_collisions = list_insert(&(*arr)[hash(buf, size)], buf);
        if (cur_collisions > max_collisions)
            max_collisions = cur_collisions;
    }
    return max_collisions;
}

void hash_print_table(list_t *arr, int size)
{
    printf("\n------------------------------------------\n"
           " HASH | DATA \n"
           "------------------------------------------\n");
    list_t *entry;

    int flag;

    for (int i = 0; i < size; i++)
    {
        flag = 0;

        entry = &arr[i];
        if (entry->value != 0)
        {
            printf("%5d | ", i);
            flag = 1;
        }
        while (entry != NULL)
        {
            if (entry->value != 0)
                printf("%d ", entry->value);
            entry = entry->next;
        }
        if (flag)
            printf("\n------------------------------------------\n");
    }
}
