#include "mntypes.h"

TVar TValues_new(TLint size){
    TValues arr =(TValues)malloc(sizeof(TVar)*size);
    assert(arr);
    return arr;
}
void TValues_realloc(TValues* arr,TLint new_size){
    *arr =(TValues)realloc(*arr,sizeof(TVar)*new_size);
    assert(*arr);
}

void TValues_free(TValues *arr)
{
    free(*arr);
    *arr=0;
}

TData *TData_new()
{
    TData* d=(TData*)malloc(sizeof (TData));
    assert(d);
 //   d->free_val=0;
    d->clone_val=0;
    d->is_equal=0;
    d->is_greater=0;
    d->var=0;
   // d->priv.data_type=0;
    //d->priv.is_presistent=0;
    //d->priv.is_read_only=0;
//    d->priv.name=0;
//    d->priv.val=0;
    //d->priv.is_visible=1;
    return d;
}

TData* TData_init(TTypes data_type, TData *data, TVar val,
                TFVoidPtrHld free_val, TFVarVar clone_val,
                TFCharVarVar is_equal, TFCharVarVar is_greater)
{
    //data->free_val=free_val;
    data->clone_val=clone_val;
    data->is_equal=is_equal;
    data->is_greater=is_greater;
    data->var=TVariant_init(TVariant_new(),data_type,val,0,free_val);
    //data->priv.data_type=data_type;
    //data->priv.is_presistent=0;
    //data->priv.is_read_only=0;
    //data->priv.name=0;
    //data->priv.val=val;
    return data;

}

void TData_clean(TData *data)
{
    //assert(!data->priv.is_presistent);

        TVariant_clean(data->var);
        TVariant_free(&data->var);
        //data->free_val(&data->priv.val);


}

void TData_free(TPtrHld data)
{
    //free(((TData *)(*data))->priv.name);
    free(*data);
    *data=0;
}


TData* TData_clone(TData *data)
{
    assert(data->clone_val);
    TData* d = TData_new();
    TVar val=data->clone_val(TData_value(data));
    TData_set_value(d,val);
    TData_clone_properties(data,d);
    TData_clone_methods(data,d);
    return d;

}

TData *TData_new_persistent(TData *data)
{
    TData* d = TData_new();
    d->var=data->var;
    TData_clone_methods(data,d);
    TData_clone_properties(data,d);
    //TData_set_presistent(d,1);
    return d;
}

TVariant* TData_variant(TData* data){
    return data->var;
}

void TData_set_variant(TData* data,TVariant* var){
    if (TData_variant(data)) {
        TVariant_clean(data->var);
        TVariant_free(&data->var);
    }
    data->var=var;
}
void TData_clone_methods(TData *data_src, TData *data_des)
{
    data_des->clone_val=data_src->clone_val;
    data_des->var->free_me=data_src->var->free_me;
    data_des->is_equal=data_src->is_equal;
    data_des->is_greater=data_src->is_greater;
}

void TData_clone_properties(TData* data_src,TData* data_des){
    //TData_set_readonly(data_des,TData_is_read_only(data_src));
    //TData_set_presistent(data_des,TData_is_presistent(data_src));
    TData_set_name(data_des,TData_name(data_src));
    //TData_set_visible(data_des,TData_is_visible(data_src));
    TData_set_type(data_des,TData_type(data_src));
}

char TData_isEqual(TData *d1, TData *d2)
{
    if (TData_type(d1)!=TData_type(d2)) {
        return 0;
    }
    assert(d1->is_equal);
    return d1->is_equal(TData_value(d1),TData_value(d2));
}

void TData_init_v1(TTypes data_type, TData *data, TVar val,
                   TFVoidPtrHld free_val)
{
    TData_init(data_type,data,val,free_val,0,0,0);
}

void TData_init_v2(TTypes data_type, TData *data, TVar val,
                   TFVoidPtrHld free_val, TFVarVar clone_val)
{
    TData_init(data_type,data,val,free_val,clone_val,0,0);
}

int TData_int_val(TData *d)
{
    return *(int*)(TData_value(d));
}

TVar TData_value(TData *d)
{

    return (TVariant_value(d->var));
}

void TData_set_value(TData *d, TVar val)
{
    //assert(!TData_is_read_only(d));
    TVariant_set_value(d->var,val);
}

//char TData_is_read_only(TData *d)
//{
//    return d->priv.is_read_only;
//}

//char TData_is_presistent(TData *d)
//{
//    return d->priv.is_presistent;
//}

//void TData_set_readonly(TData *d, char valbool)
//{
//    d->priv.is_read_only=valbool;
//}

//void TData_set_presistent(TData *d, char valbool)
//{
//    d->priv.is_presistent=valbool;
//}
TLint TData_name_size(const char *name)
{
    TLint j;j=0;
    for(;;){
        if(name[j]=='\0'){
            break;
        }
        j++;
    }
    return j+1;
}
char *TData_clone_name(const  char *name)
{
    if (!name) {
        return 0;
    }
    int size=TData_name_size(name);
    char* str2=malloc(sizeof (char)*(size));
    assert(str2);
    for(int i=0;name[i]!=0;i++){
        str2[i]=name[i];

    }
    str2[size-1]=0;
    return str2;
}

void TData_set_name(TData *d, const char *name)
{
    TVariant_set_name(TData_variant(d),name);

}

char *TData_name(TData *d)
{
    return TVariant_name(TData_variant(d));
}

void int_free(TPtrHld i){
    free(*i);
    *i=0;
}

TVar int_clone(TVar val){
    int* i=(int*)malloc(sizeof (int));
    assert(i);
    *i=*(int*)val;
    return i;
}
char int_isequal(TVar val1,TVar val2){
    return *(int*)val1 ==*(int*)val2;
}

char int_isgreater(TVar val1,TVar val2){
    return *(int*)val1 >*(int*)val2;
}

void TDataInt_init(TDataInt *data, int val)
{
    int* i=(int*)malloc(sizeof (int));
    assert(i);
    *i=val;
    TData_init(Int,data,i,int_free,int_clone,int_isequal,int_isgreater);
}

TDataInt *TDataInt_new_init(int val)
{
    TDataInt* i =TData_new();
    TDataInt_init(i,val);
    return i;
}

int TDataInt_val(TDataInt *i)
{
    return *(int*)TData_value(i);
}





void double_free(TPtrHld i){
    free(*i);
    *i=0;
}

TVar double_clone(TVar val){
    double* i=(double*)malloc(sizeof (double));
    assert(i);
    *i=*(double*)val;
    return i;
}
char double_isequal(TVar val1,TVar val2){
    return *(double*)val1 ==*(double*)val2;
}

char double_isgreater(TVar val1,TVar val2){
    return *(double*)val1 >*(double*)val2;
}

void TDataDouble_init(TDataDouble *data, double val)
{
    double* i=(double*)malloc(sizeof (double));
    assert(i);
    *i=val;
    TData_init(Double,data,i,double_free,double_clone,double_isequal,double_isgreater);
}

TDataDouble *TDataDouble_new_init(double val)
{
    TDataDouble* i =TData_new();
    TDataDouble_init(i,val);
    return i;
}

double TDataDouble_val(TDataDouble *i)
{
    return *(double*)TData_value(i);
}

TTypes TData_type(TData *d)
{
    return TVariant_type(TData_variant(d));
}

//char TData_is_visible(TData *d)
//{
//    return d->priv.is_visible;
//}

//void TData_set_visible(TData *d, char visible_bool)
//{
//    d->priv.is_visible=visible_bool;
//}

void TData_set_type(TData *d, TTypes data_type)
{
    TVariant_set_type(TData_variant(d),data_type);
}

void TData_clean_free(TData **data_hld)
{
    TData_clean(*data_hld);
    TData_free((TPtrHld)data_hld);
}

TVariant *TVariant_init(TVariant *var, TTypes data_type, TVar val,
                        const char *name, TFVoidPtrHld free_me)
{
    var->data_type=data_type;
    var->name=TData_clone_name(name);
    var->val=val;
    var->free_me=free_me;
    return var;
}

void TVariant_clean(TVariant *var)
{
    if (var->free_me){
    var->free_me($P(var->val));
    }
}

TVariant *TVariant_new()
{
    TVariant* var = (TVariant*) malloc(sizeof (TVariant));
    assert(var);
    var->data_type=-1;
    var->name=0;
    var->val=0;
    var->free_me=0;
    return var;
}

void TVariant_free(TVariant **var_hld)
{
    free((*var_hld)->name);
    free(*var_hld);
    *var_hld=0;
}

char *TVariant_name(TVariant *var)
{
    return var->name;
}

void TVariant_set_name(TVariant *var, const char *name)
{
    char* str =var->name;
    var->name=TData_clone_name(name);
    if(str) free(str);
}

TVar TVariant_value(TVariant *var)
{
    return var->val;
}

void TVariant_set_value(TVariant *var, TVar value)
{
    assert(var);
    if (var->free_me) {
        var->free_me($P(var->val));
    }
    if(var)
    var->val=value;
}

TTypes TVariant_type(TVariant *var)
{
    return var->data_type;
}

void TVariant_set_type(TVariant *var, TTypes data_type)
{
    var->data_type=data_type;
}

void TVariant_clean_free(TVariant **var_hld)
{
    TVariant_clean(*var_hld);
    TVariant_free(var_hld);
}
