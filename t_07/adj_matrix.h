#ifndef ADJ_MATRIX_H
#define ADJ_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "main_header.h"

#include "io.h"

//матрица смежности
typedef struct
{
    int size; //количество вершин в графе
    int **matrix; //сама матрица (указатель на массив указателей)
} adjm_t;

adjm_t *adjm_create(int size);
void adjm_free(adjm_t *matrix);

void adjm_input(FILE *f, adjm_t *matrix);
void adjm_ouptut(FILE *f, adjm_t matrix);

adjm_t *adjm_copy(adjm_t matrix);
void dfs(const adjm_t matrix, int v, int *visited);

#endif // ADJ_MATRIX_H
