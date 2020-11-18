#include "structures.h"

void queue_create_list(queue *d)
{
    d->max_num = MAX_LEN;
    d->p_in = NULL;
    d->p_out = NULL;
    d->count_request = 0;
    d->sum_size = 0;
    d->curr_size = 0;
    d->out_request = 0;
    d->in_request = 0;
}

void queue_create_arr(queue *d, char *q)
{
    queue_create_list(d);
    d->low = q;
    d->up = q + d->max_num;
    d->p_in = q;
    d->p_out = q;
}


void queue_del(queue *d)
{
    d->curr_size--;
    d->sum_size += d->curr_size;
    d->count_request++;
    d->out_request++;
}

void queue_add(queue *d)
{
    d->curr_size++;
    d->sum_size += d->curr_size;
    d->count_request++;
    d->in_request++;
}

int queue_is_empty(queue d)
{
    return ((d.p_in == d.p_out) && (*((char*)d.p_in) == 0));
}

double rand_time(times t)
{
    return (t.max - t.min) * (rand() / (double)RAND_MAX) + t.min;
}

/*
Подсчет тактов
*/
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}
