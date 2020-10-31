#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "main_header.h"
#include "alloc_free.h"
#include "outputs.h"
#include "compare.h"

int usual_to_rare(double **ptrs, int n, int m, int amount, double **a, int **ja, int **ia);
int sum_usual(double **ptrs1, double **ptrs2, double ***ptrs_res, int n, int m, int64_t *time_sum_usual);
int sum_rare(int n, int amount1, int amount2, int *amount3_final,
             double *a1, int *aj1, int *ai1,
             double *a2, int *aj2, int *ai2,
             double **a3_final, int **aj3_final, int **ai3_final, int64_t *time_sum_rare);


#endif // OPERATIONS_H
