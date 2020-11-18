#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "in_out.h"
#include "structures.h"
#include "list.h"
#include "array.h"


int main(void)
{
    srand(time(NULL));
    setbuf(stdout, NULL);
    int n = 1000;
    int interval = 100;
    int log = 1;
    times T1 = {1, 5};
    times T2 = {0, 3};
    times T3 = {0, 4};
    times T4 = {0, 1};

    show_info();

    int flag = -1;
    while (flag)
    {
        printf("\nEnter command:\n"
               "\t1 - Print current values\n"
               "\t2 - Change values\n"
               "\t3 - Model with queue-list\n"
               "\t4 - Model with queue-array\n"
               "\t0 - Exit program\n");

        fflush(stdin);
        if (scanf("%d", &flag) != 1)
        {
            printf("ERROR: unknown command\n");
            continue;
        }

        switch (flag)
        {
            case 0:
                break;
            case 1:
                print_values(n, interval, log, &T1, &T2, &T3, &T4);
                break;
            case 2:
                input_values(&n, &interval, &log, &T1, &T2, &T3, &T4);
                break;
            case 3:
                model_list(n, interval, T1, T2, T3, T4, log);
                break;
            case 4:
                model_array(n, interval, T1, T2, T3, T4, log);
                break;
            default:
                printf("ERROR: unknown command\n");
                break;
        }
    }
    return 0;
}
