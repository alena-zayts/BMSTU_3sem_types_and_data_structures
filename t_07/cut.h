#ifndef CUT_H
#define CUT_H

#include "graph.h"

unsigned long factorial(int n);

int comb_amount(int n, int k);

void mkcombs(edge_t **ans, edge_t *tmp, chain_t chain, int tmp_size, int n,
             int left, int k, int *idx, int *crow);

edge_t **mkcombsvect(chain_t chain, int rows, int n,
                     int k, int *idx, int *crow);

int is_connected(adjm_t matrix);

adjm_t *adjm_cut(adjm_t matrix, edge_t **vars, int cmbs, int len);

adjm_t *graph_cut(adjm_t matrix);

#endif // CUT_H
