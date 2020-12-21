#include "adj_matrix.h"

adjm_t *adjm_create(int size)
{
    adjm_t *matrix = malloc(sizeof(adjm_t));
    if (!matrix)
        return NULL;

    matrix->size = size;
    matrix->matrix = malloc(size * sizeof(int *));
    if (!matrix->matrix)
    {
        free(matrix);
        return NULL;
    }

    for (int i = 0; i < size; i++)
    {
        matrix->matrix[i] = calloc(size, sizeof(int));
        if (!(matrix->matrix[i]))
        {
            for (int j = 0; j < i; ++j)
            {
                free(matrix->matrix[j]);
            }
            free(matrix->matrix);
            free(matrix);

            return NULL;
        }
    }

    return matrix;
}

void adjm_free(adjm_t *matrix)
{
    if (!matrix)
        return;
    for (int i = 0; i < matrix->size; ++i)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}

void adjm_input(FILE *f, adjm_t *matrix)
{
    printf("Input edges of graph in format \"v1 v2\" (numeration begins with 0, loops are not allowed).\n");
    printf("To finish input, enter \"-1 -1\":\n");

    int v1 = 0, v2 = 0;

    while (1)
    {
        fflush(stdin);
        if (fscanf(f, "%d%d", &v1, &v2) != 2)
        {
            printf("ERROR: incorrect edge. Try again:\n");
            continue;
        }

        if ((v1 == -1) && (v2 == -1))
            return;

        if ((v1 < 0) || (v2 < 0) || (v1 >= matrix->size) || (v2 >= matrix->size))
        {
            printf("ERROR: incorrect edge. Try again:\n");
            continue;
        }
        if (v1 == v2)
        {
            printf("ERROR: loops are not allowed. Try again:\n");
            continue;;
        }

        matrix->matrix[v1][v2] = CONNECTED;
        matrix->matrix[v2][v1] = CONNECTED;
    }
}

void adjm_ouptut(FILE *f, adjm_t matrix)
{
    for (int i = 0; i < matrix.size; ++i)
    {
        for (int j = 0; j < matrix.size; ++j)
        {
            fprintf(f, "%d ", matrix.matrix[i][j]);
        }
        fprintf(f, "\n");
    }
}


//
adjm_t *adjm_copy(adjm_t matrix)
{
    adjm_t *copy = adjm_create(matrix.size);

    for (int i = 0; i < matrix.size; i++)
        for (int j = 0; j < matrix.size; j++)
            if (matrix.matrix[i][j])
                copy->matrix[i][j] = CONNECTED;

    return copy;
}



void dfs(const adjm_t matrix, int v, int *visited)
{
    visited[v] = 1;

    for (int i = 0; i < matrix.size; i++)
    {
        if (matrix.matrix[v][i] && !visited[i])
        {
            dfs(matrix, i, visited);
        }
    }
}
