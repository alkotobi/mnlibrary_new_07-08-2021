#ifndef MNLINKED_LIST_H
#define MNLINKED_LIST_H

#include "mntypes.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef  struct TLinkedList TLinkedList;
struct TLinkedList{
    TLinkedList* root_node;
    TLinkedList* next_node;
    TVar val;
};

TLinkedList* TLinkedList_new(TVar val);
void TLinkedList_add(TLinkedList *root , TVar item);

typedef TLinkedList TLinkedListData  ;
TLinkedListData* TLinkedListData_new(TData* val);
void TLinkedListData_add(TLinkedListData *root , TData *item);
void TLinkedListData_add_or_replace(TLinkedListData *root , TData *item);
TLinkedListData* TLinkedListData_find(TLinkedListData *root , TData *item);
TData* TLinkedListData_get_data(TLinkedListData * item);
void TLinkedList_add_or_replace(TLinkedListData *root , TVar *item,
                                TFVoidPtrHld free_me,
                                TFCharVarVar is_equal);
TLinkedList *TLinkedList_find(TLinkedList *root , TVar *item,
                                  TFCharVarVar is_equal);
TVar TLinkedList_get_value(TLinkedListData * item);
void TLinkedList_set_value(TLinkedListData * item, TVar value, TFVoidPtrHld free_me);

#ifdef __cplusplus
}
#endif


#endif // MNLINKED_LIST_H
