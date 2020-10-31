#include "operations.h"

//сложение матриц в классическом представлении
int sum_usual(double **ptrs1, double **ptrs2, double ***ptrs_res, int n, int m, int64_t *time_sum_usual)
{
    int64_t start, stop;
    double **ptrs = NULL;
    ptrs = allocate_usual(n, m);

    if (ptrs != NULL)
    {
        start = tick();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ptrs[i][j] = ptrs1[i][j] + ptrs2[i][j];
        stop = tick();
        *time_sum_usual = stop - start;
    }
    else
        return ERRMEM;

    *ptrs_res = ptrs;
    return OK;
}

//сложение матриц в разреженном представлении
int sum_rare(int n, int amount1, int amount2, int *amount3_final,
             double *a1, int *aj1, int *ai1,
             double *a2, int *aj2, int *ai2,
             double **a3_final, int **aj3_final, int **ai3_final, int64_t *time_sum_rare)
{
    int rc = OK;
    int64_t start, stop;
    double *a3 = NULL;
    int *aj3 = NULL;
    int *ai3 = NULL;
    int amount3 = amount1 + amount2;
    //выделение памяти
    rc = allocate_rare(&a3, &aj3, &ai3, n, amount3);
    if (rc == OK)
    {
        int a1_beg_i, a2_beg_i, a3_beg_i = 0;
        int a1_end_i, a2_end_i;
        int a1_finished, a2_finished;

         //начало суммирования
         start = tick();

         for (int row = 0; row < n; row++) //суммируем по строкам
         {
            ai3[row] = -1;
            if ((ai1[row] == -1) && (ai2[row] == -1)) //строки в обеих матрицах пустые - итоговая пустая
                continue;
            else
            {
                //начала и концы строк в обеих матрицах
                a1_beg_i = ai1[row];
                a2_beg_i = ai2[row];
                a1_end_i = -1;
                a2_end_i = -1;
                a1_finished = (ai1[row] == -1) ? 1 : 0;
                a2_finished = (ai2[row] == -1) ? 1 : 0;

                if (!a1_finished) //строка в первой матрице непустая
                {
                    //конец строки в первой матрице
                    for (int next_row = row + 1; next_row < n; next_row++)
                    if (ai1[next_row] != -1)
                    {
                        a1_end_i = ai1[next_row] - 1;
                        break;
                    }
                    if (a1_end_i == -1)
                        a1_end_i = amount1 - 1;
                    }

                if (!a2_finished) //строка во второй матрице непустая
                {
                    //конец строки во второй матрице
                    for (int next_row = row + 1; next_row < n; next_row++)
                    if (ai2[next_row] != -1)
                    {
                        a2_end_i = ai2[next_row] - 1;
                        break;
                    }
                    if (a2_end_i == -1)
                        a2_end_i = amount2 - 1;
                }

                //только первая
                if ((!a1_finished) && (a2_finished))
                {
                    //итоговая строка начинается с текущего элемента и равна строке первой матрицы
                    ai3[row] = a3_beg_i;
                    while (a1_beg_i <= a1_end_i)
                    {
                        a3[a3_beg_i] = a1[a1_beg_i];
                        aj3[a3_beg_i] = aj1[a1_beg_i];
                        a3_beg_i++;
                        a1_beg_i++;
                    }
                }

                //только вторая
                else if ((a1_finished) && (!a2_finished))
                {
                    //итоговая строка начинается с текущего элемента и равна строке второй матрицы
                    ai3[row] = a3_beg_i;
                    while (a2_beg_i <= a2_end_i)
                    {
                        a3[a3_beg_i] = a2[a2_beg_i];
                        aj3[a3_beg_i] = aj2[a2_beg_i];
                        a3_beg_i++;
                        a2_beg_i++;
                    }
                }

                //обе
                else
                {
                    while ((!a1_finished) || !(a2_finished))
                    {
                        //надо складывать
                        if ((aj1[a1_beg_i] == aj2[a2_beg_i]) && (!a1_finished) && (!a2_finished))
                        {
                            a3[a3_beg_i] = a1[a1_beg_i] + a2[a2_beg_i];
                            aj3[a3_beg_i] = aj1[a1_beg_i];
                            a1_beg_i++;
                            a2_beg_i++;
                            if (fabs(a3[a3_beg_i] - 0) > EPS)//полуичили не ноль
                            {
                                if (ai3[row] == -1)
                                    ai3[row] = a3_beg_i;
                                a3_beg_i++;
                             }
                        }
                        //не надо складывать
                        else
                        {
                            //берем из первой матрицы
                            if (((aj1[a1_beg_i] < aj2[a2_beg_i]) && (!a1_finished) && (!a2_finished))
                                  || (a2_finished))
                            {
                                a3[a3_beg_i] = a1[a1_beg_i];
                                aj3[a3_beg_i] = aj1[a1_beg_i];
                                if (ai3[row] == -1)
                                    ai3[row] = a3_beg_i;
                                a3_beg_i++;
                                a1_beg_i++;
                             }
                             //берем из второй матрицы
                             else if (((aj1[a1_beg_i] > aj2[a2_beg_i]) && (!a1_finished) && (!a2_finished))
                                      || (a1_finished))
                             {
                                a3[a3_beg_i] = a2[a2_beg_i];
                                aj3[a3_beg_i] = aj2[a2_beg_i];
                                if (ai3[row] == -1)
                                    ai3[row] = a3_beg_i;
                                a3_beg_i++;
                                a2_beg_i++;
                             }
                        }
                        if (a1_beg_i > a1_end_i)
                            a1_finished = 1;
                        if (a2_beg_i > a2_end_i)
                            a2_finished = 1;
                    }
                }
            }
         }
         stop = tick();
         *time_sum_rare = stop - start;
         amount3 = a3_beg_i;
         *a3_final = a3;
         *ai3_final = ai3;
         *aj3_final = aj3;
         *amount3_final = amount3;
    }
    else
        return ERRMEM;
    return OK;
}

//перевод матрицы из классической формы в разреженную
int usual_to_rare(double **ptrs, int n, int m, int amount, double **a, int **ja, int **ia)
{
    int rc = OK;
    //выделение памяти
    rc = allocate_rare(a, ja, ia, n, amount);

    //начало преобразования
    if (rc == OK)
    {
        int i_tek = 0;
        int i_written;
        for (int i = 0; i < n; i++)
        {
            i_written = 0;
            for (int j = 0; j < m; j++)
            {
                if (fabs(ptrs[i][j] - 0) > EPS)
                {
                    (*a)[i_tek] = ptrs[i][j];
                    (*ja)[i_tek] = j;
                    if (!i_written)
                    {
                        i_written = 1;
                        (*ia)[i] = i_tek;
                    }
                    i_tek++;
                }
            }
            if (!i_written)
                (*ia)[i] = -1;
            }
    }
    else
        return ERRMEM;
    return OK;
}
