#ifndef TEST_H
#define TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_red(char* message);
void print_green(char* message);
void print_yellow(char* message);
void print_blue(char* message);
void print_magenta(char* message);
void print_cyan(char* message);
char test(char bool_res, char* message);
char test_v1(char bool_res);

#ifdef __cplusplus
}
#endif



#endif // TEST_H
