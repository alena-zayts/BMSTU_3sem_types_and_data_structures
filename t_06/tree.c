#include "tree.h"

tree_node *node_create(int value)
{
    tree_node *node = malloc(sizeof(tree_node));
    if (!node)
    {
        printf("MEMORY ERROR!");
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

tree_node *node_insert(tree_node *node, int value)
{
    if (node == NULL)
    {
        return node_create(value);
    }
    if (value > node->value)
    {
        node->left = node_insert(node->left, value);
    }
    else if (value < node->value)
    {
        node->right = node_insert(node->right, value);
    }
    return node;
}

void tree_create(tree_node **root, FILE *f)
{
    rewind(f);
    int value;
    fscanf(f, "%d", &value);
    *root = node_insert(*root, value);

    while (fscanf(f, "%d", &value) == 1)
        node_insert(*root, value);
}

void tree_print(tree_node *root, int space)
{
    if (root == NULL)
        return;
    //printf("ROOOT %d\n", root->value);
    {
        space += TAB;

        tree_print(root->right, space);

        printf("\n");
        for (int i = TAB; i < space; i++)
        {
            printf(" ");
        }
        printf("%d\n", root->value);

        tree_print(root->left, space);
    }
}

void tree_depth(tree_node *root, int *vrtxs, int *cmprs, int depth)
{
    if (root)
    {
        (*vrtxs)++;
        (*cmprs) += depth;

        tree_depth(root->right, vrtxs, cmprs, depth + 1);
        tree_depth(root->left, vrtxs, cmprs, depth + 1);
    }
}

//push to 0
void tree_push(tree_arr *arr, tree_node *node)
{
    (arr->size)++;
    if (arr->size >= arr->mem_size)
    {
        arr->mem_size *= 2;
        arr->arr = realloc(arr->arr, arr->mem_size * sizeof(tree_node *));
        if (arr->arr == NULL)
            printf("MEMORY ERROR");
    }
    for (int i = arr->size; i > 0; i--)
        arr->arr[i] = arr->arr[i - 1];

    arr->arr[0] = node;
}

tree_node *tree_build(tree_arr *arr, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;
    tree_node *root = arr->arr[mid];

    root->right = tree_build(arr, start, mid - 1);
    root->left = tree_build(arr, mid + 1, end);

    return root;
}

void nodes_save(tree_node *root, tree_arr *arr)
{
    if (root == NULL)
    {
        return;
    }

    nodes_save(root->left, arr);
    tree_push(arr, root);
    nodes_save(root->right, arr);
}

tree_node *tree_balance(tree_node *root, int *unique)
{
    tree_arr arr;
    arr.mem_size = 8;
    arr.size = 0;
    arr.arr = malloc(sizeof(tree_node *) * arr.mem_size);
    if (arr.arr == NULL)
        printf("MEMORY ERROR\n");

    nodes_save(root, &arr);

    int n = arr.size;
    *unique = n;

    tree_node *r = tree_build(&arr, 0, n - 1);

    free(arr.arr);

    return r;
}

void tree_free(tree_node *node)
{
    if (node == NULL)
    {
        return;
    }

    tree_free(node->left);
    tree_free(node->right);

    free(node);
}
