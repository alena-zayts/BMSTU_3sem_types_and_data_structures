#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdlib.h>
#include <inttypes.h>

#define MAX_LEN 10000
#define EPS 1e-6


//Times ranges
struct range
{
    double min;
    double max;
};
typedef struct range times;

//The descriptor of a queue
struct queue
{
    void* low; //lower address
    void* up; //upper address
    void* p_in; //address to add elem
    void* p_out; //address to delete elem
    int max_num; //maximum amount of elements in queue
    int count_request; // total amount of requests
    int sum_size; // used to count average amount of elements in queue
    int curr_size; //current amount of elements in queue
    int out_request; //amount of requests to delete elem
    int in_request; //amount of requests to add elem
};
typedef struct queue queue;

//Node of queue-list
typedef struct node node;
struct node
{
    char inf;
    node *next;
};

void queue_create_list(queue *d);
void queue_create_arr(queue *d, char *q);

void queue_add(queue *d);
void queue_del(queue *d);

int queue_is_empty(queue d);

double rand_time(times t);

uint64_t tick(void);

#endif // STRUCTURES_H
