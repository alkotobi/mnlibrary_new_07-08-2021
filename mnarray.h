#ifndef MNARRAY_H
#define MNARRAY_H
#include "mntypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TArrayPrv TArrayPrv ;
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
struct TArrayPrv{
    TLint size;
    TLint count;
    TValues array;
};

void TArrayParams_init(struct TArrayPrv* prv);

struct TArray{
    struct TArrayMethods methods;
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
TVar TArray_add_or_replace(TArray *arr, TVar item, TFVoidPtrHld free_me, TFCharVarVar is_equal);
TVar TArray_set_item_at(TArray *arr, TVar item, TLint index, TFVoidPtrHld free_me);
void TArray_set_all_to_zero(TArray*arr);
void TArray_set_count(TArray * arr , TLint count);


typedef TArray TArrayData;
TArrayData* TArrayData_new();
TArrayData *TArrayData_init(TArrayData* arr);
void TArrayData_clean(TArray *arr);
void TArrayData_free(TArray** arr);
void TArrayData_add_clone(TArray *arr, TData* item);
void TArrayData_add_presistent(TArray *arr, TData* item);
TData *TArrayData_add(TArray *arr, TData* item);
TLint TArrayData_find_first(TArray*arr,TData* item);
void TArrayData_add_or_replace(TArray *arr, TData* item);
TData* TArrayData_item_at(TArrayData *arr,TLint index);


typedef TArrayData TTrash ;
TTrash* TTrash_new();
TTrash* TTRash_init(TTrash *trash);
#define NEW_TRASH() TTrash* _trash=TTRash_init(TTrash_new())
void TTrash_clear_free(TTrash** trash);
#define EMPTY_TRASH() TTrash_clear_free(&_trash)

#ifdef __cplusplus
}
#endif

#endif // MNARRAY_H
