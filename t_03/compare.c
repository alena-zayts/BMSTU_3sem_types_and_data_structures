#include "compare.h"

//подсчет числа тактов процессора
int64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

//вывод сравнительной таблицы для конкретного случая
void show_compare_1(int64_t time_sum_usual, int64_t time_sum_rare, size_t mem_usual, size_t mem_rare)
{
    printf("\nA comparative table of memory and time usage (for these two approaches)\n"
           "for this exact example:\n\n");
    printf("------------------------------------\n");
    printf("|      |      time     |   memory  \n");
    printf("|------|---------------|-----------\n");
    printf("|usual |  %6I64u ticks | %6d bytes \n", time_sum_usual, (int) mem_usual);
    printf("|------|---------------|-----------\n");
    printf("|rare  |%3.2lf%% of usual|%3.2lf%% of usual\n", (double) 100*time_sum_rare/time_sum_usual,
           (double) 100*mem_rare/mem_usual);
    printf("|------|---------------|-----------\n");
    printf("\nCPU of my computer: 2.30 GHz\n");
}

//эта функция не используется в основной программе, а служит для сравнения эффективностей (см. отчет)
//вывод сравнительной таблицы для матрицы размерностью n*n с различным процентом заполненности:
//от a до b с шагом step
int show_compare_n(int n, int a, int b, int step)
{
    double **ptrs1 = NULL;
    int amount1 = 0;
    double *a1 = NULL;
    int *aj1 = NULL;
    int *ai1 = NULL;

    double **ptrsr = NULL;
    int amountr = 0;
    double *ar = NULL;
    int *ajr = NULL;
    int *air = NULL;

    int64_t time_usual_1, time_usual_total;
    size_t mem_usual = (3*n*n)*sizeof(double) + (3*n)*sizeof(double*);
    int64_t time_rare_1, time_rare_total;
    size_t mem_rare = 0;
    int repeats = 10;
    if (n > 100)
        repeats = 1;

    ptrs1 = allocate_usual(n, n);
    if (ptrs1 == NULL)
        return ERRMEM;

    printf("\n\nComparative_table for matrix %dx%d\n", n, n);
    printf("Counted mean time for %d repeats\n", repeats);
    printf("%% nonnul |mem_usual, bytes|mem_rare, %%of usual|time_usual, ticks|time_rare, %%of usual\n");
    for (int percent = a; percent <= b; percent+=step)
    {
        time_rare_total = 0;
        time_usual_total = 0;
        mem_rare = 0;
        amount1 = n*n*percent/100;
        for (int repeat = 0; repeat < repeats; repeat++)
        {
            if ((input_automatically(n, n, amount1, ptrs1) != OK) ||
                    (usual_to_rare(ptrs1, n, n, amount1, &a1, &aj1, &ai1) != OK))
            {
                free_usual(ptrs1);
                return ERRMEM;
            }
            if ((sum_rare(n, amount1, amount1, &amountr, a1, aj1, ai1,
                          a1, aj1, ai1, &ar, &ajr, &air, &time_rare_1) != OK) ||
                    (sum_usual(ptrs1, ptrs1, &ptrsr, n, n, &time_usual_1) != OK))
            {
                free_rare(a1, aj1, ai1);
                free_rare(ar, ajr, air);
                free_usual(ptrs1);
                free_usual(ptrsr);
                return ERRMEM;
            }
            time_rare_total += time_rare_1;
            time_usual_total += time_usual_1;
            free_usual(ptrsr);
            free_rare(a1, aj1, ai1);
            free_rare(ar, ajr, air);
        }
        time_rare_total /= repeats;
        time_usual_total /= repeats;

        mem_rare += amount1*sizeof(double) + amount1 * sizeof(int) + n*sizeof(int);
        mem_rare += amount1*sizeof(double) + amount1 * sizeof(int) + n*sizeof(int);
        mem_rare += amountr*sizeof(double) + amountr * sizeof(int) + n*sizeof(int);

        printf("%3d %%    | %10d     |      %3.2f        |     %6I64u      |   %3.2f \n",
               percent, (int) mem_usual, (double) 100*mem_rare/mem_usual,
                   time_usual_total, (double) 100*time_rare_total/time_usual_total);
    }
    free_usual(ptrs1);
    printf("\n\n");
    return OK;
}


