#include "tvariant_test.h"



char TVariant_test()
{
    print_blue("testing printing variant\n");
    TVariant* var = TVariant_init_int(TVariant_new(),5);
    char* str=TVariant_to_new_cstring(var);
    print_red(str);
    var = TVariant_init_cstring(TVariant_new(),"hello");
    str=TVariant_to_new_cstring(var);
    print_red(str);
    var = TVariant_init_double(TVariant_new(),123.676);
    str=TVariant_to_new_cstring(var);
    print_red(str);
    printf("\n");
    var = TVariant_init_int(TVariant_new(),123);
    str=TVariant_to_new_cstring(var);
    print_red(str);
    var = TVariant_init_cstring(TVariant_new(),"memo tab colo bara tipo");
    str=TVariant_to_new_cstring(var);
    print_red(str);
    var = TVariant_init_double(TVariant_new(),12.6);
    str=TVariant_to_new_cstring(var);
    print_red(str);
    printf("\n");
    var = TVariant_init_int(TVariant_new(),123);
    str=TVariant_to_new_cstring(var);
    print_red(str);
    var = TVariant_init_cstring(TVariant_new(),"memo tab colo bara tipo");
    str=TVariant_to_new_cstring(var);
    print_red(str);
    var = TVariant_init_double(TVariant_new(),12.6);
    str=TVariant_to_new_cstring(var);
    print_red(str);
    printf("\n");
    return 1;
}
