#ifndef COMPARE_H
#define COMPARE_H

#include "main_header.h"
#include "inputs.h"
#include "operations.h"

void show_compare_1(int64_t time_sum_usual, int64_t time_sum_rare, size_t mem_usual, size_t mem_rare);
int show_compare_n(int n, int a, int b, int step);
int64_t tick(void);

#endif // COMPARE_H
