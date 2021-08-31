#ifndef MNSTRING_H
#define MNSTRING_H

#include "mnarray.h"
#include "cstring.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct mnstring mnstring ;
struct mnstring{

  char* string;
  int count;
  int size;
};

typedef mnstring TString;
TString* TString_new();
TString* TString_init(TString* str, char *c_str);
TString* TString_init_with_cloned_cstr(TString* str,const char *c_str);
TString* TString_init_with_empty_cstr(TString* str);
TData* TDAta_init_mnstring(TData* data,mnstring* str);
mnstring* TData_mnstring(TData* data);
char mnstring_is_greater(mnstring* str1,mnstring*str2);
void TString_clear(TString*str);
void TString_free(TString** str_hld);
void TString_clear_free(TString** str_hld);
mnstring *mnstring_new_v1();
mnstring* mnstring_new(size_t size);
void mnstring_free(mnstring **str);
mnstring* mnstring_clone(mnstring* str);
char mnstring_is_equal(mnstring* str1,mnstring* str2);
mnstring* mnstring_new_from_cstring_cpy(const char* str);
mnstring *mnstring_new_from_cstring_ref(char *string);
mnstring* mnstring_new_from_mnstring(const mnstring *s);
void *mnstring_new_from_mnstring_v0(void *s);
void mnstring_free_v0(void* str);
char mnstring_is_equal(mnstring* str1,mnstring * str2);
mnstring* mnstring_new_from_concat(int strings_count,...);
mnstring* mnstring_new_from_int(int n);
mnstring* mnstring_new_from_double(double d);
mnstring* mnstring_new_concat_multi(const char* str,...);
void mnstring_concat(mnstring* str_to,mnstring* str_sub);
void mnstring_concat_msstr_cstr(mnstring* str_to,const char*str_sub);
mnstring* mnstring_new_empty();
char mnstring_is_empty(mnstring* str);
mnstring* mnstring_new_from_array(TArray* list);

mnstring* TArray_add_mnstring(TArray* arr ,mnstring* str);
mnstring* TArray_mnstring_at(TArray* arr,TLint index);
void TArry_clean_mnstring(TArray* arr);

#define TO_TRASH_MNS(X) TArray_add(_trash,(TVar)(TDAta_init_mnstring(TData_new(),X)))
#ifdef __cplusplus
}
#endif



#endif // MNSTRING_H
