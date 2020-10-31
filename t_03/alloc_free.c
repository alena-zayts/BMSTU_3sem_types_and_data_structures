#include "alloc_free.h"

//выделение памяти под матрицу в классическом представлении
double **allocate_usual(int n, int m)
{
    double **ptrs, *data;

    ptrs = calloc(n, sizeof(double*));
    if (ptrs == NULL)
        return NULL;

    data = calloc(n * m, sizeof(double));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }

    for (int i = 0; i < n; i++)
        ptrs[i] = data + i * m;

    return ptrs;
}
//освобождение памяти из под матрицы в классическом представлении
void free_usual(double **ptrs)
{
    free(ptrs[0]);
    free(ptrs);
}

//выделение памяти под матрицу в разреженном представлении
int allocate_rare(double **a, int**aj, int **ai, int n, int amount)
{
    *a = calloc(amount, sizeof(double));
    if ((*a) != NULL)
    {
        *aj = calloc(amount, sizeof(int));
        if ((*aj) != NULL)
        {
            *ai = calloc(n, sizeof(int));
            if ((*ai) != NULL)
                return OK;
            else
            {
                free(*a);
                free(*aj);
                return ERRMEM;
            }
        }
        else
        {
            free(*a);
            return ERRMEM;
        }
    }
    else
        return ERRMEM;
}
//освобождение памяти из под матрицы в разреженном представлении
void free_rare(double *a, int *aj, int *ai)
{
    free(a);
    free(aj);
    free(ai);
}
