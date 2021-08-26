#ifndef MNSTRING_H
#define MNSTRING_H
#include "cstring.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TString TString ;
struct TString{

  char* string;
  int count;
  int size;
};

TString* TString_new();
void TString_init(TString* str);
void TString_clean(TString* str);
void TString_free(TString** str);
char* TString_get_cstring(TString* str);
void TString_from_cstring(TString* str,char* str_src);

#ifdef __cplusplus
}
#endif

#endif // MNSTRING_H
