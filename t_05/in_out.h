#ifndef IN_OUT_H
#define IN_OUT_H

#include "structures.h"

void show_info(void);

void input_time(times *T, int i);
void input_values(int *n, int *interval, int *log, times *T1, times *T2, times *T3, times *T4);

void print_time(times *T, int i);
void print_values(int n, int interval, int log, times *T1, times *T2, times *T3, times *T4);


#endif // IN_OUT_H
