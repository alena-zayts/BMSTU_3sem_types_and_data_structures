#include "welcome.h"
#include <stdio.h>

void welcome(void)
{
    printf("This program allows you to find the minimum (by the number of edges) subset of edges,\n"
           "the removal of which turns a given connected graph into a disconnected one.\n");
    printf("To see graphic visualisation, copy \"graph.txt\" to C:\\Program Files (x86)\\Graphviz 2.44.1\\bin ,\n");
    printf("run \"dot -c -Tpng graph.txt -o graph.png\" and open \"graph.png\"\n");
    printf("Deleted edges will be colored in green.\n\n\n");
}
