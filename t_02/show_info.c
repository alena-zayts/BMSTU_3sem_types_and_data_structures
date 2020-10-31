#include "main_header.h"

//вывод информации о программе
void show_main_information(void)
{
    printf("This program works with a list of literature (up to %d records),"
           " each record contains:\n\n", AMOUNT);
    printf("-author surname (up to %d symbols);\n", AUTHORLEN);
    printf("-book name (up to %d symbols);\n", NAMELEN);
    printf("-publishing house (up to %d symbols);\n", PUBLEN);
    printf("-number of pages (from %d to %d);\n", MINPAGE, MAXPAGE);
    printf("-type of literature: (1 or 2 or 3)\n");
    printf("    1 - technical\n");
    printf("        field (up to %d symbols);\n", FIELDLEN);
    printf("        origin: (1 or 2)\n");
    printf("            1 - domestic\n");
    printf("            2 - translated;\n");
    printf("        year of publishing (from %d to %d);\n", MINYEAR, MAXYEAR);
    printf("    2 - fiction\n");
    printf("        type: (1 or 2 or 3)\n");
    printf("            1 - novel\n");
    printf("            2 - play\n");
    printf("            3 - poems;\n");
    printf("    3 - childish\n");
    printf("        type: (1 or 2)\n");
    printf("            1 - fairytale\n");
    printf("            2 - poems;\n\n");
}
//вывод возможных команд
void show_commands(void)
{
    printf("Interaction with the program is carried out via the command line using only English.\n");
    printf("Symbol \"$\" means that the program is waiting for your command.\n\n");

    printf("Possible commands:\n");
    printf("help             |show information about the program and a list of possible commands;\n");
    printf("how              |show the information about the range of input values;\n\n");
    printf("amount           |show the amount of records in the existing literature list;\n\n");

    printf("clean            |clean the existing in the program list of literature;\n");
    printf("delete           |delete records by a value of author surname;\n\n");

    printf("input_prepared   |import the prepared list of literature from file literature.txt;\n");
    printf("input_my         |input your own list of literature;\n");
    printf("input_one        |add one book to the end of the existing list of literature;\n\n");


    printf("show_compare     |show a comparative table of the efficiency of using different sorting\n");
    printf("                  algoriythms and approaches;\n");//
    printf("show_tech        |show the list of domestic technical literature on the specified field;\n");
    printf("show_key_table   |show the current state of the table of keys;\n");
    printf("show_main_table  |show the current state of the list of literature;\n\n");


    printf("sort_main_bubble |sort and show the list of literature by inc. of number"
           " of pages using \"bubble\" algorythm;\n");
    printf("sort_main_quick  |sort and show the list of literature by inc. of number"
           " of pages using \"quick\" algorythm;\n");
    printf("sort_key_bubble  |show the list of literature in sorted form by sorting key table by inc. of\n"
           "                  number of pages using \"bubble\" algorythm;\n");
    printf("sort_key_quick   |show the list of literature in sorted form by sorting key table by inc. of\n"
           "                  number of pages using \"quick\" algorythm;\n");

    printf("exit             |exit the program\n\n");

}
