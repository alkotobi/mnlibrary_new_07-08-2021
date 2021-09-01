#ifndef MNTYPES_H
#define MNTYPES_H
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define ARRAY_MIN_SIZE 250
#define INT_PRINT_SIZE 5
#define DOUBLE_PRINT_SIZE 10
#define STRING_PRINT_SIZE 20
#define NAMELESS 0
typedef long int TLint ;
typedef void** TPtrHld ;
typedef char** TCstrHld ;
#define $P(X) (TPtrHld)(&X)
typedef void** TValues ;
typedef void* TVar;
typedef void* TFunction;
typedef enum {
    FVarVar,
    FCharVarVar,
    FVoidPtrHld,
    FVarVoid,
    FVoidVarVar,
    FLintVar,
    FVarVarLint,
    VoidVar
}TFunTypes ;
typedef enum {
    CString,
    Double,
    Int,
    Field,
    MNString
} TTypes ;
typedef TVar (*TFVarVar)(TVar);
typedef char(*TFCharVarVar)(TVar,TVar) ;
typedef void(*TFVoidPtrHld)(TPtrHld) ;
typedef TVar(*TFVarVoid)(void) ;
typedef void(*TFVoidVarVar)(TVar,TVar) ;
typedef TLint(*TFLintVar)(TVar) ;
typedef TVar(*TFVarVarLint)(TVar,TLint) ;
typedef void(*TFVoidVar)(TVar) ;
typedef TLint(*TFLintVarVar)(TVar,TVar) ;
typedef char* TCstring ;

TVar TValues_new(TLint size);
void TValues_free(TValues *arr);




struct TVariant{
    TTypes data_type;
    TVar val;
    char* name;
    TFVoidPtrHld free_me;
};
typedef struct TVariant TVariant ;

TVariant* TVariant_init(TVariant* var,     TTypes data_type,
              TVar val,
              const char *name,TFVoidPtrHld free_me);
void TVariant_clean(TVariant * var);
TVariant* TVariant_new();
void TVariant_free(TVariant** var_hld);
char* TVariant_name(TVariant* var);
void TVariant_set_name(TVariant* var,const char* name);
TVar TVariant_value(TVariant* var);
TVar TVariant_set_value(TVariant* var ,TVar value);
TTypes TVariant_type(TVariant* var);
void TVariant_set_type(TVariant* var,TTypes data_type);
void TVariant_clean_free(TVariant** var_hld);
TVariant* TVariant_clone(TVariant* var,TFVarVar clone_val);
TVariant* TVariant_init_int(TVariant *var, int n);
int TVariant_int(TVariant* var);
TVariant* TVariant_init_double(TVariant *var, double n);
double TVariant_double(TVariant* var);
TVariant* TVariant_init_cstring(TVariant *var, const char* str);
char* TVariant_cstring(TVariant* var);
char* TVariant_to_new_cstring(TVariant* var);
struct TDataPriv{

    char is_read_only;
    char is_presistent;// cant free
    char is_visible;
};

struct TData{
    //struct TDataPriv priv;
    TVariant* var;
    TFVarVar clone_val;
    TFCharVarVar is_equal;
    TFCharVarVar is_greater;

};

typedef struct TData TData ;
TData* TData_new();
TData *TData_init(TTypes data_type,TData* data, TVar val, TFVoidPtrHld free_val,
                  TFVarVar clone_val,TFCharVarVar is_equal,TFCharVarVar is_greater);
void TData_init_v1(TTypes data_type,TData* data,  TVar val, TFVoidPtrHld free_val);
void TData_init_v2(TTypes data_type,TData* data,  TVar val, TFVoidPtrHld free_val,
                   TFVarVar clone_val);
void TData_clean(TData* data);
void TData_free(TPtrHld data);
void TData_clean_free(TData ** data_hld);
TData *TData_clone(TData*data);
void TData_clone_methods(TData* data_src,TData* data_des);
void TData_clone_properties(TData* data_src,TData* data_des);
TData *TData_new_persistent(TData*data);
TVariant *TData_set_variant(TData* data,TVariant* var);
TVariant* TData_variant(TData* data);
char TData_isEqual(TData* d1,TData*d2);
int TData_int_val(TData* d);
TVar TData_value(TData* d);
TVar TData_set_value(TData* d,  TVar val);
//char TData_is_read_only(TData* d);
//char TData_is_presistent(TData* d);
//void TData_set_readonly(TData*d , char valbool);
//void TData_set_presistent(TData*d , char valbool);
void TData_set_name(TData*d , const char *name);
char* TData_name(TData* d);
TTypes TData_type(TData* d);
//char TData_is_visible(TData*d);
//void TData_set_visible(TData*d,char visible_bool);
void TData_set_type(TData *d, TTypes data_type);
typedef TData TDataInt ;
void TDataInt_init(TDataInt* data,int val);
TDataInt* TDataInt_new_init(int val);
int TDataInt_val(TDataInt* i);
char* TData_to_new_cstring(TData* data);

typedef TData TDataDouble ;
void TDataDouble_init(TDataInt* data,double val);
TDataInt* TDataDouble_new_init(double val);
double TDataDouble_val(TDataDouble* i);




//cstring..........
typedef struct{
  char* cstring;
  TLint size;
} TCstringSize ;

TCstringSize TCstringSize_init(char* str,TLint size);
TLint cstring_count(const char* str);
TLint cstring_size(const char* str);
char* cstring_new(TLint size);
char* cstring_new_fill_with_char(char character, TLint size);
char* cstring_replace_sub_string_at(TCstringSize str_src, char* str_sub, TLint index);
char* cstring_new_clone(const  char* str);
char* cstring_new_copy_with_char_count(const  char* str,int char_count);
char cstring_is_equal(const char *str1,const char* str2);
char* cstring_new_from_concat(int strings_count,...);
char cstring_is_empty(const char* str);
char *cstring_new_from_concat_v1(char ** str_list, size_t strings_count);
char *cstring_new_from_concat_with_nl(char ** str_list,size_t strings_count);
void cstring_free(void** str);
char cstring_is_greater(const char *str1, const char *str2);
void cstring_add(TCstrHld master_str, const char *to_add_str);
void cstring_add_chars(TCstring str,TCstring chars);
TData *TData_init_cstring(TData* data, const char *str);
char* TData_cstring(TData* d);



//TString

typedef   struct {
  char* cstring;
  int count;
  int size;
}TString;

TString *TString_new();
TString *TString_init(TString* str,char* cstring);
void TString_clean(TString* str);
void TString_free(TString** str_hld);
TString* TString_insert_sub_at(TString* str_src,char* str_sub,int index);
int TString_count(TString* str);
void TString_set_count(TString* str,int count);
int TString_size(TString* str);
void TString_set_size(TString* str,int size);
char* Tstring_cstring(TString* str);
void TString_set_cstring(TString* str, char* cstring);

#endif // MNTYPES_H
