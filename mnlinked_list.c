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
        if (!TData_is_presistent(TLinkedListData_get_data(list))) {
            TData_clean(TLinkedListData_get_data(list));
        }
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
