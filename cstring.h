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
//void cstring_add_chars(TCstring str,TCstring chars);
void cstring_add(TCstrHld master_str, const char *to_add_str);
TData *TData_init_cstring(TData* data, const char *str);
char* TData_cstring(TData* d);
typedef TArray TCstrings ;
TCstrings *TCstrings_new();
TCstrings *TCstrings_init(TCstrings* str_list);
void TCstrings_clean(TCstrings *str_list);
void TCstrings_free(TCstrings ** str_list);
void TCstrings_clean_free(TCstrings **str_list);
char *TCstrings_add(TCstrings *str_list, TCstring str);
char *TCstrings_add_clone(TCstrings *str_list, const char *str);
TCstring TCstrings_concat(TCstrings *str_list, TCstring end_line);
TLint TCstrings_char_count(TCstrings* str_list);
TCstring TCstrings_item_at(TCstrings* str_list, TLint index);
char* TCstrings_concat_multi(const char *str,...);
char* TArray_add_cstring(TArray* arr,char* str);
char* TArray_cstring_at(TArray* arr,TLint index);
void TArray_clean_cstring(TArray*arr);

#ifdef __cplusplus
}
#endif
#endif // CSTRING_H
