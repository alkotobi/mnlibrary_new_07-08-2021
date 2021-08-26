#ifndef MNDICTIONARY_H
#define MNDICTIONARY_H
#include "mntypes.h"
#include "mnarray.h"
#include "mnlinked_list.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef TArray TDictionary ;

TDictionary *TDictionary_new();
void TDictionary_init(TDictionary* dic, TLint size);
void TDictionary_add(TDictionary* dic, TData *item);
void TDictionary_expend(TDictionary** dic);


#ifdef __cplusplus
}
#endif


#endif // MNDICTIONARY_H
