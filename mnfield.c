#include "mnfield.h"




void TFieldPrv_init(struct TFieldPrv* prv){
    prv->caption=0;
    prv->data=0;
    prv->fixed_width=0;
    prv->max_width=0;
    prv->width=0;
}

mnfield *mnfield_new()
{
    mnfield* self= malloc(sizeof (mnfield));
    assert(self);
    TFieldPrv_init(&self->private);
    return self;
}

TField *mnfield_init(TField* fld, TData *data,char is_generatated,
                  int width, int max_width, int fixed_width,
                  TCstring caption, const char *name){
   // fld->private.caption=cstring_new_clone(caption);
    fld->private.width=width;
    fld->private.max_width=max_width;
    fld->private.fixed_width=fixed_width;
    fld->private.caption=cstring_new_clone(caption);
    fld->private.data=data;
    fld->private.is_generated=is_generatated;
    TData_set_name(fld->private.data,name);
    //TData_set_visible(TField_data(fld),is_generatated);
    return fld;
}

TField* mnfield_init_v1(TField* fld,TData* data,const char* name){
    return  mnfield_init(fld,data,1,0,0,0,0,name);
}

void mnfield_clean(TField *fld)
{
    TData* d=TField_data(fld);
    TData_clean(d);
    TData_free($P(d));

}
void mnfield_clean_free(mnfield **fld){
    mnfield_clean(*fld);
    mnfield_free(fld);
}
void mnfield_free(mnfield** fld){
    free((*fld)->private.caption);
    free(*fld);
    *fld=0;
}

void mnfield_dest(TField* fld){
    mnfield_clean(fld);
    mnfield_free(&fld);
}

mnfield *mnfield_new_int(const char *name, int data)
{
    TDataInt* i=TDataInt_new_init(data);

    mnfield* field =mnfield_new();
    mnfield_init_v1(field,i,name);
    return field;
}


mnfield *mnfield_new_double(const char *name, double data)
{
    TDataInt* i=TDataDouble_new_init(data);
    mnfield* field =mnfield_new();
    mnfield_init_v1(field,i,name);
    return field;
}

mnfield *mnfield_new_cloned_cstring(const char *name,const char* str)
{

    TData* d = TData_init_cstring(TData_new(),cstring_new_clone(str));
    mnfield* field =mnfield_new();
    mnfield_init_v1(field,d,name);
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


void mnfield_set_generated(mnfield*field,char is_generated){
    field->private.is_generated=is_generated;
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
    return  TData_cstring(TField_data(fld));
}
TCstring mnfield_cstring_val_cpy(mnfield* fld){
    return cstring_new_clone(TData_cstring(TField_data(fld)));
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
                 cstring_new_clone(f->private.caption),TField_name(f));
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
    return fld->private.is_generated;
}

void TField_set_is_generated(TField *fld, char is_generated_bool)
{
    fld->private.is_generated=is_generated_bool;
}

TData *TField_data(TField *fld)
{
    return fld->private.data;
}

void TField_set_data(TField *fld, TData *data)
{
//    if (!TData_is_presistent(TField_data(fld))) {
        TData* d=TField_data(fld);
        TData_clean_free(&d);
//    }
    fld->private.data=data;
}



TTypes TField_type(TField *fld)
{
    return TData_type(TField_data(fld));
}

TCstring TField_name(TField *fld)
{
    return TData_name(TField_data(fld));
}



TData* TData_init_field(TData *data_fld,TField* fld)
{
    TData_init(Field,data_fld,fld,(TFVoidPtrHld)mnfield_clean_free,
               (TFVarVar)mnfield_clone,
               (TFCharVarVar)mnfield_is_equal,(TFCharVarVar)TField_is_greater);
    return data_fld;
}

TField* TData_field(TData *data_fdl){
    return (TField*)TData_value(data_fdl);
}


char TField_is_greater(TField *fld1, TField *fld2)
{
    if (!TField_data(fld1)->is_greater) {
        return 0;
    }
    return TField_data(fld1)->is_greater(TField_data(fld1),TField_data(fld2));
}

TFields *TFields_new()
{
    return TArray_new();
}

TFields * TFields_init(TFields *flds)
{
    return TArray_init(flds);
}

TField *TFields_item_by_name(TFields *flds, const char *name)
{
    for (TLint i=0;i<TArray_count(flds) ;i++ ) {
        if (cstring_is_equal(TField_name(TFields_item_at(flds,i)),name)) {
            return TFields_item_at(flds,i);
            break;
        }
    }
    return 0;
}

TField* TFields_add(TFields *flds, TField *fld)
{
    return (TField*) TArray_add(flds,fld);
}

TField *TFields_item_at(TFields *flds, TLint index)
{
    return (TField*) TArray_item_at(flds,index);

}

void TFields_clean(TFields *flds)
{
    TArray_clean(flds,(TFVoidPtrHld)mnfield_clean_free);
}

TField *TTrash_add_field(TTrash *trash, TField *fld)
{
    TArrayData_add(trash,TData_init_field(TData_new(),fld));
    return fld;
}

TField *TArray_add_field(TArray *arr, TField *fld)
{
    TArray_add(arr,(TVar)fld);
    return fld;
}

TField *TArray_TField_at(TArray *flds, TLint index)
{
    return (TField*)TArray_item_at(flds,index);
}

void TArray_clean_field(TArray *arr)
{
    TArray_clean(arr,(TFVoidPtrHld)mnfield_clean_free);
}
