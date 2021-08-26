#include "do_test.h"


char do_test()
{
    char ret=1;
    ret=ret*mnfield_test();
    ret=ret*cstring_test();
    ret=ret*mnarray_test();

    return ret;

}
