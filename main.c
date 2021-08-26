#include <stdio.h>
#include "mnarray.h"
#include "do_test.h"

int main()
{
    if(do_test()){
        print_red("Hello World! 🙂\n");
    }else {
        print_magenta("Hello World! 🙁\n");
    }

    return 0;
}
