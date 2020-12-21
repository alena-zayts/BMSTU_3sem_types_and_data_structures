#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#include "adj_matrix.h"

//ребро графа
typedef struct
{
    int v1; //из вершины
    int v2; //в вершину
} edge_t;

//путь
typedef struct
{
    int size; //длина пути
    edge_t *edges; //массив ребер пути
} chain_t;

chain_t *chain_create(adjm_t matrix);
void chain_free(chain_t *chain);

edge_t **allocate_rows(int n, int m);
void free_rows(edge_t **data, int n);

void gv_export(adjm_t matrix, adjm_t result, int *delte);
void gv_export_empty(adjm_t matrix, int *delete);

#endif // GRAPH_H
