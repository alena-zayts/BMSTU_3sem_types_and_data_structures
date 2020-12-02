#ifndef SEARCH_H
#define SEARCH_H

#include "hash.h"

#include <stdio.h>

#include "main_header.h"
#include "tree.h"
#include "list.h"
#include "tick.h"



int search_tree(int to_find, tree_node root);
double search_tree_av(tree_node root, int *numbers, unsigned long flen);

int search_hashtable(int to_find, list_t *hash_list, int n, int (*hash)(int, int));
double search_hashtable_av(list_t *hash_list, int n, int (*hash)(int, int), int *numbers, unsigned long flen);

int search_file(int to_find, FILE *f);
double search_file_av(FILE *f, int *numberss, unsigned long flen);

void free_numbers(int *numbers, unsigned long flen);

#endif // SEARCH_H
