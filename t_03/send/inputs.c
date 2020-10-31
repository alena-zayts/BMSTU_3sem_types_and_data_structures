#include "inputs.h"

//реализация всего ввода
int input_all(int *n, int*m, double ***ptrs1, int *amount1, double ***ptrs2, int *amount2)
{
    int num_elems;
    int mode = 0;
    int rc = OK;

    //ввод n и m
    input_nm(n, m);

    //выделение памяти
    *ptrs1 = allocate_usual(*n, *m);
    if (*ptrs1 != NULL)
    {
        *ptrs2 = allocate_usual(*n, *m);
        if (*ptrs2 != NULL)
        {
            //ВВОД 1 МАТРИЦЫ
            //количсетво ненулевых элементов в 1 матрице
            printf("How many nonnull elements will be in first matrix (from 0 to %d): ", (*n)*(*m));
            fflush(stdin);
            while ((fscanf(stdin, "%d", &num_elems) != 1) ||
                   (num_elems < 0) || (num_elems > (*n)*(*m)) || (getchar() != '\n'))
            {
                printf("ERROR: incorrect amount nonnull elements. Try again: ");
                fflush(stdin);
            }
            *amount1 = num_elems;
            if (num_elems > 0)
            {
                //выбор режима ввода первой матрицы
                printf("Choose input mode: 0 - for automatically, 1 - for manually: ");
                fflush(stdin);
                while ((fscanf(stdin, "%d", &mode) != 1) || (mode < 0) || (mode > 1) || (getchar() != '\n'))
                {
                    printf("ERROR: incorrect mode. Try again: ");
                    fflush(stdin);
                }
            }
            //ввод
            if (mode == 0)
            {
                rc = input_automatically(*n, *m, num_elems, *ptrs1);
                if (rc == OK)
                    printf("Input is finished.\n"
                           "Successfully added %d nonnul elements of matrix\n\n", num_elems);
            }
            else
                input_manually(*ptrs1, *n, *m, num_elems);

            if (rc == OK)
            {
                //ВВОД 2 МАТРИЦЫ
                //количсетво ненулевых элементов в 2 матрице
                printf("How many nonnull elements will be in second matrix (from 0 to %d): ", (*n)*(*m));
                fflush(stdin);
                while ((fscanf(stdin, "%d", &num_elems) != 1)
                       || (num_elems < 0) || (num_elems > (*n)*(*m)) || (getchar() != '\n'))
                {
                    printf("ERROR: incorrect amount nonnull elements. Try again: ");
                    fflush(stdin);
                }
                *amount2 = num_elems;
                mode = 0;
                if (num_elems > 0)
                {
                    //выбор режима ввода второй матрицы
                    printf("Choose input mode: 0 - for automatically, 1 - for manually: ");
                    fflush(stdin);
                    while ((fscanf(stdin, "%d", &mode) != 1) || (mode < 0) || (mode > 1) || (getchar() != '\n'))
                    {
                        printf("ERROR: incorrect mode. Try again: ");
                        fflush(stdin);
                    }
                }
                //ввод
                if (mode == 0)
                {
                    rc = input_automatically(*n, *m, num_elems, *ptrs2);
                    if (rc == OK)
                        printf("Input is finished.\n"
                               "Successfully added %d nonnul elements of matrix\n\n", num_elems);
                }
                else
                    input_manually(*ptrs2, *n, *m, num_elems);
            }  
            //освобождение уже выделенной памяти в случае ошибок
            if (rc != OK)
            {
                free_usual(*ptrs1);
                free_usual(*ptrs2);
            }
        }
        else
        {
            free_usual(*ptrs1);
            rc = ERRMEM;
        }
    }
    else
        rc = ERRMEM;
    return rc;
}

//ввод размерности матриц
void input_nm(int *n, int *m)
{
    printf("Input number of rows n (int, >= 1): ");
    fflush(stdin);
    while ((fscanf(stdin, "%d", n) != 1) || (*n < 1) || (getchar() != '\n'))
    {
        printf("ERROR: incorrect n. Try again: ");
        fflush(stdin);
    }
    printf("Input number of columns m (int, >= 1): ");
    fflush(stdin);
    while ((fscanf(stdin, "%d", m) != 1) || (*m < 1) || (getchar() != '\n'))
    {
        printf("ERROR: incorrect m. Try again\n");
        fflush(stdin);
    }
}

//создание массива случайных позиций
void random_array(int *arr, int n)
{
    // инициализация генератора случайных чисел
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = i;
    // реализация алгоритма перестановки
    for (int i = n - 1; i >= 1; i--)
    {
        int j = rand() % (i + 1);

        int tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;
    }
}

//автоматический ввод матрицы
int input_automatically(int n, int m, int amount, double **ptrs)
{
    int *index = NULL;
    int row, col;

    index = calloc((n * m), sizeof(int));
    if (index != NULL)
    {
        random_array(index, n*m);
        //заполняем случайными числами матрицу
        for (int i = 0; i < amount; i++)
        {
            row = index[i]/m;
            col = index[i]%m;
            ptrs[row][col] = ((rand() % 10) + 0.1)*pow(-1, row+col);
        }
        free(index);
    }
    else
        return ERRMEM;
    return OK;
}

//ручной ввод матрицы
void input_manually(double **ptrs, int n, int m, int num_elems)
{
    int rc = OK;
    int i, j;
    double elem;
    FILE *f = stdin;

    printf("\nInput %d nonnull elements of matrix in coordinate format: \"i j value\", where:\n"
           "-- i - number of row (int, 0 <= i <= %d)\n"
           "-- j - number of column (int, 0 <= j <= %d)\n"
           "-- value - value of elemnt (real, |value - 0| > %lf)\n", num_elems, n - 1, m - 1, EPS);
    printf("1 element in one row\n");
    printf("i j value\n\n");

    for (int k = 0; k < num_elems; k++)
    {
        rc = OK;
        printf("Input element number %d:\n", k + 1);
        fflush(stdin);
        if ((fscanf(f, "%d%d%lf", &i, &j, &elem) != 3) || (getchar() != '\n'))
        {
            printf("ERROR: can't read this row. Try to input current element again\n");
            rc = ERRVALUE;
        }
        else if ((i < 0) || (i >= n))
        {
            printf("ERROR: incorrect number of row. Try to input current element again\n");
            rc = ERRVALUE;
        }
        else if ((j < 0) || (j >= m))
        {
            printf("ERROR: incorrect number of column. Try to input current element again\n");
            rc = ERRVALUE;
        }
        else if (fabs((ptrs)[i][j] - 0) > EPS)
        {
            printf("ERROR: an element to this posission was already added. Try to input current element again\n");
            rc = ERRVALUE;
        }
        else if (fabs(elem - 0) < EPS)
        {
            printf("ERROR: this element can't be null (or too close to null). Try to input current element again\n");
            rc = ERRVALUE;
        }
        if (rc == ERRVALUE)
            k--;
        else
        {
            ptrs[i][j] = elem;
            printf("Successfully added.\n");
        }
    }
    printf("Input is finished.\n Successfully added %d nonnul elements of matrix\n\n", num_elems);
}

