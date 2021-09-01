#ifndef MNARRAY_H
#define MNARRAY_H
#include "mntypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TArrayPrv TArrayPrv ;

#define $array_add_item_ref(array_ref,val_ref) ((TArray*)array_ref)->methods.add_item_ref(((TArray*)array_ref),val_ref)
struct TArrayPrv{
    TLint size;
    TLint count;
    TValues array;
    TLint index;
};

void TArrayParams_init(struct TArrayPrv* prv);

struct TArray{
    TArrayPrv params_prv;
};
typedef struct TArray TArray ;





TArray* TArray_new();
TArray* TArray_init(TArray* arr);
TArray *TArray_init_v1(TArray *arr,TLint size);
TVar TArray_add(TArray *arr, TVar item);
TVar TArray_add_cpy(TArray *arr, TVar item, TFVarVar clone_me);
void TArray_free_data(TArray *arr,TFVoidPtrHld free_data);
void TArray_clean(TArray *arr,TFVoidPtrHld free_data);
TLint TArray_count(TArray* arr);
TLint TArray_size(TArray* arr);
TVar TArray_item_at(TArray* arr,TLint index);
TVar TArray_remove_item_ret_ref(TArray* arr,TLint index);
void TArray_free(TPtrHld arr);
TLint TArray_find(TArray*arr, TVar item, TFCharVarVar is_equal);
TVar TArray_add_or_replace(TArray *arr, TVar item, TFCharVarVar is_equal);
TVar TArray_set_item_at(TArray *arr, TVar item, TLint index);
void TArray_set_all_to_zero(TArray*arr);
void TArray_set_count(TArray * arr , TLint count);
TArray* TArray_clone(TArray* arr , TFVarVar clone_value);
char TArray_is_equal(TArray* arr1,TArray* arr2,TFCharVarVar vals_is_equal);
TLint TArray_index(TArray* arr);
void TArray_set_index(TArray*arr,TLint index);
char *TArray_to_cstring(TArray* arr, char*(*value_to_csting)(TVar));


typedef TArray TArrayData;
TArrayData* TArrayData_new();
TArrayData *TArrayData_init(TArrayData* arr);
void TArrayData_clean(TArray *arr);
void TArrayData_free(TArray** arr);
void TArrayData_add_clone(TArray *arr, TData* item);
void TArrayData_add_presistent(TArray *arr, TData* item);
TData *TArrayData_add(TArray *arr, TData* item);
TLint TArrayData_find_first(TArray*arr,TData* item);
TData *TArrayData_add_or_replace(TArray *arr, TData* item);
TData* TArrayData_item_at(TArrayData *arr,TLint index);
char *TArrayData_to_cstring(TArray* arr);

typedef TArrayData TTrash ;
TTrash* TTrash_new();
TTrash* TTRash_init(TTrash *trash);
#define NEW_TRASH() TTrash* _trash=TTRash_init(TTrash_new())
void TTrash_clear_free(TTrash** trash);
#define EMPTY_TRASH() TTrash_clear_free(&_trash)



//TStrings


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

#endif // MNARRAY_H
