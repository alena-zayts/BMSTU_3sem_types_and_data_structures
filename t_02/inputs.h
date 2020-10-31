#ifndef INPUTS_H
#define INPUTS_H

#include "main_header.h"

int input_from_file(FILE *f, book_struct book_arr[], int *n);
int add_one(book_struct book_arr[], int key_arr[][2], int n);
int input_my(book_struct book_arr[], int key_arr[][2], int *n);
void fill_key_arr(book_struct book_arr[], int key_arr[][2], int n);

#endif // INPUTS_H
