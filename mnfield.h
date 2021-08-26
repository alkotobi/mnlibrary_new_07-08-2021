#ifndef MNFIELD_H
#define MNFIELD_H
#include "cstring.h"
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

struct mnfield_prv{
    int width;
    int max_width;
    int fixed_width;
    TData* data;
    TCstring caption;
};
typedef struct mnfield mnfield ;
struct mnfield{

  struct mnfield_prv private;
};

typedef struct mnfield TField ;
char TField_is_generated(TField* fld);
void TField_set_is_generated(TField* fld ,char is_generated_bool);
TData* TField_data(TField* fld);
void TField_set_data(TField* fld,TData* data);
mnfield *mnfield_new();
void mnfield_init(TField* fld, TData *data, char is_generatated, int width, int max_width, int fixed_width, TCstring caption);
void mnfield_init_v1(TField* fld,TData* data);
void mnfield_free(mnfield **fld);
void mnfield_clean(TField* fld);
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


int mnfield_int_val(mnfield* field);
double mnfield_double_val(mnfield* field);
TCstring mnfield_cstring_val_ref(mnfield* fld);
TCstring mnfield_cstring_val_cpy(mnfield* fld);
char mnfield_is_equal(mnfield* fld1,mnfield* fld2);

TCstring mnfield_val_to_new_cstring(mnfield* fld);
TTypes TField_type(TField* fld);
TCstring TField_name(TField* fld);
typedef TData TDataField ;
TDataField* TDataField_new();
void TDataField_init(TDataField* data_fld, TField *fld);
void TDataField_free_clean(TPtrHld d);
char TField_is_greater(TField* fld1,TField* fld2);

#ifdef __cplusplus
}
#endif

#endif // MNFIELD_H
