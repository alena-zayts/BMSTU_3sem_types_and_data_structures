#include "graph.h"

chain_t *chain_create(adjm_t matrix)
{
    int edges = 0;

    for (int i = 0; i < matrix.size; i++)
        for (int j = 0; j < matrix.size; j++)
            if (matrix.matrix[i][j])
                edges++;

    edges /= 2;

    chain_t *chain = malloc(sizeof(chain_t));
    if (!chain)
        return NULL;

    chain->size = edges;
    chain->edges = malloc(sizeof(edge_t) * edges);
    if (!chain->edges)
    {
        free(chain);
        return NULL;
    }

    edge_t edge;
    int idx = 0;

    adjm_t *copy = adjm_copy(matrix);

    for (int i = 0; i < copy->size; i++)
    {
        for (int j = 0; j < copy->size; j++)
        {
            if (copy->matrix[i][j])
            {
                edge.v1 = i;
                edge.v2 = j;
                chain->edges[idx] = edge;

                copy->matrix[i][j] = 0;
                copy->matrix[j][i] = 0;

                idx++;
            }
        }
    }
    adjm_free(copy);

    return chain;
}

void chain_free(chain_t *chain)
{
    if (chain)
    {
        free(chain->edges);
        free(chain);
    }
}

edge_t **allocate_rows(int n, int m)
{
    edge_t **data = malloc(sizeof(edge_t *) * n);
    if (!data)
        return NULL;

    for (int i = 0; i < n; ++i)
    {
        data[i] = malloc(sizeof(edge_t) * m);
        if (!data[i])
        {
            for (int j = 0; j < i; ++j)
                free(data[j]);
            return NULL;
        }
    }
    return data;
}

void free_rows(edge_t **data, int n)
{
    if (!data)
        return;
    for (int i = 0; i < n; ++i)
        free(data[i]);
    free(data);
}

void gv_export(adjm_t matrix, adjm_t result, int *delete)
{
    *delete = 0;
    FILE *f = fopen("graph.txt", "w");
    fprintf(f, "graph {\n");

    for (int i = 0; i < matrix.size; i++)
        for (int j = 0; j < matrix.size; j++)
            if (matrix.matrix[i][j])
                matrix.matrix[j][i] = 0;

    for (int i = 0; i < result.size; i++)
        for (int j = 0; j < result.size; j++)
            if (result.matrix[i][j])
                result.matrix[j][i] = 0;

    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            if (matrix.matrix[i][j] && result.matrix[i][j])
                fprintf(f, "%d -- %d;\n", i, j);
            if (matrix.matrix[i][j] && !result.matrix[i][j])
            {
                (*delete)++;
                fprintf(f, "%d -- %d[color=green,penwidth=3.0];\n", i, j);
            }
        }
        fprintf(f, "%d;\n", i);
    }

    fprintf(f, "}\n");
    fclose(f);
}

void gv_export_empty(adjm_t matrix, int *delete)
{
    *delete = 0;
    FILE *f = fopen("graph.txt", "w");
    fprintf(f, "graph {\n");

    for (int i = 0; i < matrix.size; i++)
        for (int j = 0; j < matrix.size; j++)
            if (matrix.matrix[i][j])
                matrix.matrix[j][i] = 0;

    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            if (matrix.matrix[i][j])
            {
                (*delete)++;
                fprintf(f, "%d -- %d[color=green,penwidth=3.0];\n", i, j);
            }
        }
        fprintf(f, "%d;\n", i);
    }

    fprintf(f, "}\n");
    fclose(f);
}
