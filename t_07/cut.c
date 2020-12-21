#include "cut.h"

unsigned long factorial(int n)
{
    unsigned long res = 1;

    for (int i = 1; i <= n; i++)
        res *= i;

    return res;
}

int comb_amount(int n, int k)
{
    return (factorial(n) / (factorial(k) * factorial(n - k)));
}

void mkcombs(edge_t **ans, edge_t *tmp, chain_t chain, int tmp_size, int n,
             int left, int k, int *idx, int *crow)
{
    if (k == 0)
    {
        for (int i = 0; i < tmp_size; i++)
            ans[*crow][i] = tmp[i];
        (*crow)++;
        return;
    }

    for (int i = left; i <= n; i++)
    {
        tmp[(*idx)++] = chain.edges[i - 1];
        mkcombs(ans, tmp, chain, tmp_size, n, i + 1, k - 1, idx, crow);
        (*idx)--;
    }
}

edge_t **mkcombsvect(chain_t chain, int rows, int n,
                     int k, int *idx, int *crow)
{
    edge_t **ans = allocate_rows(rows, k);
    edge_t *tmp = malloc(sizeof(edge_t) * k);

    mkcombs(ans, tmp, chain, k, n, 1, k, idx, crow);
    free(tmp);

    return ans;
}

int is_connected(adjm_t matrix)
{
    int *visited = calloc(matrix.size, sizeof(int));
    dfs(matrix, 0, visited);

    for (int i = 0; i < matrix.size; i++)
        if (visited[i] == 0)
        {
            free(visited);
            return 0;
        }
    free(visited);

    return 1;
}

adjm_t *adjm_cut(adjm_t matrix, edge_t **vars, int cmbs, int len)
{
    adjm_t *copy = adjm_copy(matrix);

    for (int i = 0; i < cmbs; i++)
    {
        if (!is_connected(*copy))
            return copy;
        adjm_free(copy);
        copy = adjm_copy(matrix);
        for (int j = 0; j < len; j++)
        {
            copy->matrix[vars[i][j].v1][vars[i][j].v2] = 0;
            copy->matrix[vars[i][j].v2][vars[i][j].v1] = 0;
        }
    }
    adjm_free(copy);

    return NULL;
}

adjm_t *graph_cut(adjm_t matrix)
{
    adjm_t *result;

    chain_t *chain = chain_create(matrix);
    for (int i = 1; i <= chain->size; ++i)
    {
        int idx = 0, crow = 0;
        int cmbs = comb_amount(chain->size, i);
        edge_t **vars = mkcombsvect(*chain, cmbs, chain->size, i, &idx, &crow);

        result = adjm_cut(matrix, vars, cmbs, i);

        if (result)
        {
            chain_free(chain);
            free_rows(vars, cmbs);
            return result;
        }
        free_rows(vars, cmbs);
    }
    chain_free(chain);
    adjm_free(result);

    return NULL;
}
