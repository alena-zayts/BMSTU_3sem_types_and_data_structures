#ifndef STACK_LIST_H
#define STACK_LIST_H

#include "main_header.h"
#include "free_array.h"
#include "tick.h"

//стек в виде линейного односвязного списка
typedef struct stack_list
{
    int data; //значение элемента стека
    int ind; //индекс элемента стека
    struct stack_list *next; //указатель на предыдущий элемент
} stack_list_s;


stack_list_s *create_stack_list_node(const int data);

int is_full_stack_list(stack_list_s *root, const int limit);

int is_empty_stack_list(stack_list_s *root);

int push_stack_list(stack_list_s **root, const int data, uint64_t *time);

int input_stack_list(const int count, stack_list_s **root, uint64_t *time);

int output_stack_list(stack_list_s *root);

void pop_stack_list(stack_list_s **root, free_arr_s *fmem, int *el, uint64_t *time);

void check_top_stack_list(stack_list_s *root, free_arr_s *fmem);

void free_stack_list(stack_list_s **root, free_arr_s *fmem);

#endif // STACK_LIST_H
