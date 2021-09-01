#include "mnarray.h"


void TArrayParams_init(struct TArrayPrv* prv){
    prv->array=0;
    prv->count=0;
    prv->size=0;
    prv->index=0;
}
TArray *TArray_new()
{
    TArray* a=(TArray*)malloc(sizeof (TArray));
    assert(a);
    TArrayParams_init(&a->params_prv);
    return a;
}


TArray* TArray_init(TArray *arr)
{
    return  TArray_init_v1(arr,ARRAY_MIN_SIZE);

}
TArray* TArray_init_v1(TArray *arr,TLint size)
{
    arr->params_prv.array=TValues_new(size);
    arr->params_prv.count=0;
    arr->params_prv.size=size;
    return arr;
}



TVar TArray_add(TArray* arr,TVar item)
{
    //TODO: test TArray_add
    if (arr->params_prv.count==arr->params_prv.size) {

        TValues vals=calloc(arr->params_prv.size*2,sizeof (TVar));
        for (TLint i=0;i<arr->params_prv.size ;i++ ) {
            vals[i]=TArray_item_at(arr,i);
        }
        free(arr->params_prv.array);
        arr->params_prv.array=vals;
        arr->params_prv.size=arr->params_prv.size*2;
        assert(arr->params_prv.array);
    }
    arr->params_prv.array[arr->params_prv.count]=item;
    arr->params_prv.count++;
    return item;
}

void TArray_free_data(TArray* arr, TFVoidPtrHld free_data)
{
    if (free_data) {
        for (TLint i=0;i<TArray_count(arr) ;i++ ) {
            free_data(&arr->params_prv.array[i]);
        }
        TArray_set_count(arr,0);
    }

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

TVar TArray_add_cpy(TArray *arr, TVar item,TFVarVar clone_me)
{
    return TArray_add(arr,clone_me(item));
}

void TArray_set_count(TArray * arr , TLint count){
    arr->params_prv.count=count;
}

TArray* TArray_clone(TArray* arr , TFVarVar clone_value){
    TArray* a=TArray_init(TArray_new());
    for (TLint i=0;i<TArray_count(arr) ;i++ ) {
        TArray_add(a,clone_value(TArray_item_at(arr,i)));
    }
    return a;
}

char TArray_is_equal(TArray* arr1,TArray* arr2,TFCharVarVar vals_is_equal){
    if (TArray_count(arr2)!=TArray_count(arr1)) return 0;
    TLint i=0;
    for (;i<TArray_count(arr1) ;i++ ) {
        if(!vals_is_equal(TArray_item_at(arr1,i),TArray_item_at(arr2,i))){
            return 0;
        }
    }

    return 1;
}

TLint TArray_index(TArray* arr){
    return arr->params_prv.index;
}

void TArray_set_index(TArray*arr,TLint index){
    arr->params_prv.index=index;
}

char *TArray_to_cstring(TArray* arr,char*(*value_to_csting)(TVar)){
//TODO:TArray_to_cstring test

    TCstrings* a=TCstrings_init(TCstrings_new());
    for (TLint i=0;i<TArray_count(arr) ;i++ ) {
        TArray_add(a,value_to_csting(TArray_item_at(arr,i)));
    }
    return  TCstrings_concat(a,"\n");

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
    TValues_free(&a->params_prv.array);
    free(*arr);
    *arr=0;
}


TArrayData* TArrayData_new(){
    return TArray_new();
}
TArrayData* TArrayData_init(TArrayData* arr)
{
    TArray_init(arr);
    return arr;
}

void TArrayData_clean(TArray *arr)
{
    for (TLint i=0;i<TArray_count(arr) ;i++ ) {
            TData* d=TArrayData_item_at(arr,i);
            TData_clean_free(&d);
    }

}

void TArrayData_add_clone(TArray *arr, TData *item)
{
    TArrayData_add(arr,TData_clone(item));
}

void TArrayData_add_presistent(TArray *arr, TData *item)
{

    TArrayData_add(arr,TData_new_persistent(item));
}

TData* TArrayData_add(TArray *arr, TData* item){
    return (TData*)TArray_add(arr,item);
}

TLint TArray_find(TArray *arr, TVar item,TFCharVarVar is_equal)
{
    for(TLint i=0;i<TArray_count(arr);i++){
        if (is_equal(TArrayData_item_at(arr,i),item)) {
            return i;
        }
    }
    return -1;
}

TVar TArray_add_or_replace(TArray *arr, TVar item,TFCharVarVar is_equal)
{
    //will return the remplaced item if exists
    TLint index= TArray_find(arr,item,is_equal);
    if (index>-1) {
        return TArray_set_item_at(arr,item,index);
    }else {
     TArrayData_add(arr,item);
     return 0;
}

}

TVar TArray_set_item_at(TArray *arr, TVar item,TLint index){
    //will return the replaced Item
    assert(index<TArray_size(arr));
    TVar v=arr->params_prv.array[index];
    arr->params_prv.array[index]=item;
    return v;
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

TData* TArrayData_add_or_replace(TArray *arr, TData *item)
{
    TLint index=TArrayData_find_first(arr,item);
    TData* data=0;
    if (index>=0) {
        data= TArrayData_item_at(arr,index);
        arr->params_prv.array[index]=item;
    }else{
    TArrayData_add(arr,item);
    }
    return data;
}

TData *TArrayData_item_at(TArrayData *arr, TLint index)
{
    return  (TData*)TArray_item_at(arr,index);
}

char *TArrayData_to_cstring(TArray* arr){
    return TArray_to_cstring(arr,(char*(*)(TVar))TData_to_new_cstring);
}

void TArrayData_free(TArray **arr)
{
    TArray_free((TPtrHld)arr);
}

TTrash *TTrash_new()
{
    return TArrayData_new();
}

TTrash *TTRash_init(TTrash* trash)
{
    return TArrayData_init(trash);
}

void TTrash_clear_free(TTrash **trash)
{
    TArrayData_clean(*trash);
    TArrayData_free(trash);
}





void cstring_add(TCstrHld master_str,const char* to_add_str){
    //TODO: test cstring_add
    TCstrings* strs =TCstrings_init(TCstrings_new());
    TCstrings_add(strs,*master_str);
    TCstrings_add_clone(strs,to_add_str);
    char* ret=TCstrings_concat(strs,"");
    TCstrings_clean_free(&strs);
    *master_str =ret;

}




TCstrings *TCstrings_new()
{
    return TArray_new();
}

TCstrings* TCstrings_init(TCstrings *str_list)
{
    return TArray_init(str_list);
}

void TCstrings_clean(TCstrings *str_list){
    TArray_clean(str_list,cstring_free);
}

void TCstrings_free(TCstrings **str_list)
{
    free(*str_list);
    *str_list=0;
}

void TCstrings_clean_free(TCstrings **str_list){
    TCstrings_clean(*str_list);
    TCstrings_free(str_list);
}

char* TCstrings_add(TCstrings *str_list, TCstring str)
{
    TArray_add(str_list,str);
    return str;
}

char* TCstrings_add_clone(TCstrings *str_list,const char* str)
{
    char* _str =cstring_new_clone(str);
    TArray_add(str_list,cstring_new_clone(str));
    return _str;
}

TCstring TCstrings_concat(TCstrings *str_list, TCstring end_line)
{
    //TODO:test TCstrings_concat
    TLint end_count=cstring_count(end_line);
    TLint end_lines_count=end_count*TArray_count(str_list);
    TLint char_count=TCstrings_char_count(str_list);
    TCstring str =(TCstring) malloc(sizeof (char)*(end_lines_count+char_count+1));
    assert(str);
    TCstringSize str_and_size=TCstringSize_init(str,end_lines_count+char_count);
    TLint j=0;
    TLint k=0;
    for (TLint i=0;i<char_count ;i++ ) {
        if (TArray_cstring_at(str_list,k)[j]==0) {
            j=0;
            k++;
            cstring_replace_sub_string_at(str_and_size,end_line,i+1);
            i=i+end_count;
            continue;
        }
        str[i]=TArray_cstring_at(str_list,k)[j];
        j++;

    }
    return str;

}

TLint TCstrings_char_count(TCstrings *str_list)
{
    TLint char_count=0;
    for (TLint i=0;i<TArray_count(str_list) ;i++ ) {
        char_count=char_count+ cstring_count(TCstrings_item_at(str_list,i));
    }
    return char_count;
}

TCstring TCstrings_item_at(TCstrings *str_list, TLint index)
{
    return (TCstring)TArrayData_item_at(str_list,index);
}


char* TCstrings_concat_multi(const char *str,...){
    //TODO: recheck TCstrings_concat_multi
    va_list ap;
    int i=0;
    int j=0;
    va_start(ap, str);
    char* str1 =cstring_new(250);
    TCstrings* list =TCstrings_new();
    TCstrings_init(list);
    while(str[i]!='\0'){
        if(str[i]=='%'){
            str1[j]=0;
            TCstrings_add(list,cstring_new_clone(str1));
            i++;
            if(str[i]=='s'){
                char*s =cstring_new_clone(va_arg(ap, char*));
                TCstrings_add(list,s);
            }
            else if(str[i]=='d'){
                char* s = cstring_new(200);
                sprintf(s,"%d",va_arg(ap, int));
                TCstrings_add(list,s);
            }
            else if(str[i]=='f'){//for mnstring
                char* s = cstring_new(200);
                sprintf(s,"%f",va_arg(ap, double));
                TCstrings_add(list,s);
            }
            j=0;
            i++;
            continue;
        }
        str1[j]=str[i];
        j++;
        i++;
    }
    va_end(ap);
    str1[j]=0;
    TCstrings_add(list,str1);
    char*s=TCstrings_concat(list,"");
    TCstrings_clean(list);
    TCstrings_free(&list);
    return  s;
}

char *TArray_add_cstring(TArray *arr, char *str)
{
    TArray_add(arr,(TVar)str);
    return str;
}

char *TArray_cstring_at(TArray *arr, TLint index)
{
    return (char*)TArray_item_at(arr,index);
}

void TArray_clean_cstring(TArray *arr)
{
    TArray_clean(arr,cstring_free);
}

