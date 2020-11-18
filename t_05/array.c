#include <stdio.h>
#include <time.h>
#include <math.h>

#include "array.h"
#include "structures.h"

void arr_push(queue* d, char* qu, char c)
{
    char *p_in = d->p_in;
    if (d->p_in == d->p_out && *((char*)d->p_in) != '\0')
        printf("The queue is full.\n");
    else
    {
        *((char*)d->p_in) = c;
        if (d->p_in != d->up)
            d->p_in = p_in + 1;
        else
            d->p_in = d->low;
    }
    *qu = 'x';
}


char arr_pop(queue* d, char* qu)
{
    char *p_out = d->p_out;
    char ps = '\0';
    if (d->p_in == d->p_out && *((char*)d->p_in) == '\0')
    {
        printf("Empty queue.\n");
    }
    else
    {
        ps = *((char*)d->p_out);
        *((char*)d->p_out) = '\0';
        if (d->p_out != d->up)
            d->p_out = p_out + 1;
        else
            d->p_out = d->low;
    }
    return ps;
    *qu = 'x';
}

void arr_print(queue* d, char* qu)
{
    if (d->p_in == d->p_out && *((char*)d->p_in) == '\0')
    {
        printf("Empty queue\n");
    }
    else
    {
        printf("Queue: \n");
        char* begin = d->p_out;
        char* end = d->p_in;
        do
        {
            printf("Inf: %c \n", *begin);
            if (begin != d->up)
                begin += 1;
            else
                begin = d->low;
        }
        while(begin != end);
        printf("\n");
    }
    *qu = 'x';
}


void model_array(int n, int interval, times t1, times t2, times t3, times t4, int log)
{
    //for queue-array
    char *q1, *q2;
    queue d1, d2;

    q1 = (char*)calloc(MAX_LEN, sizeof(char));
    q2 = (char*)calloc(MAX_LEN, sizeof(char));

    queue_create_arr(&d1, q1);
    queue_create_arr(&d2, q2);

    int type = 1; // Current request type

    double time = 0.0; // Modeling time
    double t_q1 = 0, t_q2 = 0, t_oa = 0;

    // Requests to queue
    int req_in1 = 0, req_in2 = 0, req_out1 = 0, req_out2 = 0;
    int req_show = 0;

    double total_time_out1 = 0;
    double total_time_out2 = 0;

    //BEGIN
    uint64_t timer_beg = tick();

    while (req_out1 < n)
    {
        //overflow
        if (d1.p_in == d1.p_out && *((char*)d1.p_in))
        {
            printf("==========================\n");
            printf("ERROR: Queue1 is overflow. Stopping modeling.\n");
            break;
        }
        if (d2.p_in == d2.p_out && *((char*)d2.p_in))
        {
            printf("==========================\n");
            printf("ERROR: Queue2 is overflow. Stopping modeling.\n");
            break;
        }

        if (fabs(t_q1 - 0) < EPS)
            t_q1 = rand_time(t1);
        if (fabs(t_q2 - 0) < EPS)
            t_q2 = rand_time(t2);
        if (fabs(t_oa - 0) < EPS)
        {
            //choosing queue to process
            if (!queue_is_empty(d1))
            {
                t_oa = rand_time(t3);
                type = 1;
                arr_pop(&d1, q1);
                queue_del(&d1);
                total_time_out1 += t_oa;
            }
            else if (!queue_is_empty(d2))
            {
                t_oa = rand_time(t4);
                type = 2;
                arr_pop(&d2, q2);
                queue_del(&d2);
                total_time_out2 += t_oa;
            }
        }

        double t_min = 0;

        if (fabs(t_oa - 0) < EPS)
            t_min = fmin(t_q1, t_q2);
        else
            t_min = fmin(t_q1, fmin(t_q2, t_oa));

        // Process requests
        if (fabs(t_min - t_oa) < EPS)
        {
            t_oa = 0;
            if(type == 1)
                req_out1++;
            if(type == 2)
                req_out2++;
        }
        if (req_out1 == n)
            break;

        // Add requests
        if (fabs(t_min - t_q1) < EPS)
        {
            arr_push(&d1, q1, '1');
            queue_add(&d1);
            req_in1++;
        }
        if (fabs(t_min - t_q2) < EPS)
        {
            arr_push(&d2, q2, '2');
            queue_add(&d2);
            req_in2++;
        }

        t_q1 -= t_min;
        t_q2 -= t_min;

        if(t_oa >= t_min)
            t_oa -= t_min;
        time += t_min;
        // show intermediate results
        if(req_out1 % interval == 0 && req_out1 != req_show && log)
        {
            req_show = req_out1;
            printf("after posrocessing %4d elements of first queue:\n", req_out1);
            printf("\tqueue1:\n");
            printf("\t\tamount in queue: current -  %3d, avg - %3d\n", d1.curr_size,
                   2 * d1.sum_size/(d1.in_request + d1.out_request));
            printf("\t\twent in -  %3d, went out - %3d\n", req_in1, req_out1);
            printf("\t\tavg time in queue %lf\n", (double) time / req_out1);
            printf("\tqueue2:\n");
            printf("\t\tamount in queue: current -  %3d, avg - %3d\n", d2.curr_size,
                   2 * d2.sum_size/(d2.in_request + d2.out_request));
            printf("\t\twent in -  %3d, went out - %3d\n", req_in2, req_out2);
            printf("\t\tavg time in queue %lf\n", (double) time / req_out2);
        }
    }
    //END
    uint64_t timer_end = tick();
    uint64_t timer = timer_end - timer_beg;

    printf("\n\nFINAL RESULTS OF MODELING\n");
    printf("\tModeling time: %f \n", time);
    printf("\tIn/Out from 1 queue: %d %d (%d)\n", req_in1, req_out1, req_in1 - req_out1);
    printf("\tIn/Out from 2 queue: %d %d (%d)\n", req_in2, req_out2, req_in2 - req_out2);
    double downtime = fabs(time - total_time_out1 - total_time_out2);
    printf("\tOA downtime: %lf \n\n", downtime);


    printf("\n\nTHEORETICAL RESULTS:\n");
    double av_t_in1 = (t1.min + t1.max) / 2;
    double av_t_out1 = (t3.min + t3.max) / 2;
    double av_t_in2 = (t2.min + t2.max) / 2;
    double av_t_out2 = (t4.min + t4.max) / 2;
    double t_modelling;
    printf("\tQueue1: Avg time comings %lf, processing %lf\n", av_t_in1, av_t_out1);
    printf("\tQueue2: Avg time comings %lf, processing %lf\n", av_t_in2, av_t_out2);

    if (av_t_in1 <= av_t_out1)
    {
        printf("In queue1 avg time comings <= processing\n");
        printf("This means that expected modeling time is counted by avg time processing in queue1.\n");
        t_modelling = n * av_t_out1;
        printf("\tExpected modeling time = %d * %lf = %lf\n", n, av_t_out1, t_modelling);
    }
    else
    {
        printf("In queue1 avg time comings > processing\n");
        printf("This means that expected modeling time is counted by avg time coming in queue1.\n");
        t_modelling = n * av_t_in1;
        printf("\tExpected modeling time = %d * %lf = %lf\n", n, av_t_in1, t_modelling);
    }

    double out_err = fabs(100*(time - t_modelling)/t_modelling);
    printf("Out error: %lf%%\n\n", out_err);

    printf("\n\nEFFICIENCY RESULTS:\n");

    printf("Time of modeling using queue-array: %ju ticks\n", timer);
    printf("Avg memory needed = 2 * %d + 2 * %d * %d = %db\n\n", (int) sizeof(char *),
           (int) sizeof(char), (int) MAX_LEN, ((int) (2*sizeof(char *) + sizeof(char)*MAX_LEN*2)));

    free(q1);
    free(q2);
}
