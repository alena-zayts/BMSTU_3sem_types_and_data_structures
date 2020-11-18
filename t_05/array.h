#ifndef ARRAY_H
#define ARRAY_H

#include "structures.h"

void arr_push(queue* d, char* qu, char c);
char arr_pop(queue* d, char* qu);
void arr_print(queue* d, char* qu);

void model_array(int n, int interval, times t1, times t2, times t3, times t4, int log_flag);


#endif // ARRAY_H
