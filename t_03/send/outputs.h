#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "main_header.h"

void output_rare(double *a, int *aj, int *ai, int amount, int n);
void output_usual(double **ptrs, int n, int m);
void output_matrix(const char *s, double **ptrs, int n, int m, double *a, int *aj, int *ai, int amount);

#endif // OUTPUTS_H
