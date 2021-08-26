#include "mndictionary.h"

size_t hash(const char *str,size_t size)
{
    size_t hash = 5381;
    size_t c;
    for (size_t i=0;str[i]!=0 ;i++ ) {
        c=str[i];
        hash = ((hash << 5) + hash) + c;
    }
    //    while (c = *str++)
    //        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    if (hash<0) hash=-hash;
    return hash % size;
}

TDictionary *TDictionary_new()
{
    TDictionary* dic= TArray_new();


    return dic;
}

void TDictionary_init(TDictionary* dic,TLint size){
        TArray_init_v1(dic,size);
    TArray_set_all_to_zero(dic);
}

void TDictionary_add(TDictionary *dic,TData* item)
{
    assert(TData_name(item));
    double factor =  TArray_size(dic)/(double)TArray_count(dic);
    if (factor<0.75) {
        TDictionary_expend(&dic);
    }
    TLint index = hash(TData_name(item),TArray_size(dic));
    TLinkedListData* data = (TLinkedListData*)TArray_item_at(dic,index);
    if (data) {

        TLinkedListData_add_or_replace(data,item);
    }else {
        TLinkedListData* data = TLinkedListData_new(item);
        TArray_set_item_at(dic,data,index);
    }
    TArray_set_count(dic,TArray_count(dic)+1);
}

void TDictionary_expend(TDictionary **dic)
{
    TDictionary* new_dic=TDictionary_new();
    TDictionary_init(new_dic,TArray_size(*dic)*2);
    for (TLint i=0;i<TArray_size(*dic) ;i++ ) {
        TLinkedListData* data = (TLinkedListData*)TArrayData_item_at(*dic,i);
        if (data) {
            TLinkedList* d=TLinkedList_new(0);
            for (; data->next_node;data=data->next_node ) {
                TDictionary_add(new_dic,TLinkedListData_get_data(data));
                d->next_node=data->next_node;
                free(data);
                data=d;
            }
            free(d);
            TArray_set_item_at(*dic,0,i);
        }
    }
    TArray_clean(*dic,0);
    TArray_free((TPtrHld)dic);
    *dic=new_dic;
}


