#ifndef MNARRAY_H
#define MNARRAY_H
#include "mntypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TArrayParams TArrayParams ;
struct TArrayMethods {
    TFVoidVarVar add_item_ref;
    TFVoidVarVar add_item_cpy;
    TFVarVarLint remove_item_ret_ref;
    TFVoidVarVar clean;
    TFVoidPtrHld free_array;
    TFLintVar get_count;
    TFLintVar get_size;
    TFVarVarLint get_item_at;
    TFLintVarVar find_first_item;
    TFVoidVarVar add_or_replace_item;
};
#define $array_add_item_ref(array_ref,val_ref) ((TArray*)array_ref)->methods.add_item_ref(((TArray*)array_ref),val_ref)
struct TArrayParams{
    TLint size;
    TLint count;
    TValues array;
};
struct TArray{
    struct TArrayMethods methods;
    TArrayParams params_prv;
};
typedef struct TArray TArray ;





TArray* TArray_new();
void TArray_init(TArray* arr);
void TArray_init_v1(TArray *arr,TLint size);
TArray* TArray_new_init();
void TArray_add(TArray *arr, TVar item);
void TArray_add_cpy(TArray *arr, TVar item);
void TArray_free_data(TArray *arr,TFVoidPtrHld free_data);
void TArray_clean(TArray *arr,TFVoidPtrHld free_data);
TLint TArray_count(TArray* arr);
TLint TArray_size(TArray* arr);
TVar TArray_item_at(TArray* arr,TLint index);
TVar TArray_remove_item_ret_ref(TArray* arr,TLint index);
void TArray_free(TPtrHld arr);
TLint TArray_find(TArray*arr,TVar item);
void TArray_add_or_replace(TArray *arr, TVar item);
void TArray_set_item_at(TArray *arr, TVar item,TLint index);
void TArray_set_all_to_zero(TArray*arr);
void TArray_set_count(TArray * arr , TLint count);


typedef TArray TArrayData;
void TArrayData_init(TArrayData* arr);
void TArrayData_clean(TArray *arr);
void TArrayData_add_clone(TArray *arr, TData* item);
void TArrayData_add_presistent(TArray *arr, TData* item);
void TArrayData_add(TArray *arr, TData* item);
TLint TArrayData_find_first(TArray*arr,TData* item);
void TArrayData_add_or_replace(TArray *arr, TData* item);
TData* TArrayData_item_at(TArrayData *arr,TLint index);
#ifdef __cplusplus
}
#endif

#endif // MNARRAY_H