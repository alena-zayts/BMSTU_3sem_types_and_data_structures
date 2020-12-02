#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <math.h>

#include "main_header.h"
#include "list.h"

int is_simple(unsigned int num);
unsigned int next_simple(int n);

int square_mid_hash(int value, int n);
int del_hash(int value, int n);

int hash_create_table(list_t **arr, int size, FILE *f, int (*hash)(int, int));
void hash_print_table(list_t *arr, int size);

#endif // HASH_H
