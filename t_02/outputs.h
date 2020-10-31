#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "main_header.h"

void print_book(book_struct book);
void print_books(book_struct book_arr[], int n);
void print_keys(int key_arr[][2], int n);
void print_books_by_keys(book_struct book_arr[], int key_arr[][2], int n);

#endif // OUTPUTS_H
