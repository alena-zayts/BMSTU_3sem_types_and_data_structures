#include "file.h"

int *file_read(FILE *f, long *final_amount)
{
    rewind(f);
    long amount = file_amount(f);
    if ((int) amount == ERRFILE)
        return NULL;

    long ind = 0;
    int value;
    int *numbers = malloc(sizeof(int) * amount);

    if (!numbers)
    {
        printf("MEMORY ERROR\n");
        return NULL;
    }

    while (fscanf(f, "%d", &value) == 1)
    {
        numbers[ind] = value;
        ind++;
    }

    rewind(f);
    *final_amount = amount;

    return numbers;
}

long file_amount(FILE *f)
{
    rewind(f);

    long amount = 0;
    int value;

    while (fscanf(f, "%d", &value) == 1)
        amount++;

    if ((fgetc(f) != EOF) || (amount == 0))
    {
        printf("ERROR! Incorrect value in file. Finishing...\n");
        return ERRFILE;
    }

    rewind(f);

    return amount;
}

int file_bytes(FILE *f)
{
    rewind(f);
    fseek(f, 0, SEEK_END);
    unsigned size = ftell(f);
    rewind(f);

    return size;
}
