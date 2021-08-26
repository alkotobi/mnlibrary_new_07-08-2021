#ifndef CSTRING_H
#define CSTRING_H
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "mnarray.h"

#ifdef __cplusplus
extern "C"
{
#endif
TLint cstring_count(const char* str);
TLint cstring_size(const char* str);
char* cstring_new(TLint size);
char* cstring_new_clone(const  char* str);
char* cstring_new_copy_with_char_count(const  char* str,int char_count);
char cstring_is_equal(const char *str1,const char* str2);
char* cstring_new_from_concat(int strings_count,...);
char cstring_is_empty(const char* str);
char *cstring_new_from_concat_v1(char ** str_list, size_t strings_count);
char *cstring_new_from_concat_with_nl(char ** str_list,size_t strings_count);
void cstring_free(void** str);
char cstring_is_greater(const char *str1, const char *str2);
void cstring_add_chars(TCstring str,TCstring chars);
void cstring_init_Tdata(TData* data, const char *str);
TData* cstring_new_TData(const char *str);
TData cstring_to_TData(TCstring str);
TCstring cstring_from_TData_ref(TData* data);
TCstring cstring_from_TData_cpy(TData* data);
typedef TArray TCstrings ;
TCstrings *TCstrings_new();
void TCstrings_init(TCstrings* str_list);
void TCstrings_clean(TCstrings *str_list);
void TCstrings_free(TCstrings ** str_list);
void TCstrings_add(TCstrings *str_list, TCstring str);
TCstring TCstrings_concat(TCstrings *str_list, TCstring end_line);
TLint TCstrings_char_count(TCstrings* str_list);
TCstring TCstrings_item_at(TCstrings* str_list, TLint index);
char* TCstrings_concat_multi(const char *str,...);

#ifdef __cplusplus
}
#endif
#endif // CSTRING_H
