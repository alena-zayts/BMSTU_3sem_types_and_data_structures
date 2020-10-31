#ifndef ALLOC_FREE_H
#define ALLOC_FREE_H

#include "main_header.h"

double **allocate_usual(int n, int m);
void free_usual(double **ptrs);
int allocate_rare(double **a, int**aj, int **ai, int n, int amount);
void free_rare(double *a, int *aj, int *ai);

#endif // ALLOC_FREE_H
