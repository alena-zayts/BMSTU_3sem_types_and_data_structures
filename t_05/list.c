#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "structures.h"

//create node
node* create_node(char c)
{
    node *item = malloc(sizeof(node));
    if (item)
    {
        item->inf = c;
        item->next = NULL;
    }
    return item;
}

//add node in begining
node* add_node(node *head, node *elem)
{
    elem->next = head;
    return elem;
}

//pop last node (FIFO)
node* pop_node(node **head)
{
    node* back = NULL;
    if (*head != NULL)
    {
        node *cur = (*head);
        if (cur->next)
        {
            for ( ; (cur->next)->next; cur = cur->next)
                ;
            back = cur->next;
            cur->next = NULL;
        }
        else
        {
            back = cur;
            *head = NULL;
        }
    }
    return back;
}

//free memory from list
void free_all(node *head)
{
    node *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

//push element into queue-list
node* list_push(node* qu, char c, node** used_memory, int *count_used, node** freed_memory, int* cnt_freed, int* cnt_reused)
{
    node* item = NULL;
    //create node
    item = create_node(c);
    if (item)
    {
        //change the list of used memory
        used_memory[*(count_used++)] = item;
        int znak = 0;
        for (int i = 0; i < *cnt_freed; i++)
        {
            if (item == freed_memory[i])
            {
                freed_memory[i] = NULL;
                znak = 1;
            }
            if (znak)
                freed_memory[i] = freed_memory[i+1];
        }
        if (znak)
        {
            *cnt_freed -= 1;
            *cnt_reused += 1;
        }
        //add node
        qu = add_node(qu, item);
    }
    else
        printf("The queue is full (no memory left).\n");
    return qu;
}

//pop element from queue-list
node* list_pop(node** qu)
{
    node* cur = NULL;
    cur = pop_node(qu);
    if (cur == NULL)
        printf("The queue is empty.\n");
    return cur;
}

//print queue-list
void list_print(node* qu)
{
    node* cur = qu;
    if (qu == NULL)
        printf("Empty queue\n");
    else
    {
        printf("Current queue: \n");
        for ( ; cur; cur = cur->next)
            printf("Inf: %c\n", cur->inf);
        printf("\n");
    }
}

//model the task using queue-list
void model_list(int n, int interval, times t1, times t2, times t3, times t4, int log_flag)
{
    node* ret;
    //for checking memory
    node* freed_memory[MAX_LEN];
    int cnt_freed = 0;
    node* used_memory[MAX_LEN];
    int count_used = 0;
    int cnt_reused = 0;

    //for queues-lists
    node *q1 = NULL, *q2 = NULL;
    queue d1, d2;

    queue_create_list(&d1);
    queue_create_list(&d2);

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
        if (d1.curr_size >= MAX_LEN)
        {
            printf("==========================\n");
            printf("ERROR: Queue1 is overflow. Stopping modeling.\n");
            break;
        }
        if (d2.curr_size >= MAX_LEN)
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
            if ((q1 == NULL) && q2)
            {
                t_oa = rand_time(t4);
                type = 2;

                ret = list_pop(&q2);
                if (ret != NULL)
                {
                    freed_memory[cnt_freed++] = ret;
                    free(ret);
                }
                queue_del(&d2);
                total_time_out2 += t_oa;
            }
            else if (q1)
            {
                t_oa = rand_time(t3);
                type = 1;
                ret = list_pop(&q1);

                if (ret != NULL)
                {
                    freed_memory[cnt_freed++] = ret;
                    free(ret);
                }
                queue_del(&d1);
                total_time_out1 += t_oa;
            }
        }

        //find min time
        double t_min = 0;
        if (fabs(t_oa - 0) < EPS)//no elmemts to process
            t_min = fmin(t_q1, t_q2);
        else
            t_min = fmin(t_q1, fmin(t_q2, t_oa));//have elements to process

        // Process requests
        if (fabs(t_oa - t_min) < EPS) //min time is time of oa
        {
            t_oa = 0.;
            if (type == 1)
                req_out1++;
            if (type == 2)
                req_out2++;
        }
        if (req_out1 == n) //end processing
            break;

        // Add requests
        if (fabs(t_q1 - t_min) < EPS)
        {
            q1 = list_push(q1, '1', used_memory, &count_used, freed_memory, &cnt_freed, &cnt_reused);
            queue_add(&d1);
            req_in1++;
        }
        if (fabs(t_q2 - t_min) < EPS)
        {
            q2 = list_push(q2, '2', used_memory, &count_used, freed_memory, &cnt_freed, &cnt_reused);
            queue_add(&d2);
            req_in2++;
        }

        //using simultaneously
        t_q1 -= t_min;
        t_q2 -= t_min;

        if (t_oa >= t_min)
            t_oa -= t_min;
        time += t_min;

        // show intermediate results
        if(log_flag && (req_out1 % interval == 0) && req_out1 != req_show)
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

    printf("Time of modeling using queue-list: %ju ticks\n", timer);

    int avg_nodes = (d1.sum_size/d1.out_request + 1) + (d2.sum_size/d2.out_request + 1);
    printf("Avg nodes, that are kept in memory in both queues: %d\n", avg_nodes);
    printf("Avg memory needed = 2 * %d + %d * %d = %db\n\n", (int) sizeof(char *),
           (int) sizeof(node), avg_nodes, ((int) (2*sizeof(char *) + sizeof(node)*avg_nodes)));

    int flag = 0;
    printf("Show memory results? 1-yes/0-no: ");
    fflush(stdin);
    while ((scanf("%d", &flag) != 1) || (flag < 0) || (flag > 1))
    {
        printf("\nERROR: incorrect value. Try again: ");
        fflush(stdin);
    }

    if (flag)
    {
        printf("Reused adresses: %d\n", cnt_reused);
        printf("Still free     : %d\n", cnt_freed);
        for (int i = 0; i < fmin(20, cnt_freed); i++)
            printf("%p\n", (void*)freed_memory[i]);
    }

    free_all(q1);
    free_all(q2);
}
