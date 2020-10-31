#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H

#include "main_header.h"
#include "tick.h"
#include "stack_array.h"
#include "stack_list.h"

int dec_order_arr(stack_arr_s *stack);

int dec_order_list(stack_list_s **root, free_arr_s *fmem);

#endif // STACK_OPERATIONS_H
