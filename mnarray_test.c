#include "mnarray_test.h"



char mnarray_test()
{
    char ret=1;

    ret=ret*TArray_new_test();
    ret=ret*TArray_init_test();
    ret=ret*TArray_add_ref_test();
    ret=ret*TArray_free_data_test();
    ret=ret*TArray_count_test();
    ret=ret*TArray_size_test();
    ret=ret*TArray_item_at_test();
    ret=ret*TArray_remove_item_ret_ref_test();
    ret=ret*TArrayData_free_data_test();
    ret=ret*TArrayData_add_cpy_test();
    ret=ret*TArrayData_add_ref_test();
    ret=ret*TArrayData_find_first_test();
    ret=ret*TArrayData_add_or_replace_test();
    return ret;
}

char TArray_new_test()
{
    print_blue("testing TArray_new \n");
    TArray* ar= TArray_new();
    TArray_init(ar);
    char res= ar!=0;
    TArray_free_data(ar,0);
    TArray_free((TPtrHld)&ar);
    test_v1(res);
    return res;
}

char TArray_init_test()
{
    print_blue("TArray_init\n");
    TArray ar;
    TArray_init(&ar);
    char res=1;
    res=res*(ar.params_prv.array!=0);
    res=res*(ar.params_prv.count==0);
    res=res*ar.params_prv.size==ARRAY_MIN_SIZE;
    test_v1(res);
    return res;
}



char TArray_add_ref_test()
{
    print_blue("TArray_add_ref\n");
    TArray arr;
    TArray_init(&arr);
    int i=5;
    int b=6;

    TArray_add(&arr,(TVar)&i);
    TArray_add(&arr,(TVar)&b);
    char ret=*((int*)TArray_item_at(&arr,0))==5;
    ret=ret*(*((int*)TArray_item_at(&arr,1))==6);
    test_v1(ret);
    return ret;
}





char TArray_free_data_test()
{
    print_blue("TArray_free\n");
    char* str =cstring_new_clone("hello");
    TArray* arr=TArray_init(TArray_new());

    TArray_add(arr,str);
    TArray_add(arr,cstring_new_clone("yes"));
    TArray_free_data(arr,cstring_free);
    char res = arr->params_prv.count==0;
    TArray_free($P(arr));
    test_v1(res);
    return res;
}

char TArray_count_test()
{
    print_blue("TArray_count\n");
    char* str =cstring_new_clone("hello");
    TArray arr;
    TArray_init(&arr);
    TArray_add(&arr,str);
    TArray_add(&arr,cstring_new_clone("yes"));
    char res = TArray_count(&arr)==2;
    TArray_free_data(&arr,cstring_free);

    test_v1(res);
    return arr.params_prv.count==0;
}

char TArray_size_test()
{
    print_blue("TArray_size\n");
    TArray arr;
    TArray_init(&arr);
    char ret = TArray_size(&arr)==ARRAY_MIN_SIZE;
    test_v1(ret);
    TArray_free_data(&arr,0);
    return ret;
}

char TArray_item_at_test()
{
    print_blue("TArray_item_at\n");
    char* str =cstring_new_clone("hello");
    TArray arr;
    TArray_init(&arr);
    TArray_add(&arr,str);
    TArray_add(&arr,cstring_new_clone("yes"));
    char res = TArray_count(&arr)==2;
    char* str1=(char*)TArray_item_at(&arr,0);
    res=res*cstring_is_equal(str1,"hello");
    str1=(char*)TArray_item_at(&arr,1);
    res=res*cstring_is_equal(str1,"yes");
    TArray_free_data(&arr,cstring_free);
    test_v1(res);
    return res;
}

char TArray_remove_item_ret_ref_test()
{
    print_blue("TArray_remove_item_ret_ref\n");
    char* str =cstring_new_clone("hello");
    TArray arr;
    TArray_init(&arr);
    TArray_add(&arr,str);
    TArray_add(&arr,cstring_new_clone("yes"));
    char res = TArray_count(&arr)==2;
    char* str1=(char*)TArray_item_at(&arr,0);
    res=res*cstring_is_equal(str1,"hello");
    str1=(char*)TArray_item_at(&arr,1);
    res=res*cstring_is_equal(str1,"yes");
    str1=(char*)TArray_remove_item_ret_ref(&arr,0);
    res=res*cstring_is_equal(str1,"hello");
    res=res*TArray_count(&arr)==1;
    str1=(char*)TArray_item_at(&arr,0);
    res=res*cstring_is_equal(str1,"yes");
    TArray_free_data(&arr,cstring_free);
    test_v1(res);
    return res;
}



char TArrayData_free_data_test()
{
    print_blue("some tests arround TArrayData_free_data\n");
    TArrayData arr;
    TArrayData_init(&arr);
    TCstring str1=cstring_new_clone("hello");
    TCstring str2=cstring_new_clone("me");
    TCstring str3=cstring_new_clone("third");
    TData* data = TData_init_cstring(TData_new(),str3);
    TData_set_name(data,"charli");
    char* str = TData_name(data);
    str++;
    TArrayData_add_presistent(&arr,TData_init_cstring(TData_new(),str1));
    TArrayData_add(&arr,TData_init_cstring(TData_new(),str2));
    TArrayData_add_clone(&arr,data);
    TArrayData_clean(&arr);
    //free(str1);
    //free(str2);
    test_v1(1);
    return 1;
}

TData *TArrayData_migrating_test()
{
    TCstring str1=cstring_new_clone("hello");
    TData* data = TData_init_cstring(TData_new(),str1);
    return data;
}

char TArrayData_add_cpy_test()
{
    print_blue("TArrayData_add_clone\n");
    TArrayData arr;
    TArrayData_init(&arr);
    TCstring str3=cstring_new_clone("third");
    TData* data = TData_init_cstring(TData_new(),str3);
    TArrayData_add_clone(&arr,data);
    TArrayData_clean(&arr);
    TData_clean(data);
    TData_free($P(data));
    test_v1(1);
    return 1;
}

char TArrayData_add_ref_test()
{
    print_blue("TArrayData_add\n");
    TArrayData arr;
    TArrayData_init(&arr);
    TCstring str3=cstring_new_clone("third");
    TData* data = TData_init_cstring(TData_new(),str3);
    TArrayData_add(&arr,data);
    TArrayData_clean(&arr);
    //TData_clean(data);
    //TData_free($P(data));
    test_v1(1);
    return 1;
}

char TArrayData_find_first_test()
{
    print_blue("TArrayData_find_first\n");
    TArrayData arr;
    TArrayData_init(&arr);
    TCstring str1=cstring_new_clone("hello");
    TCstring str2=cstring_new_clone("me");
    TCstring str3=cstring_new_clone("third");
    TData* data = TData_init_cstring(TData_new(),str3);
    TArrayData_add_presistent(&arr,TData_init_cstring(TData_new(),str1));
    TArrayData_add(&arr,TData_init_cstring(TData_new(),str2));
    TArrayData_add_clone(&arr,data);
    data = TData_init_cstring(TData_new(),cstring_new_clone("third"));
    TLint index= TArrayData_find_first(&arr,data);
    TData_free($P(data));
    TArrayData_clean(&arr);
    //free(str1);
    //free(str2);
    test_v1(index==2);
    return 1;
}

char TArrayData_add_or_replace_test()
{
    print_blue("TArrayData_add_or_replace\n");
    TArrayData arr;
    TArrayData_init(&arr);
    TCstring str1=cstring_new_clone("hello");
    TCstring str2=cstring_new_clone("me");
    TCstring str3=cstring_new_clone("third");
    TData* data = TData_init_cstring(TData_new(),str3);
    TArrayData_add_presistent(&arr,TData_init_cstring(TData_new(),str1));
    TArrayData_add(&arr,TData_init_cstring(TData_new(),str2));
    TArrayData_add_clone(&arr,data);
    data = TData_init_cstring(TData_new(),cstring_new_clone("third"));
    TArrayData_add_or_replace(&arr,data);
    TLint index= TArrayData_find_first(&arr,data);
    char ret=TArray_count(&arr)==3;

    test_v1(index==2 && ret);
    return 1;
}
