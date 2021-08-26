#include "mnfield_test.h"


char mnfield_test()
{

    char res=1;
    res=res* mnfield_TData_test();
    res=res*mnfield_new_int_t();
    res=res*mnfield_new_double_t();
    res=res*mnfield_new_mnstring_t();
    res=res*mnfield_setval_int_t();
    res=res*mnfield_setval_double_t();
    res=res*mnfield_setval_cstring_t();
    res=res*mnfield_clone_t();
    return res;
}


char mnfield_new_int_t()
{
    print_blue("tetsing mnfield_new_int(char*,int)...\n");
    print_magenta("tetsing mnfield_int_val(*mnfield)...\n");
    mnfield* fld=mnfield_new_int("name",10);
    char res=cstring_is_equal(TField_name(fld),"name");
    res=res*(mnfield_int_val(fld)==10);
    test(res,"mnfield_new_int is working\n mnfield_int_val is working\n");
    mnfield_clean(fld);
    mnfield_free(&fld);
    return res;

}

char mnfield_new_double_t()
{
    print_blue("tetsing mnfield_new_double(char*,double)...\n");
    print_magenta("tetsing mnfield_double_val(*mnfield)...\n");
    mnfield* fld=mnfield_new_double("name",10.5);
    char res=cstring_is_equal(TField_name(fld),"name");
    res=res*(mnfield_double_val(fld)==10.5);
    test(res,"mnfield_new_double is working\n mnfield_double_val is working\n");
    mnfield_clean(fld);
    mnfield_free(&fld);
    return res;
}

char mnfield_new_mnstring_t()
{
    print_blue("tetsing mnfield_new_mnstring(char*,double)...\n");
    print_magenta("tetsing mnfield_mnstring_val(*mnfield)...\n");
    mnfield* fld=mnfield_new_cloned_cstring("name","string");
    char res=cstring_is_equal(TField_name(fld),"name");
    TCstring str=mnfield_val_to_new_cstring(fld);
    TCstring str1="string";
    res=res*(cstring_is_equal(str,str1));
    test(res,"mnfield_new_mnstring is working\n mnfield_mnstring_val is working\n");
    mnfield_clean(fld);
    mnfield_free(&fld);
    return res;
}

char mnfield_setval_int_t()
{
    print_blue("tetsing mnfield_setval_int(int)...\n");
    mnfield* fld=mnfield_new_int("name",10);
    mnfield_setval_int(fld,15);
    char res=(mnfield_int_val(fld)==15);
    test(res,"mnfield_setval_int is working\n");
    mnfield_free(&fld);
    return res;
}

char mnfield_setval_double_t()
{
    print_blue("tetsing mnfield_setval_double(double)...\n");
    mnfield* fld=mnfield_new_double("name",10.8);
    mnfield_setval_double(fld,15.5);
    char res=(mnfield_double_val(fld)==15.5);
    test(res,"mnfield_setval_double is working\n");
    mnfield_free(&fld);
    return res;
}

char mnfield_setval_cstring_t()
{
    print_blue("tetsing mnfield_setval_cstring(fld,char*)...\n");
    mnfield* fld=mnfield_new_cloned_cstring("name","me");
    mnfield_setval_cstring(fld,"salam");
    char res=(cstring_is_equal(mnfield_cstring_val_ref(fld),"salam"));
    test(res,"mnfield_setval_cstring is working\n");
    mnfield_clean(fld);
    mnfield_free(&fld);
    return res;
}

char mnfield_clone_t()
{
    print_blue("tetsing mnfield*mnfield_clone(mnfield*fld)...\n");
    mnfield* fld=mnfield_new_cloned_cstring("name","string");
    mnfield* fldcpy=mnfield_clone(fld);
    char res=mnfield_is_equal(fld,fldcpy);
    mnfield_free(&fld);
    mnfield_free(&fldcpy);
    fld=mnfield_new_double("name",10.5);
    fldcpy=mnfield_clone(fld);
    res=res*mnfield_is_equal(fld,fldcpy);
    mnfield_free(&fld);
    mnfield_free(&fldcpy);
    fld=mnfield_new_cloned_cstring("name","allah");
    fldcpy=mnfield_clone(fld);
    res=res*mnfield_is_equal(fld,fldcpy);
    test(res,"mnfield_clone is working\n ");
    mnfield_free(&fld);
    mnfield_free(&fldcpy);

    return res;
}


char mnfield_TData_test()
{
    print_blue("tetsing TDataField_is_equal...\n");
    TDataField* d=TDataField_new();
    TDataField_init(d,mnfield_new_int("age",43));
    TDataField* d1=TDataField_new();
    TDataField_init(d1,mnfield_new_int("age",43));
    char ret = TData_isEqual(d,d1) ;
    test_v1(ret);

    return ret;

}
