#ifndef LIST_H
#define LIST_H

#include "structures.h"

node* create_node(char c);
node* add_node(node *head, node *item);
node* pop_node(node **head);

void free_all(node *head);


node* list_push(node* qu, char c, node** used_memory, int *count_used, node** freed_memory, int* count_freed, int* second_used);
node* list_pop(node** qu);
void list_print(node* qu);

void model_list(int n, int interval, times t1, times t2, times t3, times t4, int log_flag);

#endif // LIST_H
