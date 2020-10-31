#include "main_header.h"
#include "show_info.h"
#include "free_array.h"
#include "stack_array.h"
#include "stack_list.h"
#include "stack_operations.h"
#include "tick.h"

//сравнение времени для различных реализаций стека
//и различного количества элементов в стеке
int compare(int max_capacity, int n_povt)
{
    free_arr_s *fmem = NULL;
    stack_list_s *root = NULL;
    stack_arr_s *stack = NULL;
    uint64_t t_popl = 0, t_popa = 0, t_pushl = 0, t_pusha = 0, t_opl = 0, t_opa = 0;
    uint64_t time, start, end;
    int el;
    int amount;

    for (int povt = 0; povt < n_povt; povt++)
    {
        //создание и заполнение стеков
        stack = create_stack_arr(max_capacity);
        if (stack == NULL)
        {
            printf("MEMORY ERROR. Couldn't allocate stack-array.\n"
                   "Try again with smaller maximum amount of elements in stack-array.\n"
                   " Exiting program..");
            free_stack_arr(stack);
            free_stack_list(&root, fmem);
            free_free_arr(fmem);
            return ERRMEM;
        }

        fmem = create_free_arr(max_capacity * max_capacity);
        if (fmem == NULL)
        {
            printf("MEMORY ERROR. Couldn't allocate array of free memory.\n"
                   "Try again with smaller maximum amount of elements in stack-list.\n"
                   "Exiting program..");
            free_stack_arr(stack);
            free_stack_list(&root, fmem);
            free_free_arr(fmem);
            return ERRMEM;
        }

        for (int i = 0; i < (max_capacity); i++)
        {
            push_stack_arr(stack, (-1*i)%10, &time);
            if (push_stack_list(&root, (-1*i)%10, &time))
            {
                printf("MEMORY ERROR. Couldn't allocate stack-list.\n"
                       "Try again with smaller maximum amount of elements in stack-list.\n"
                       "Exiting program..");
                free_stack_arr(stack);
                free_stack_list(&root, fmem);
                free_free_arr(fmem);
                return ERRMEM;
            }
        }

        //время удаления элемента
        pop_stack_arr(stack, &el, &time);
        t_popa += time;
        pop_stack_list(&root, fmem, &el, &time);
        t_popl += time;

        //время добавления элемента

        push_stack_arr(stack, 1, &time);
        t_pusha += time;
        if (push_stack_list(&root, 1, &time))
        {
            printf("MEMORY ERROR. Couldn't allocate stack-list.\n"
                   "Try again with smaller maximum amount of elements in stack-list.\n"
                   "Exiting program..");
            free_stack_arr(stack);
            free_stack_list(&root, fmem);
            free_free_arr(fmem);
            return ERRMEM;
        }
        t_pushl += time;

        //вывод убывающих серий в обратном порядке

        {
            printf("Decreasing subsequences in stack-array:\n");
            start = tick();
            amount = dec_order_arr(stack);
            end = tick();
            t_opa += (end - start);
            if (!amount)
                printf("Decreasing subsequences not found\n");


            printf("Decreasing subsequences in stack-list:\n");
            start = tick();
            amount = dec_order_list(&root, fmem);
            end = tick();
            t_opl += (end - start);
            if (!amount)
                printf("Decreasing subsequences not found\n");
         }

        free_stack_arr(stack);
        free_stack_list(&root, fmem);
        free_free_arr(fmem);
    }
    //вывод результатов
    printf("\nMean time in ticks for %d measurements:\n\n", n_povt);
    printf("Pop %d of %d element to stack:\n", max_capacity, max_capacity);
    printf("stack-array: %ju\n", t_popa/n_povt);
    printf("stack-list: %ju\n\n", t_popl/n_povt);
    printf("Push %d of %d element to stack:\n", max_capacity, max_capacity);
    printf("stack-array: %ju\n", t_pusha/n_povt);
    printf("stack-list: %ju\n\n", t_pushl/n_povt);
    printf("Displaying decreasing subsequences in stack of %d elements\n", max_capacity);
    printf("stack-array: %ju\n", t_opa/n_povt);
    printf("stack-list: %ju\n\n", t_opl/n_povt);
    return OK;
}

int main(void)
{
    setbuf(stdout, NULL);
    //return compare(100, 100);
    int capacity, max_capacity;
    free_arr_s *fmem = NULL;
    stack_list_s *root = NULL;
    stack_arr_s *stack = NULL;

    int cmd = -1;
    int el, amount;
    uint64_t start, end, time;

    show_info();
    show_commands();

    while (cmd)
    {
        //ввод команды
        printf("\nInput command:\n");
        fflush(stdin);
        while ((fscanf(stdin, "%d", &cmd) != 1) || (cmd < MINCOMMAND) || (cmd > MAXCOMMAND) ||
               (getchar() != '\n'))
        {
            printf("ERROR: unknown command.\n");
            show_commands();
            printf("Try to input command again:\n");
            fflush(stdin);
        }
        //выполнение команды
        {
            //создание стека-массива и заполнение начальными значениями
            if (cmd == 1)
            {
                if (stack)
                    printf("ERROR: stack-array already exists\n");
                else
                {
                    printf("Input maximum amount of elements in stack-array (int, >=0):\n");
                    fflush(stdin);
                    while ((fscanf(stdin, "%d", &max_capacity) != 1) || (max_capacity < 0)
                           || (getchar() != '\n'))
                    {
                        printf("ERROR: incorrect amount. Try again\n");
                        fflush(stdin);
                    }

                    stack = create_stack_arr(max_capacity);
                    if (stack == NULL)
                    {
                        printf("MEMORY ERROR. Couldn't allocate stack.\n"
                               "Try again with smaller maximum amount of elements in stack-array.\n"
                               " Exiting program..");
                        free_stack_arr(stack);
                        free_stack_list(&root, fmem);
                        free_free_arr(fmem);
                        return ERRMEM;
                    }

                    printf("Input initial amount of elements in stack-array (int, >=0 and <=%d):\n", max_capacity);
                    fflush(stdin);
                    while ((fscanf(stdin, "%d", &capacity) != 1) || (capacity < 0)
                           || (capacity > max_capacity) || (getchar() != '\n'))
                    {
                        printf("ERROR: incorrect initial amount. Try again\n");
                        fflush(stdin);
                    }
                    input_stack_arr(capacity, stack, &time);
                }
            }
            //добавление элемента в стек-массив
            if (cmd == 2)
            {
                if (stack == NULL)
                    printf("ERROR: first create a stack-array\n");
                else
                {
                    if (is_full_stack_arr(stack))
                        printf("ERROR: stack-array is already full\n");
                    else
                    {
                        input_stack_arr(1, stack, &time);
                        printf("Elapsed time in ticks: %ju\n", time);
                    }
                }
            }
            //удаление элемента из стека-массива
            if (cmd == 3)
            {
                if (stack == NULL)
                    printf("ERROR: first create a stack-array\n");
                else
                {
                    if (is_empty_stack_arr(stack))
                        printf("ERROR: stack-array is empty\n");
                    else
                    {
                        pop_stack_arr(stack, &el, &time);
                        printf("Successfully popped element with value %d\n", el);
                        printf("Elapsed time in ticks: %ju\n", time);
                    }
                }
            }
            //стек-массив: вывести убывающие серии в обратном порядке и время обработки
            if (cmd == 4)
            {
                if (stack == NULL)
                    printf("ERROR: first create a stack-array\n");
                else if (is_empty_stack_arr(stack))
                    printf("ERROR: stack-array is empty\n");
                else
                {
                    printf("Decreasing subsequences in stack-array:\n");
                    start = tick();
                    amount = dec_order_arr(stack);
                    end = tick();
                    if (!amount)
                        printf("Decreasing subsequences not found\n");
                    printf("Elapsed time in ticks (including printing): %ju\n", (end - start));
                 }
            }
            //текущее состояние стека-массива
            if (cmd == 5)
            {
                printf("Current state of stack-array:");
                if (stack == NULL)
                    printf("Stack-array was not created yet\n");
                else
                {
                    if (is_empty_stack_arr(stack))
                        printf("stack-array is empty\n");
                    else
                        output_stack_arr(stack);
                }
            }
            //создание стека-списка и заполнение начальными значениями
            if (cmd == 6)
            {
                if (root)
                    printf("ERROR: stack-list already exists\n");
                else
                {
                    printf("Input maximum amount of elements in stack-list (int, >=0):\n");
                    fflush(stdin);
                    while ((fscanf(stdin, "%d", &max_capacity) != 1) || (max_capacity < 0)
                           || (getchar() != '\n'))
                    {
                        printf("ERROR: incorrect amount. Try again\n");
                        fflush(stdin);
                    }
                    fmem = create_free_arr(max_capacity * max_capacity);
                    if (fmem == NULL)
                    {
                        printf("MEMORY ERROR. Couldn't allocate array of free memory.\n"
                               "Try again with smaller maximum amount of elements in stack-list.\n"
                               "Exiting program..");
                        free_stack_arr(stack);
                        free_stack_list(&root, fmem);
                        free_free_arr(fmem);
                        return ERRMEM;
                    }

                    printf("Input initial amount of elements in stack-list (int, >=0 and <=%d):\n", max_capacity);
                    fflush(stdin);
                    while ((fscanf(stdin, "%d", &capacity) != 1) || (capacity < 0)
                           || (capacity > max_capacity) || (getchar() != '\n'))
                    {
                        printf("ERROR: incorrect initial amount. Try again\n");
                        fflush(stdin);
                    }
                    if (input_stack_list(capacity, &root, &time))
                    {
                        printf("MEMORY ERROR. Couldn't allocate stack-list.\n"
                               "Try again with smaller maximum amount of elements in stack-list.\n"
                               "Exiting program..");
                        free_stack_arr(stack);
                        free_stack_list(&root, fmem);
                        free_free_arr(fmem);
                        return ERRMEM;
                    }

                }
            }
            //добавление элемента в стек-список
            if (cmd == 7)
            {
                if (root == NULL)
                    printf("ERROR: first create a stack-list\n");
                else
                {
                    if (is_full_stack_list(root, max_capacity))
                        printf("ERROR: stack is already full\n");
                    else
                    {
                        if (input_stack_list(1, &root, &time))
                        {
                            printf("MEMORY ERROR. Couldn't allocate next element in stack-list.\n"
                                   "Try again with smaller maximum amount of elements in stack-list.\n"
                                   "Exiting program..");
                            free_stack_arr(stack);
                            free_stack_list(&root, fmem);
                            free_free_arr(fmem);
                            return ERRMEM;
                        }
                        printf("Elapsed time in ticks: %ju\n", time);
                        check_top_stack_list(root, fmem);
                    }
                }
            }
            //удаление элемента из стека-списка
            if (cmd == 8)
            {
                if (root == NULL)
                    printf("ERROR: first create a stack-list\n");
                else
                {
                    if (is_empty_stack_list(root))
                        printf("ERROR: stack-list is empty\n");
                    else
                    {
                        pop_stack_list(&root, fmem, &el, &time);
                        printf("Successfully popped element with value %d\n", el);
                        printf("Elapsed time in ticks: %ju\n", time);
                        cmd = 9;
                    }
                }
            }
            //вывод массива освободившихся адрессов
            if (cmd == 9)
            {
                if (root == NULL)
                    printf("ERROR: first create a stack-list and make some operations\n");
                else
                {
                    printf("Array of released addresses:\n");
                    output_free_arr(*fmem);
                }
            }
            //стек-список: вывести убывающие серии в обратном порядке и время обработки
            if (cmd == 10)
            {
                if (root == NULL)
                    printf("ERROR: first create a stack-list\n");
                else if (is_empty_stack_list(root))
                    printf("ERROR: stack-list is empty\n");
                else
                {
                    printf("Decreasing subsequences in stack-list:\n");
                    start = tick();
                    amount = dec_order_list(&root, fmem);
                    end = tick();
                    if (!amount)
                        printf("Decreasing subsequences not found\n");
                    printf("Elapsed time in ticks (including printing): %ju\n", (end - start));
                }
            }
            //текущее состояние стека-списка
            if (cmd == 11)
            {
                if (root == NULL)
                    printf("Stack-list was not created yet\n");
                else
                {
                    printf("Current state of stack-list:\n");
                    if (is_empty_stack_list(root))
                        printf("Stack-list is empty\n");
                    else
                        output_stack_list(root);
                }
            }
            //информация об используемой памяти
            if (cmd == 12)
            {
                printf("Memory, needed for stack realizations:\n");
                printf("In array realisation:\n"
                       "   %zu bytes for each element + %zu bytes needed for information about stack\n",
                       sizeof(int), sizeof(int)*2 + sizeof(int*));
                printf("In list realisation:\n"
                       "   %zu bytes for each elemnt (each includes information about stack)\n",
                       sizeof(stack_list_s));
            }
        }
    }

    free_stack_arr(stack);
    free_stack_list(&root, fmem);
    free_free_arr(fmem);
    printf("\nExiting program..");

    return OK;
}
