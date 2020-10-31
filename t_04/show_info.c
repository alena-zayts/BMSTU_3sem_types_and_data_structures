#include "show_info.h"

void show_info(void)
{
    printf("The program implements working with stack and allows you to perform operations of:\n"
           "1) adding elements,\n"
           "2) deleting elements,\n"
           "3) displaying the current state of the stack,\n"
           "4) printing decreasing series of sequences of integers in reverse order.\n"
           "The stack is implemented in two types:\n"
           "a. array;\n"
           "b. list.\n");
}

void show_commands(void)
{
    printf("\nPossible commands:\n");
    printf("0   Exit the program\n");
    printf("Commands for stack-array:\n");
    printf("1   Create a stack-array and enter the initial values.\n");
    printf("2   Add an element to the existing stack-array.\n");
    printf("3   Delete an element from the stack-array (implemented as pop\n"
           "         when deleting, the value of the deleted element is displayed).\n");
    printf("4   Output a decreasing series of sequences of integers from the stack-array\n"
           "         in reverse order and a quantitative characteristic of processing\n"
           "         (the stack array will be completely emptied).\n");
    printf("5   Display the current state of the stack-array (the stack array itself will not change).\n");
    printf("Commands for stack-list:\n");
    printf("6   Create a stack-list and enter the initial values.\n");
    printf("7   Add an item to the stack-list.\n");
    printf("8   Delete an element from the stack-list (implemented as pop\n"
           "         when deleting, the value of the element being deleted is displayed)\n"
           "         and output an array of freed addresses\n");
    printf("9   Output an array of freed addresses.\n");
    printf("10  Output a decreasing series of sequences of integers from the stack-list\n"
           "         in reverse order and a quantitative characteristic of processing\n"
           "         (the stack array will be completely emptied and deleted).\n");
    printf("11  Display the current state of the stack-list with the addresses of elements\n"
           "         (the stack-list itself will not change).\n");
    printf("12  Show information about memory required for each method\n");
    printf("\n");
}
