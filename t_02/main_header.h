#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define AMOUNT 5000
#define AUTHORLEN 25
#define NAMELEN 25
#define PUBLEN 25
#define FIELDLEN 15
#define COMMANDLEN 20

#define MINYEAR 0
#define MAXYEAR 2100
#define MINPAGE 1
#define MAXPAGE 9999

#define OK 0
#define ERRCOMMAND -1
#define ERROPEN -2
#define ERREMPTY -3
#define ERRVALUE -4
#define TOOMANY -5
#define EXIT -6
#define ERRCOMPARE -7

typedef struct
{
    char author[AUTHORLEN + 1];
    char name[NAMELEN + 1];
    char pub[PUBLEN + 1];
    int pages;
    int type_l; //1-technical, 2 - fictional, 3- childish
    union {
        struct {
            char field[FIELDLEN + 1];
            int origin; //1-domestic, 2 - translated
            int year;
        } tech;
        int fict; //1-novel, 2 - play, 3 - poems
        int child; // 1 - fairytale, 2 - poems
    } type_l_inf;
} book_struct;

#endif // MAIN_HEADER_H
