#include "adj_matrix.h"
#include "main_header.h"
#include "tick.h"
#include "cut.h"
#include "graph.h"
#include "welcome.h"

int main()
{
    setbuf(stdout, NULL);
    int size;
    int delete;
    adjm_t *result;

    welcome();

    printf("Input amount of vertices of graph (int, >0): ");
    fflush(stdin);
    while ((fscanf(stdin, "%d", &size) != 1) || (size <= 0))
    {
        printf("ERROR: incorrect amount of vertices. Try again: ");
        fflush(stdin);
    }
    if (size == 1)
    {
        printf("ERROR: Graph consists of one verticy. It can't be disjoint. Exiting program...\n");
        return OK;
    }

    adjm_t *matrix = adjm_create(size);
    if (!matrix)
    {
        printf("ERROR: couldn't allocate memory. Exiting program...");
        return ERRMEM;
    }

    adjm_input(stdin, matrix);
    if (!is_connected(*matrix))
    {
        printf("ERROR: Graph is already disjoint! Exiting program...");
        gv_export(*matrix, *matrix, &delete);
        adjm_free(matrix);
        return OK;
    }

    uint64_t start, end, time;
    start = tick();
    result = graph_cut(*matrix);
    end = tick();
    time = end - start;

    if (result)
    {
        gv_export(*matrix, *result, &delete);
        printf("SUCCESS! Need to delete at least %d edges\n", delete);
        printf("Time (in ticks): %ju\n", time);
    }
    else
    {
        gv_export_empty(*matrix, &delete);
        printf("SUCCESS! Will need to delete all %d edges\n", delete);
        printf("Time (in ticks): %ju\n", time);
    }
    adjm_free(matrix);
    adjm_free(result);

    return OK;
}
