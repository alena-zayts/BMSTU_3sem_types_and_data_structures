#ifndef SORT_H
#define SORT_H

#include "main_header.h"

void sort_keys_bubble(int key_arr[][2], int n);
void sort_books_bubble(book_struct book_arr[], int n);
int int2_cmp(const void *val1, const void *val2);
int struct_cmp(const void *val1, const void *val2);

#endif // SORT_H
