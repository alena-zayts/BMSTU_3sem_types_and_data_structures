#include "outputs.h"

//вывод матрицы в двух представлениях (если возможно)
void output_matrix(const char *s, double **ptrs, int n, int m, double *a, int *aj, int *ai, int amount)
{
    printf("\n%s\n", s);
    if ((n <= MAXNSHOWN) && (m <= MAXNSHOWN))
    {
        printf("IN USUAL FORMAT:\n");
        output_usual(ptrs, n, m);
    }
    printf("IN SPECIAL FORMAT:\n");
    output_rare(a, aj, ai, amount, n);
}

//вывод матрицы в классическом представлении
void output_usual(double **ptrs, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < m; j++)
            printf(" %3.1lf |", ptrs[i][j]);
        printf("\n");
    }
}
//вывод матрицы в разреженном представлении
void output_rare(double *a, int *aj, int *ai, int amount, int n)
{
    int repeats = ((n - 1)/MAXNSHOWN) + 1;
    for (int i_repeat = 0; i_repeat < repeats; i_repeat++)
    {
        printf("\n");
        printf("i:  |");
        for (int i = (i_repeat*MAXNSHOWN); (i < (i_repeat + 1)*MAXNSHOWN) && ((i < n) || (i < amount)); i++)
            printf("%3d |", i);
        printf("\n");

        printf("a:  |");
        for (int i = (i_repeat*MAXNSHOWN); (i < (i_repeat + 1)*MAXNSHOWN) && (i < amount); i++)
            printf("%3.1lf |", a[i]);
        printf("\n");

        printf("aj: |");
        for (int i = (i_repeat*MAXNSHOWN); (i < (i_repeat + 1)*MAXNSHOWN) && (i < amount); i++)
            printf("%3d |", aj[i]);
        printf("\n");

        printf("ai: |");
        for (int i = (i_repeat*MAXNSHOWN); (i < (i_repeat + 1)*MAXNSHOWN) && ((i < n)); i++)
            printf("%3d |", ai[i]);
        printf("\n");
    }
}
