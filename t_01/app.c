#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MANTLEN 30
#define MANTLENROUND 31
#define ORDLEN 5
#define INTLEN 30

#define OK 0
#define ERRNOSIGN -1
#define ERRTOOLONGMANT -2
#define ERRLETTER -3
#define ERRORDER -4
#define ERRTOOLONGINT -5
#define ERRNOTHING -6
#define ERRZERO -7
#define ERRMZ -8
#define ERRPEREPOLN -9
#define EMPTYINPUT -10

//структура для представления вещественных чисел
typedef struct
{
    char sign; //знак мантиссы
    short int mant[MANTLENROUND];//значащие цифры мантиссы31 разряд будет использован для округления
    int order; //порядок
} float_struct;

//структура для представления целого числа
typedef struct
{
    char sign; //знак числа
    short int integer[INTLEN]; //значащие цифры числа
} integer_struct;

typedef short int digit; //тип для хранения цифр
typedef short int index; //тип для хранения индексов

// функция осуществляет вывод информации о программе на экран
//входные данные: -
//изменяемые данные: -
//выходные данные: -
void show_info(void)
{
    printf("The program can divide a real (float) number by an integer.\n\n");
    printf("Format and range of input data:\n");
    printf("First enter a real number in the format    'S1m.nES2K'    , where:\n"
           "--S1 and S2 are the mantissa sign and the order sign respectively (S1 MUST be entered, S2 - AT WILL),\n"
           "--the total length of mantissa (m+n) is up to 30 significant digits,\n"
           "--value of the order K is up to 5 digits (from -99999 to 99999)\n"
           "--the symbol of exponenta can be both small and big ('e' or 'E')\n");
    printf("Th+2+2+en enter an integer in the format   'Sd'   , where:\n"
           "--S is the sign of an integer (MUST be entered),\n"
           "--d is the number, total length of d is up to 30 significant digits long\n\n");
    printf("Format of output data:\n");
    printf("If input and division were completed correctly,you will get a real number in the format  'S10.m1ES2k1' , where:\n"
           "--S1 and S2 are the mantissa sign and the order sign respectively,\n"
           "--m1 - mantissa is up to 30 significant digits,\n"
           "--k1 is up to 5 digits (from -99999 to 99999)\n"
           "Otherwise, you will get the information about an occured error\n\n");
}

//функция осуществляет ввод действительного числа (со встроенной нормализацией)
//входные данные: - адрес структуры (float_struct *x)
//изменяемые данные: - структура (float_struct x) заполняется введенным числом
//выходные данные: -код ошибки или 0
int input_float(float_struct *x)
{
    short int add_to_order = 0;
    char ch;
    _Bool met_dot = 0, met_digit = 0;
    //Вывод информации
    printf("Enter a real number (example to help):\n");
    printf("-123456789012345.678901234567890E-12345\n");

    ch = getchar();
    if (ch == '\n')
        return EMPTYINPUT;//проверка на пустой ввод

    //ввод знака
    if ((ch != '-') && (ch != '+'))
        return ERRNOSIGN;
    x->sign = ch;

    //запись значащих цифр мантиссы
    index i_mant;
    for (i_mant = 0, ch = getchar(); (ch != '\n') && (ch != 'E') && (ch != 'e'); ch = getchar())
    {
        if (i_mant == MANTLEN)
            return ERRTOOLONGMANT;//переполнение мантиссы
        if (ch == '.')
        {
            if (!met_dot)
                met_dot = 1; //встечена точка
            else
                return ERRLETTER;
        }
        else
        {
            //введена цифра
            if ((ch >= '0') && (ch <= '9'))
            {
                //до десятичной точки
                if (!met_dot)
                {
                    //является значащей
                    if ((ch > '0') || (i_mant > 0))
                    {
                        x->mant[i_mant++] = atoi(&ch);
                        add_to_order++;
                        met_digit = 1;
                    }
                }
                //после десятичной точки
                else
                {
                    //является значащей
                    if ((ch > '0') || (met_digit))
                    {
                        x->mant[i_mant++] = atoi(&ch);
                        met_digit = 1;
                    }
                    //не является значащей
                    else
                        add_to_order--;
                }
            }
            //встречена буква
            else
                return ERRLETTER;
        }
    }
    //число записано в экспоненциальной форме
    if ((ch == 'e') || (ch == 'E'))
    {
        //ввод порядка
        if ((scanf("%d", &(x->order)) != 1) || (x->order > 99999) || (x->order < -99999))
            return ERRORDER;
        getchar();
    }
    if (i_mant == 0)
        return ERRNOTHING;//нет значащих цифр мантиссы
    x->order += add_to_order;//изменение порядка при нормализации
    return OK;//ввод прошел успешно
}

//функция осуществляет ввод целого числа
//входные данные: - адрес структуры (integer_struct *y),
//                  указатель на количество значащих цифр в числе (short int *integer_len)
//изменяемые данные: - структура (y) заполняется введенным числом,
//                     integer_len содержит количество значащих цифр
//выходные данные: -код ошибки или 0
int input_integer(integer_struct *y, short int *integer_len)
{
    char ch;
    _Bool zero = 1;
    //вывод информации
    printf("\nEnter an integer (example to help):\n");
    printf("+123456789012345678901234567890\n");

    ch = getchar();
    if (ch == '\n')
        return EMPTYINPUT;//пустой ввод
    //ввод знака
    y->sign = ch;
    if ((y->sign != '-') && (y->sign != '+'))
        return ERRNOSIGN;

    ch = getchar();
    for (index i = 0; ch != '\n'; ch = getchar())//ввод значащих цифр числа
    {
        if (i == INTLEN)
            return ERRTOOLONGINT;//переполнение
        //введена цифра
        if ((ch >= '0') && (ch <= '9'))
        {
            //цифра является значащей
            if (ch > '0' || !zero)
            {
                zero = 0;
                y->integer[(*integer_len)] = atoi(&ch);
                (*integer_len)++;
                i++;
            }
        }
        else
            return ERRLETTER;//введено нечисловое значение
    }
    if (zero)
        return ERRZERO;//попытка деления на нуль
    return OK;//ввод прошел успешно
}

//функция осуществляет вывод действительного числа на экран (только значащих цифр)
//входные данные: - структура (float_struct x),
//изменяемые данные: -
//выходные данные: -
void print_float(float_struct x)
{
    printf("%c0.", x.sign);//вывод знака
    for (index i = MANTLEN - 1; i >= 0; i--)
        if (x.mant[i])
        {
            for (index j = 0; j <= i; j++)//вывод значащих цифр
                printf("%d", x.mant[j]);
            i = -1;
        }
    //вывод экспоненты
    printf("E");
    if (x.order > 0)
        printf("+");
    printf("%d\n", x.order);
}

//функция осуществляет нормализацию действительного числа
//входные данные: - адрес структуры (float_struct *x),
//изменяемые данные: - число в стурктуре x нормализуется
//выходные данные: - код ошибки или 0
int normalize(float_struct *x)
{
    short int delete_from_order = 0;
    for (index i = 0; i < MANTLEN; i++)
    {
        //подсчет незначащих цифр
        if (x->mant[i] == 0)
            delete_from_order++;
        else
            break;
    }
    //если были незначащие цифры
    if (delete_from_order > 0)
    {
        //сдвиг
        for (index i = 0; i + delete_from_order < MANTLEN; i++)
            x->mant[i] = x->mant[i + delete_from_order];
        for (index i = MANTLEN - delete_from_order; i <= MANTLEN; i++)
            x->mant[i] = 0;
    }
    //изменение порядка
    x->order -= delete_from_order;
    if (x->order < -99999)
        return ERRMZ;//машинный нуль
    if (x->order > 99999)
        return ERRPEREPOLN;//машинный нуль
    return OK;
}

//промежуточная функция для операции деления
//функция считает, сколько раз можно вычесть из первого числа второе, чтобы первое осталось неотрицательным
//входные данные: - цифры первого числа (short int x_final[]),
//                 цифры второго числа (short int y[]),
//                 количество значащих цифр в первом числе (short int len_x),
//                 количество значащих цифр во втором числе (short int len_y),
//
//изменяемые данные: - в первом числе (short int x_final[]) останется остаток от вычитаний
//выходные данные: - произведенное количество вычитаний
int max_minus(short int x_final[], short int y[], short int len_x, short int len_y)
{
    //копирование числа x_final в локальную переменную
    digit x[MANTLENROUND] = {0};
    for (index i = 0; i < len_x; i++)
        x[i] = x_final[i];

    short int result = -1;
    _Bool works = 1;
    //пока получается вычесть, прибавляем к результату 1
    for (; works; result++)
    {
        //вычитаем, начиная с последнего разряда
        for (index i = 1; (i < len_y + 1) && works; i++)
        {
            //если получилось вычесть без заимствования
            if (x[len_x - i] >= y[len_y - i])
                x[len_x - i] -= y[len_y - i];
            //инчае пытаемся занять из старших разрядов
            else
            {
                for (index j = i + 1; (j < len_x + 1) && (x[len_x - i] < 10); j++)
                    if (x[len_x - j] > 0)
                    {
                        x[len_x - j]--;
                        for (index k = j - 1; k != i; k--)
                            x[len_x - k] += 9;
                        x[len_x - i] += 10;
                    }
                //если получилось занять
                if (x[len_x - i] >= y[len_y - i])
                    x[len_x - i] -= y[len_y - i];
                //иначе прекращаем вычитание
                else
                    works = 0;
            }
        }
        //если вычитаение прошло успешно, то можем изменить исходное число и продолжить вычитание
        if (works)
            for (index i = 0; i < len_x; i++)
                x_final[i] = x[i];

    }
    return result;
}

//функция, осуществляющая деление "в столбик" первого (вещественного) числа на второе (целое)
//входные данные: - первое число (float_struct *x)
//                 второе число (integer_struct y),
//                 количество значащих цифр во втором числе (short int len_y),
//                 адрес структуры результата - вещественного числа (float_struct *result)
//изменяемые данные: - в первом числе (short int x_final[]) останется остаток от деления
//                   - в структуре, result останется результат деления
//выходные данные: -
void division(float_struct *x, integer_struct y, short int len_y, float_struct *result)
{
    index i_beg; //начало отрезка мантиссы делимого, из которого будем вычитать
    index i_end; //конец отрезка мантиссы делимого, из которого будем вычитать
    index i_res; //разряд результата, который сейчас вычисляем
    digit tek_res; //полученное значение текущего разряда

    result->sign = x->sign == y.sign ? '+': '-';//определяем знак результата
    result->order = x->order;//определяем порядок результата
    //производим деление "в столбик", пока не дойдем до конца мантиссы
    for (i_beg = 0, i_end = 0, i_res = 0; i_end < MANTLENROUND; i_end++, i_res++)
    {
        //вычисляем значение для текущего разряда мантиссы результата
        tek_res = max_minus(&(x->mant[i_beg]), y.integer, i_end - i_beg + 1, len_y);
        result->mant[i_res] = tek_res;
        //получилось вычесть - значит сдвигам начало отрезка мантиссы делимого, из которого будем вычитать на 1 вправо
        if ((x->mant[i_beg]) == 0)
            i_beg++;
    }
}

//функция, осуществляющая округление результата (до 30 значащих цифр в мантиссе)
//входные данные: - результат деления - вещественное число (float_struct *x)
//изменяемые данные: - результат деления - вещественное число (float_struct *x) будет округлен
//выходные данные: -
void round_f(float_struct *x)
{
    //если 31 разряд >= 5, значит нужно округлять
    if ((x->mant[MANTLENROUND - 1]) >= 5)
    {
        //к 30 разряду прибавляем 1
        x->mant[MANTLENROUND - 2]++;
        //производим цикличное округление, пока это требуется
        for (index i = MANTLENROUND - 2; i > 0; i--)
        {
            if ((x->mant[i]) > 9)
            {
                x->mant[i] = 0;
                (x->mant[i - 1])++;
            }
            else
                break;
        }
        //если число перестало быть нормализованным, сдвигаем разряды
        if ((x->mant[0]) > 9)
        {
            for (index i = MANTLENROUND - 1; i > 1; i--)
                x->mant[i] = x->mant[i - 1];
             x->mant[0] = 1;
             x->mant[1] = 0;
             x->order++;
        }
    }
    //помечаем 31 разряд как незначащий
    x->mant[MANTLENROUND - 1] = 0;
}

//главная функция main, без параметров,
//возвращает код ошибки или 0 в случае успешного завершения
int main(void)
{
    setbuf(stdout, NULL);
    int rc = OK;
    short int integer_len = 0;

    //создаю и обнуляю структуры для делимого, делителя и результата
    float_struct x;
    integer_struct y;
    float_struct result;
    memset(&x, 0, sizeof(float_struct)); 
    memset(&y, 0, sizeof(integer_struct));
    memset(&result, 0, sizeof(float_struct));

    //вывожу общую информации о программе
    show_info();

    //ввожу первое (действительное) число
    rc = input_float(&x);
    //если первое число введено корректно
    if (rc == OK)
    {
        //нормализую введенное число
        normalize(&x);
        //ввожу второе (целое) число
        rc = input_integer(&y, &integer_len);
        //если второе число введено корректно
        if (rc == OK)
        {
            division(&x, y, integer_len, &result);//делю
            round_f(&result);//округляю
            rc = normalize(&result);//нормализую
            //если нормализация прошла успешно
            if (rc == OK)
            {
                //вывожу результат
                printf("\nDivision went successfully, result:\n");
                print_float(result);
            }
        }
    }
    //если в программе произошла ошибка, вывожу соответствующее сообщение
    printf("\n");
    if (rc == ERRNOSIGN)
        printf("ERROR: didn't get a sign where expected");
    if (rc == ERRTOOLONGMANT)
        printf("ERROR: the mantissa is too long (m+n) is more than 30 significant digits");
    if (rc == ERRLETTER)
        printf("ERROR: met an unknown symbol");
    if (rc == ERRORDER)
        printf("ERROR: incorrect order input: less than -99999 or more than 99999 or met an unknown symbol");
    if (rc == ERRTOOLONGINT)
        printf("ERROR: the integer has more than 30 significant digits");
    if (rc == ERRNOTHING)
        printf("The mantissa has no significant digits: 0 divided by any number is 0");
    if (rc == ERRZERO)
        printf("ERROR: can't divide by zero");
    if (rc == ERRMZ)
        printf("ERROR: met a machine zero");
    if (rc == ERRPEREPOLN)
        printf("ERROR: as a result of normalization, an order overflow occured");
    if (rc == EMPTYINPUT)
        printf("ERROR: empty input");

    return rc;
}
