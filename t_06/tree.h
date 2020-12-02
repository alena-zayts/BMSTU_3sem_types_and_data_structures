#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main_header.h"


typedef struct tree_node
{
    int value; //значение узла
    struct tree_node *left; //левый потомок
    struct tree_node *right; //правый потомок
} tree_node;


typedef struct
{
    tree_node **arr; //указатель на массив указателей узлов дерева
    int size; //текущий размер
    int mem_size; //доступный размер
} tree_arr;


tree_node *node_create(int value);
tree_node *node_insert(tree_node *node, int value);

void tree_create(tree_node **root, FILE *f);
void tree_depth(tree_node *root, int *vrtxs, int *cmprs, int depth);
void tree_push(tree_arr *arr, tree_node *node);
void nodes_save(tree_node *root, tree_arr *arr);

tree_node *tree_build(tree_arr *arr, int start, int end);
tree_node *tree_balance(tree_node *root, int *unique);
void tree_print(tree_node *root, int space);
void tree_free(tree_node *node);


#endif // TREE_H
