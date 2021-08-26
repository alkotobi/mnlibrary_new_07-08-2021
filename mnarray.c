#include "mnarray.h"



TArray *TArray_new()
{
    TArray* a=(TArray*)malloc(sizeof (TArray));
    assert(a);
    return a;
}



void TArray_init_methods(TArray* arr){
    arr->methods.add_item_ref=(TFVoidVarVar)TArray_add;
    arr->methods.add_item_cpy=(TFVoidVarVar)TArray_add_cpy;
    arr->methods.remove_item_ret_ref=(TFVarVarLint)TArray_remove_item_ret_ref;
    arr->methods.clean=(TFVoidVarVar)TArray_free_data;
    arr->methods.get_count=(TFLintVar)TArray_count;
    arr->methods.get_size=(TFLintVar)TArray_size;
    arr->methods.get_item_at=(TFVarVarLint)TArray_item_at;
    arr->methods.free_array=TArray_free;
    arr->methods.find_first_item=(TFLintVarVar)TArray_find;
    arr->methods.add_or_replace_item=(TFVoidVarVar)TArray_add_or_replace;
}
void TArray_init(TArray *arr)
{
    TArray_init_v1(arr,ARRAY_MIN_SIZE);

}
void TArray_init_v1(TArray *arr,TLint size)
{
    arr->params_prv.array=TValues_new(size);
    arr->params_prv.count=0;
    arr->params_prv.size=ARRAY_MIN_SIZE;
    TArray_init_methods(arr);
}

TArray *TArray_new_init()
{
    TArray* arr=TArray_new();
    TArray_init(arr);
    return arr;
}

void TArray_add(TArray* arr,TVar item)
{
    if (arr->params_prv.count==arr->params_prv.size) {
        arr->params_prv.size=arr->params_prv.size*2;
        TValues_realloc(&arr->params_prv.array,arr->params_prv.size);
        assert(arr->params_prv.array);
    }
    arr->params_prv.array[arr->params_prv.count]=item;
    arr->params_prv.count++;
}

void TArray_free_data(TArray* arr, TFVoidPtrHld free_data)
{
    if (free_data) {
        for (TLint i=0;i<TArray_count(arr) ;i++ ) {
            free_data(&arr->params_prv.array[i]);
        }
        TArray_set_count(arr,0);
    }
    TValues_free(&arr->params_prv.array);
}

void TArray_clean(TArray *arr,TFVoidPtrHld free_data){
    TArray_free_data(arr,free_data);
}

TLint TArray_count(TArray *arr)
{
    return arr->params_prv.count;
}

TLint TArray_size(TArray *arr)
{
    return arr->params_prv.size;
}

TVar TArray_item_at(TArray *arr, TLint index)
{
    assert(index<arr->params_prv.count);
    return arr->params_prv.array[index];
}

void TArray_add_cpy(TArray *arr, TVar item)
{
    assert(0&&arr&&(item));
}

void TArray_set_count(TArray * arr , TLint count){
    arr->params_prv.count=count;
}


TVar TArray_remove_item_ret_ref(TArray *arr, TLint index)
{
    assert(index<arr->params_prv.count);
    TVar ret=arr->params_prv.array[index];
    for (TLint i=index;i<arr->params_prv.count-1;i++ ) {
        arr->params_prv.array[i]=arr->params_prv.array[i+1];
    }
    arr->params_prv.array[arr->params_prv.count-1]=0;
    arr->params_prv.count--;
    return ret;
}

void TArray_free(TPtrHld arr)
{
    TArray* a=(TArray*)*arr;
    assert(!a->params_prv.array);
    free(*arr);
    *arr=0;
}

void TArrayData_init(TArrayData* arr)
{
    TArray_init(arr);
    arr->methods.clean=(TFVoidVarVar)TArrayData_clean;
    arr->methods.add_item_cpy=(TFVoidVarVar)TArrayData_add_clone;
    arr->methods.add_item_ref=(TFVoidVarVar)TArrayData_add_presistent;
    arr->methods.find_first_item=(TFLintVarVar)TArrayData_find_first;
    arr->methods.add_or_replace_item=(TFVoidVarVar)TArrayData_add_or_replace;

}

void TArrayData_clean(TArray *arr)
{
    for (TLint i=0;i<TArray_count(arr) ;i++ ) {
        if (!TData_is_presistent(TArrayData_item_at(arr,i))) {
            TData_clean(TArrayData_item_at(arr,i));
        }
        TData_free(&arr->params_prv.array[i]);
    }
    free(arr->params_prv.array);
    arr->params_prv.array=0;
}

void TArrayData_add_clone(TArray *arr, TData *item)
{
    TArrayData_add(arr,TData_clone(item));
}

void TArrayData_add_presistent(TArray *arr, TData *item)
{

    TArrayData_add(arr,TData_new_persistent(item));
}

void TArrayData_add(TArray *arr, TData* item){
    TArray_add(arr,item);
}

TLint TArray_find(TArray *arr, TVar item)
{
    assert(0&&arr&&item);
    return 0;
}

void TArray_add_or_replace(TArray *arr, TVar item)
{
    assert(0&&arr&&item);

}

void TArray_set_item_at(TArray *arr, TVar item,TLint index){
    assert(index<TArray_size(arr));
    arr->params_prv.array[index]=item;
}

void TArray_set_all_to_zero(TArray *arr)
{
    for (TLint i=0;i<TArray_size(arr) ;i++ ) {
        arr->params_prv.array[i]=0;
    }
}

TLint TArrayData_find_first(TArray *arr, TData *item)
{
    for (TLint i=0;i<TArray_count(arr) ;i++ ) {
        if (TData_isEqual(TArray_item_at(arr,i),item)) {
            return i;
        }
    }
    return -1;
}

void TArrayData_add_or_replace(TArray *arr, TData *item)
{
    TLint index=arr->methods.find_first_item(arr,item);
    if (index>=0) {
        TData* data= TArrayData_item_at(arr,index);
        if(!TData_is_presistent(data)){
            TData_clean(data);
            TData_free($P(data));
        }
        arr->params_prv.array[index]=item;
    }else{
    TArrayData_add(arr,item);
    }
}

TData *TArrayData_item_at(TArrayData *arr, TLint index)
{
    return  (TData*)TArray_item_at(arr,index);
}

