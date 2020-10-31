#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include "main_header.h"
#include "tick.h"

//стек в виде массива
typedef struct
{
    int top; //верхушка стека
    int capacity; //вместимость стека
    int *arr; //указатель на массив
} stack_arr_s;

stack_arr_s *create_stack_arr(const int capacity);

void free_stack_arr(stack_arr_s *stack);

int is_full_stack_arr(stack_arr_s *stack);

int is_empty_stack_arr(stack_arr_s *stack);

void push_stack_arr(stack_arr_s *stack, const int data, uint64_t *time);

void input_stack_arr(const int count, stack_arr_s *stack, uint64_t *time);

void output_stack_arr(stack_arr_s *stack);

void pop_stack_arr(stack_arr_s *stack, int *el, uint64_t *time);

#endif // STACK_ARRAY_H
