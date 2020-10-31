#ifndef COMPARE_H
#define COMPARE_H

#define POVT 10

#include <inttypes.h>
#include <sys/time.h>
#include "main_header.h"
#include "inputs.h"
#include "sort.h"

void show_compare(int64_t time_main_bubble, int64_t time_key_bubble, int64_t time_main_quick, int64_t time_key_quick);
int compare(void);

#endif // COMPARE_H
