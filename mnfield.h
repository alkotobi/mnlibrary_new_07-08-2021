#ifndef MNFIELD_H
#define MNFIELD_H

#include "mnarray.h"
\
#include <stdio.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define MNFIELD_SWIDTHL 250
#define MNFIELD_SWIDTHM 100
#define MNFIELD_SWIDTHS 50
#define MNFIELD_NWIDTH 10

struct TFieldPrv{
    int width;
    int max_width;
    int fixed_width;
    char is_generated;
    TData* data;
    TCstring caption;
};
void TFieldPrv_init(struct TFieldPrv* prv);
typedef struct mnfield mnfield ;
struct mnfield{

  struct TFieldPrv private;
};

typedef struct mnfield TField ;
char TField_is_generated(TField* fld);
void TField_set_is_generated(TField* fld ,char is_generated_bool);
TData* TField_data(TField* fld);
TData *TField_set_data(TField* fld,TData* data);
mnfield *mnfield_new();
TField *mnfield_init(TField* fld, TData *data, char is_generatated,
                  int width, int max_width, int fixed_width,
                  TCstring caption, const char *name);
TField *mnfield_init_v1(TField* fld, TData* data, const char *name);
void mnfield_free(mnfield **fld);
void mnfield_clean(TField* fld);
void mnfield_clean_free(mnfield **fld);
void mnfield_dest(TField* fld);
mnfield* mnfield_clone(mnfield* i);
char mnfield_is_equal(mnfield* in1,mnfield* in2);
mnfield* mnfield_new_int(const char* name, int data);
void mnfield_prepare_for_gui(mnfield* fld,
                                 const char* caption,int width,
                                 int min_width,int fixed_width );
mnfield* mnfield_new();
mnfield* mnfield_new_double(const char* name,double data);
mnfield* mnfield_new_cloned_cstring(const char*name, const char *str);

void mnfield_setval_int(mnfield*field,int data);
void mnfield_setval_double(mnfield*field,double data);
void mnfield_setval_cstring(mnfield*field, const char*str);
void mnfield_set_generated(mnfield*field,char is_generated);
int mnfield_int_val(mnfield* field);
double mnfield_double_val(mnfield* field);
TCstring mnfield_cstring_val_ref(mnfield* fld);
TCstring mnfield_cstring_val_cpy(mnfield* fld);
char mnfield_is_equal(mnfield* fld1,mnfield* fld2);

TCstring mnfield_val_to_new_cstring(mnfield* fld);
TTypes TField_type(TField* fld);
TCstring TField_name(TField* fld);

TData *TData_init_field(TData* data_fld, TField *fld);

TField* TData_field(TData* data_fdl);
char TField_is_greater(TField* fld1,TField* fld2);
char* TField_to_csting(TField* fld);

typedef  TArrayData TFields;
TFields* TFields_new();
TFields *TFields_init(TFields* flds);
void TFields_clean(TFields* flds);
TField *TFields_add(TFields* flds,TField* fld);
TField* TFields_item_by_name(TFields* flds,const char* name);
TField* TFields_item_at(TFields* flds,TLint index);
TField* TTrash_add_field(TTrash* trash,TField*fld);
#define TO_TRASH_FLD(X) TTrash_add_field(_trash,X)

TField* TArray_add_field(TArray*arr , TField* fld);
TField* TArray_TField_at(TArray* flds,TLint index);
void TArray_clean_field(TArray* arr);
#ifdef __cplusplus
}
#endif

#endif // MNFIELD_H
