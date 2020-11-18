#include <stdio.h>
#include "in_out.h"

void show_info(void)
{
    printf("This program simulate the process of servicing the first 1000 requests of the 1st type\n");
    printf("Max capacity of each queue = %d\n", MAX_LEN);

}

void input_time(times *T, int i)
{
    printf("\nInput T%d_min T%d_max  value: ", i, i);
    fflush(stdin);
    while ((scanf("%lf %lf", &(T->min), &(T->max)) != 2) || (T->min < 0) || (T->max <= 0) || (T->min > T->max))
    {
        printf("\nERROR: incorrect values. Try again: ");
        fflush(stdin);
    }
}

void input_values(int *n, int *interval, int *log, times *T1, times *T2, times *T3, times *T4)
{
    printf("\nInput stop amount in queue1: ");
    fflush(stdin);
    while ((scanf("%d", n) != 1) || (*n <= 0))
    {
        printf("\nERROR: incorrect value. Try again: ");
        fflush(stdin);
    }

    printf("\nDo you want to see intermidiate results? 0(f)/1(t): ");
    fflush(stdin);
    while ((scanf("%d", log) != 1) || (*log < 0) || (*log > 1))
    {
        printf("\nERROR: incorrect value. Try again: ");
        fflush(stdin);
    }

    if (*log)
    {
        printf("\nShow intermidiate results every .. elemnts: ");
        fflush(stdin);
        while ((scanf("%d", interval) != 1) || (*interval <= 0) || (*interval > *n))
        {
            printf("\nERROR: incorrect value. Try again: ");
            fflush(stdin);
        }
    }
    input_time(T1, 1);
    input_time(T2, 2);
    input_time(T3, 3);
    input_time(T4, 4);
}

void print_time(times *T, int i)
{
    printf("T%d_min: %lf   T%d_max: %lf \n", i, T->min, i, T->max);
}


void print_values(int n, int interval, int log, times *T1, times *T2, times *T3, times *T4)
{
    printf("\nStop amount in queue1 is %d\n", n);

    if (log)
        printf("Show intermidiate results every %d queue1 elements\n", interval);
    else
        printf("Don't show intermidiate results.\n");

    print_time(T1, 1);
    print_time(T2, 2);
    print_time(T3, 3);
    print_time(T4, 4);
}

