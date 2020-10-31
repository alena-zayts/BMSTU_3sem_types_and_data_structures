#include "show_info.h"

//вывод общей информации о программе
void show_info(void)
{
    printf("A sparse (containing many zeros) matrix (with real values) is stored in the form of 3 objects:\n"
           "-- vector A contains the values of non-zero elements;\n"
           "-- vector JA contains column numbers for elements of vector A;\n"
           "-- vector IA with the Nk element containing the number of components in A and JA\n"
           "          that begin the description of the Nk row of the matrix A.\n"
           "          (-1 means that the row is empty)\n\n"
           "The program can:\n"
           "1) Simulate the operation of adding two matrices stored in this form,\n"
           "   with the result in the same form.\n"
           "2) perform the addition operation using the standard algorithm for working with matrices.\n"
           "3) Compare the time of operations and the amount of memory when using these 2 algorithms\n\n");

    printf("To add up two matrices, first input n (amount of rows) and m (amount of columns) in them.\n"
           "Then input source matrices in one of the following ways:\n"
           "0) automaticly: specify the amount of nonnull elements in matrix\n"
           "1) manually: specify the amount of nonnull elements and then input them in a coordinate format:\n"
           "   \"i j value\",\n"
           "   where i - the number of row (int, 0 <= i <= n-1);\n"
           "         j - the number of column (int, 0 <= j <= m-1);\n"
           "         value - value of this element (real, |value - 0| > %lf)\n", EPS);

    printf("You will get:\n"
           "-- the source matrices and a matrix-result of adding in the described form\n"
           "   (if n <= %d and m <= %d, the matrices will be shown in a usual form as well);\n"
           "-- the the results of comparing of the time and the amount of\n"
           "   memory when using these 2 algorithms (simulated and standard) for this exact operation\n\n"
           , MAXNSHOWN, MAXNSHOWN);
}


