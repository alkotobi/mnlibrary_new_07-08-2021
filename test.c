#include "test.h"
void print_red(char *message)
{
    printf(ANSI_COLOR_RED);
    printf("%s",message);
    printf(ANSI_COLOR_RESET);

}

void print_green(char *message)
{
    printf(ANSI_COLOR_GREEN);
    printf("%s",message);
    printf(ANSI_COLOR_RESET);

}

void print_yellow(char *message)
{
    printf(ANSI_COLOR_YELLOW);
    printf("%s",message);
    printf(ANSI_COLOR_RESET);
}

void print_blue(char *message)
{
    printf(ANSI_COLOR_BLUE);
    printf("%s",message);
    printf(ANSI_COLOR_RESET);
}

void print_magenta(char *message)
{
    printf(ANSI_COLOR_MAGENTA);
    printf("%s",message);
    printf(ANSI_COLOR_RESET);
}

void print_cyan(char *message)
{
    printf(ANSI_COLOR_CYAN);
    printf("%s",message);
    printf(ANSI_COLOR_RESET);
}

char test(char bool_res, char *pass_message)
{
    if(bool_res){
        print_green(pass_message);

    }else {
        printf(ANSI_COLOR_RED "not ");
        print_red(pass_message);

}
    return bool_res;
}

char test_v1(char bool_res)
{
    return test(bool_res,"working\n");
}
