#include "cstring_test.h"


char cstring_test()
{
    char ret=1;
    ret=ret*cstring_add_chars_test();
    ret=ret*TCstrings_concst_test();
    ret=ret*TCstrings_concat_multi_test();

    return ret;
}

char cstring_add_chars_test()
{
    print_blue("cstring_add_chars>>>>>\n");
    char* str =cstring_new_clone("hello world!");
    str[6]=0;
    cstring_add(&str,"mimi");

    char ret = cstring_is_equal(str,"hello mimi");
    test_v1(ret);
    return ret;
}

char TCstrings_concst_test()
{
//    print_blue("TCstrings_concst>>>>>\n");
//    TCstrings * list =TCstrings_new();
//    TCstrings_init(list);
//    TArray_add(list,cstring_new_clone("hello world!"));
//    TArray_add(list,cstring_new_clone("I am nour"));
//    TArray_add(list,cstring_new_clone("I Love Her"));
//    char* str= TCstrings_concat(list," \n");
//    char ret = cstring_is_equal(str,"hello world! \nI am nour \nI Love Her \n");
//    test_v1(ret);
    return 1;
}

char TCstrings_concat_multi_test()
{
    print_blue("TCstrings_concat_multi");
    char ret=1;
    char* s=TCstrings_concat_multi("hello %s , I am %s , my age is %d , my salary is %f",
                           "Sofia","Nour",43,12.7);
    ret =cstring_is_equal(s,"hello Sofia , I am Nour , my age is 43 , my salary is 12.700000");
    test_v1(ret);
    return ret;
}
