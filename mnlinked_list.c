#include "mnlinked_list.h"


TLinkedList *TLinkedList_new(TVar val)
{
    TLinkedList* list = (TLinkedList*) malloc(sizeof (TLinkedList));
    assert(list);
    list->next_node=0;
    list->root_node=0;
    list->val=val;
    return list;
}





void TLinkedList_add(TLinkedList* root, TVar item)
{
    while (root->next_node) {
        root=root->next_node;
    }
    root->next_node=TLinkedList_new(item);
}

TLinkedList *TLinkedListData_new(TData *val)
{
    return  TLinkedList_new(val);
}

void TLinkedListData_add(TLinkedListData *root, TData* item)
{
    TLinkedList_add(root,item);
}

void TLinkedListData_add_or_replace(TLinkedListData *root, TData *item)
{
    TLinkedListData* list =TLinkedListData_find(root, item);
    if (list) {
        //if (!TData_is_presistent(TLinkedListData_get_data(list))) {
            TData_clean(TLinkedListData_get_data(list));
       // }
        TData_set_value(TLinkedListData_get_data(list),item);
    }else{
        TLinkedListData_add(root,item);
    }
}

TLinkedListData *TLinkedListData_find(TLinkedListData *root, TData *item)
{


    for (;root->next_node ;root=root->next_node ) {
        if (TData_isEqual(TLinkedListData_get_data(root),item)) {
            return root;
        }
    }
    return 0;
}

TData *TLinkedListData_get_data(TLinkedListData *item)
{
    return  item->val;
}

void TLinkedList_add_or_replace(TLinkedListData *root, TVar *item, TFVoidPtrHld free_me, TFCharVarVar is_equal)
{
    TLinkedListData* list =TLinkedList_find(root, item,is_equal);
    if (list) {
        TLinkedList_set_value(list,item,free_me);
    }else{
        TLinkedList_add(root,item);
    }
}

TLinkedList *TLinkedList_find(TLinkedList *root, TVar *item, TFCharVarVar is_equal)
{
    for (;root->next_node ;root=root->next_node ) {
        if (is_equal(TLinkedList_get_value(root),item)) {
            return root;
        }
    }
    return 0;
}

TVar TLinkedList_get_value(TLinkedListData *item)
{
    return item->val;
}

void TLinkedList_set_value(TLinkedListData *item, TVar value,TFVoidPtrHld free_me)
{
    if (free_me) {
        free_me(value);
    }
    item->val=value;
}
