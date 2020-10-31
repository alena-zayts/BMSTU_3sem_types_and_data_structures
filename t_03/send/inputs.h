#ifndef INPUTS_H
#define INPUTS_H

#include "main_header.h"
#include "alloc_free.h"

int input_all(int *n, int*m, double ***ptrs1, int *amount1, double ***ptrs2, int *amount2);
void input_nm(int *n, int *m);
void input_manually(double **ptrs, int n, int m, int num_elems);
int input_automatically(int n, int m, int amount, double **ptrs);
void random_array(int *arr, int n);

#endif // INPUTS_H
