#include "main_header.h"
#include "show_info.h"
#include "inputs.h"
#include "operations.h"
#include "outputs.h"
#include "compare.h"


int main(void)
{
    setbuf(stdout, NULL);
    int rc = OK;

    double **ptrs1 = NULL;
    int amount1 = 0;
    double *a1 = NULL;
    int *aj1 = NULL;
    int *ai1 = NULL;

    double **ptrs2 = NULL;
    int amount2 = 0;
    double *a2 = NULL;
    int *aj2 = NULL;
    int *ai2 = NULL;

    double **ptrs3 = NULL;
    int amount3 = 0;
    double *a3 = NULL;
    int *aj3 = NULL;
    int *ai3 = NULL;

    int n, m;
    int64_t time_usual;
    size_t mem_usual;
    int64_t time_rare;
    size_t mem_rare;


    show_info();

    rc = input_all(&n, &m, &ptrs1, &amount1, &ptrs2, &amount2);
    if (rc == OK)
    {
        rc = usual_to_rare(ptrs1, n, m, amount1, &a1, &aj1, &ai1);
        if (rc == OK)
        {
            rc = usual_to_rare(ptrs2, n, m, amount2, &a2, &aj2, &ai2);
            if (rc == OK)
            {
                output_matrix("ENTERED MATRIX 1", ptrs1, n, m, a1, aj1, ai1, amount1);
                output_matrix("ENTERED MATRIX 2", ptrs2, n, m, a2, aj2, ai2, amount2);

                rc = sum_usual(ptrs1, ptrs2, &ptrs3, n, m, &time_usual);
                if (rc == OK)
                {
                    rc = sum_rare(n, amount1, amount2, &amount3, a1, aj1, ai1,
                                  a2, aj2, ai2, &a3, &aj3, &ai3, &time_rare);
                    if (rc == OK)
                    {
                        output_matrix("SUM MATRIX", ptrs3, n, m, a3, aj3, ai3, amount3);

                        mem_usual = 3 * (n * m) * sizeof(double) + 3 * n * sizeof(double*);
                        mem_rare = (((amount1+amount2+amount3)*(sizeof(double)+sizeof(int)))+
                                    3*n*sizeof(int));

                        show_compare_1(time_usual, time_rare, mem_usual, mem_rare);

                        printf("\n\n To see the comparative table of using these two algorytms for different\n"
                               "matricies sizes and percentage of nonnull elements, see the report\n");
                        free_usual(ptrs1);
                        free_usual(ptrs2);
                        free_usual(ptrs3);
                        free_rare(a1, aj1, ai1);
                        free_rare(a2, aj2, ai2);
                        free_rare(a3, aj3, ai3);
                    }
                    else
                    {
                        free_usual(ptrs1);
                        free_usual(ptrs2);
                        free_usual(ptrs3);
                        free_rare(a1, aj1, ai1);
                        free_rare(a2, aj2, ai2);
                    }
                }
                else
                {
                    free_usual(ptrs1);
                    free_usual(ptrs2);
                    free_rare(a1, aj1, ai1);
                    free_rare(a2, aj2, ai2);
                }
            }
            else
            {
                free_usual(ptrs1);
                free_usual(ptrs2);
                free_rare(a1, aj1, ai1);
            }
        }
        else
        {
            free_usual(ptrs1);
            free_usual(ptrs2);
        }
    }
    if (rc == ERRMEM)
        printf("MEMORY ERROR: couldn't allocate matrix.\n Finishing program");
    if (rc == OK)
        printf("Everything went ok, finishing program\n");
    return rc;
}
