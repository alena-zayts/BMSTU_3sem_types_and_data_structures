#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#include "main_header.h"

int *file_read(FILE *f, long *final_amount);
long file_amount(FILE *f);
int file_bytes(FILE *f);


#endif // FILE_H
