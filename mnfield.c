#include "mnfield.h"






mnfield *mnfield_new()
{
    mnfield* self= malloc(sizeof (mnfield));
    assert(self);
    self->private.caption=0;
    self->private.width=0;
    self->private.max_width=0;
    self->private.fixed_width=0;
    self->private.caption=0;
    return self;
}

void mnfield_init(TField* fld,TData* data ,char is_generatated,
                  int width,
                  int max_width,
                  int fixed_width,
                  TCstring caption){
    fld->private.caption=cstring_new_clone(caption);
    fld->private.width=width;
    fld->private.max_width=max_width;
    fld->private.fixed_width=fixed_width;
    fld->private.caption=cstring_new_clone(caption);
    fld->private.data=data;
    TData_set_visible(TField_data(fld),is_generatated);
}

void mnfield_init_v1(TField* fld,TData* data){
    mnfield_init(fld,data,0,0,0,0,0);
}
void mnfield_free(mnfield** fld){

    free(*fld);
    *fld=0;
}



mnfield *mnfield_new_int(const char *name, int data)
{
    TDataInt* i=TDataInt_new_init(data);
    TData_set_name(i,name);
    mnfield* field =mnfield_new();
    mnfield_init_v1(field,i);
    return field;
}


mnfield *mnfield_new_double(const char *name, double data)
{
    TDataInt* i=TDataDouble_new_init(data);
    TData_set_name(i,name);
    mnfield* field =mnfield_new();
    mnfield_init_v1(field,i);
    return field;
}

mnfield *mnfield_new_cloned_cstring(const char *name,const char* str)
{

    TData* d = cstring_new_TData(cstring_new_clone(str));
    TData_set_name(d,name);
    mnfield* field =mnfield_new();
    mnfield_init_v1(field,d);
    return field;
}


void mnfield_prepare_for_gui(mnfield* fld,
                             const char* caption,int width,
                             int min_width,int fixed_width ){
    fld->private.caption=cstring_new_clone(caption);
    fld->private.fixed_width=fixed_width;
    fld->private.max_width=min_width;
    fld->private.width=width;
}

void mnfield_setval_int(mnfield *field, int data)
{
    int* i=(int*)malloc(sizeof (int));
    *i=data;
    TData_set_value(TField_data(field),i);

}

void mnfield_setval_double(mnfield *field, double data)
{
    double* i=(double*)malloc(sizeof (double));
    *i=data;
    TData_set_value(TField_data(field),i);
}

void mnfield_setval_cstring(mnfield *field, const char *str)
{
    TData_set_value(TField_data(field),cstring_new_clone(str));
}




int mnfield_int_val(mnfield *field)
{ 
    return TDataInt_val(TField_data(field));
}

double mnfield_double_val(mnfield *field)
{
    return TDataDouble_val(TField_data(field));
}

TCstring mnfield_cstring_val_ref(mnfield* fld){
    return  cstring_from_TData_ref(TField_data(fld));
}
TCstring mnfield_cstring_val_cpy(mnfield* fld){
    return cstring_from_TData_cpy(TField_data(fld));
}

void TField_clone_prop(TField* fld_src,TField* fld_des){
    fld_des->private.caption=cstring_new_clone(fld_src->private.caption);
    fld_des->private.data=TData_clone(TField_data(fld_src));
    fld_des->private.fixed_width=fld_src->private.fixed_width;
    fld_des->private.max_width=fld_src->private.max_width;
    fld_des->private.width=fld_src->private.width;
    TField_set_is_generated(fld_des,TField_is_generated(fld_src));
}

mnfield *mnfield_clone(mnfield *f)
{
    mnfield* fld=mnfield_new();
    mnfield_init(fld,
                 TData_clone(TField_data(f)),
                 TField_is_generated(f),
                 f->private.width,
                 f->private.max_width,
                 f->private.fixed_width,
                 cstring_new_clone(f->private.caption));
    return fld;
}



char mnfield_is_equal(mnfield *fld1, mnfield *fld2)
{
    return  TData_isEqual(TField_data(fld1),TField_data(fld2));


}

TCstring mnfield_val_to_new_cstring(mnfield* fld){
    if(TField_type(fld)==CString){
        char* str=(char*)TData_value(TField_data(fld));
        return str;
    }else if (TField_type(fld)==Int) {
        return TCstrings_concat_multi("%d",TDataInt_val(TField_data(fld)));
    }else{
        return TCstrings_concat_multi("%d",TDataDouble_val(TField_data(fld)));
    }
    return 0;

}


char TField_is_generated(TField *fld)
{
    return TData_is_visible(TField_data(fld));
}

void TField_set_is_generated(TField *fld, char is_generated_bool)
{
    TData_set_visible(TField_data(fld),is_generated_bool);
}

TData *TField_data(TField *fld)
{
    return fld->private.data;
}

void TField_set_data(TField *fld, TData *data)
{
    if (!TData_is_presistent(TField_data(fld))) {
        TData* d=TField_data(fld);
        TData_clean(d);
        TData_free($P(d));
    }
    fld->private.data=data;
}

void mnfield_clean(TField *fld)
{
    TData* d=TField_data(fld);
    TData_clean(d);
    TData_free($P(d));
    free(fld->private.caption);
}

TTypes TField_type(TField *fld)
{
    return TData_type(TField_data(fld));
}

TCstring TField_name(TField *fld)
{
    return TData_name(TField_data(fld));
}

TDataField *TDataField_new()
{
    return TData_new();
}

void TDataField_init(TDataField *data_fld,TField* fld)
{
    TData_init(Field,data_fld,fld,TDataField_free_clean,
               (TFVarVar)mnfield_clone,
               (TFCharVarVar)mnfield_is_equal,(TFCharVarVar)TField_is_greater);
}

void TDataField_free_clean(TPtrHld d)
{
    mnfield_clean(*d);
    mnfield_free((TField**)d);
}

char TField_is_greater(TField *fld1, TField *fld2)
{
    if (!TField_data(fld1)->is_greater) {
        return 0;
    }
    return TField_data(fld1)->is_greater(TField_data(fld1),TField_data(fld2));
}
