#include "mnstring.h"



TString *TString_new()
{
    TString* str =(TString*) malloc(sizeof (TString));
    assert(str);
    str->string=0;
    str->size=0;
    str->count=0;
    return str;
}

void TString_init(TString *str)
{
    char* s =(char*)malloc(sizeof (char)* (ARRAY_MIN_SIZE+1));
    assert(s);
    str->string=s;
    str->size=ARRAY_MIN_SIZE;
    str->count=0;
}

void TString_clean(TString *str)
{
    free(str->string);
    str->string=0;
    str->size=0;
    str->count=0;
}

void TString_free(TString **str)
{
    assert(!(*str)->string);
    free(*str);
    *str=0;
}

char *TString_get_cstring(TString *str)
{
    return str->string;
}

void TString_from_cstring(TString *str, char *str_src)
{
    TString_clean(str);
    str->string= cstring_new_clone(str_src);
    str->size=cstring_count(str_src);
    str->count=str->size;
}
