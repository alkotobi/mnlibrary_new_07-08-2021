#ifndef MNTYPES_H
#define MNTYPES_H
#include <stdlib.h>
#include <assert.h>
#define ARRAY_MIN_SIZE 250
typedef long int TLint ;
typedef void** TPtrHld ;
typedef char** TCstrHld ;
#define $P(X) (TPtrHld)(&X)
typedef void** TValues ;
typedef void* TVar;
typedef void* TFunction;
typedef enum {
    FVarVar,
    FCharVarVar,
    FVoidPtrHld,
    FVarVoid,
    FVoidVarVar,
    FLintVar,
    FVarVarLint,
    VoidVar
}TFunTypes ;
typedef enum {
    CString,
    Double,
    Int,
    Field,
    MNString
} TTypes ;
typedef TVar (*TFVarVar)(TVar);
typedef char(*TFCharVarVar)(TVar,TVar) ;
typedef void(*TFVoidPtrHld)(TPtrHld) ;
typedef TVar(*TFVarVoid)(void) ;
typedef void(*TFVoidVarVar)(TVar,TVar) ;
typedef TLint(*TFLintVar)(TVar) ;
typedef TVar(*TFVarVarLint)(TVar,TLint) ;
typedef void(*TFVoidVar)(TVar) ;
typedef TLint(*TFLintVarVar)(TVar,TVar) ;
typedef char* TCstring ;

TVar TValues_new(TLint size);
void TValues_realloc(TValues* arr,TLint new_size);
void TValues_free(TValues *arr);




struct TVariant{
    TTypes data_type;
    TVar val;
    char* name;
    TFVoidPtrHld free_me;
};
typedef struct TVariant TVariant ;

TVariant* TVariant_init(TVariant* var,     TTypes data_type,
              TVar val,
              const char *name,TFVoidPtrHld free_me);
void TVariant_clean(TVariant * var);
TVariant* TVariant_new();
void TVariant_free(TVariant** var_hld);
char* TVariant_name(TVariant* var);
void TVariant_set_name(TVariant* var,const char* name);
TVar TVariant_value(TVariant* var);
void TVariant_set_value(TVariant* var ,TVar value);
TTypes TVariant_type(TVariant* var);
void TVariant_set_type(TVariant* var,TTypes data_type);
void TVariant_clean_free(TVariant** var_hld);
TVariant* TVariant_clone(TVariant* var,TFVarVar clone_val);

struct TDataPriv{

    char is_read_only;
    char is_presistent;// cant free
    char is_visible;
};

struct TData{
    //struct TDataPriv priv;
    TVariant* var;
    TFVarVar clone_val;
    TFCharVarVar is_equal;
    TFCharVarVar is_greater;

};

typedef struct TData TData ;
TData* TData_new();
TData *TData_init(TTypes data_type,TData* data, TVar val, TFVoidPtrHld free_val,
                  TFVarVar clone_val,TFCharVarVar is_equal,TFCharVarVar is_greater);
void TData_init_v1(TTypes data_type,TData* data,  TVar val, TFVoidPtrHld free_val);
void TData_init_v2(TTypes data_type,TData* data,  TVar val, TFVoidPtrHld free_val,
                   TFVarVar clone_val);
void TData_clean(TData* data);
void TData_free(TPtrHld data);
void TData_clean_free(TData ** data_hld);
TData *TData_clone(TData*data);
void TData_clone_methods(TData* data_src,TData* data_des);
void TData_clone_properties(TData* data_src,TData* data_des);
TData *TData_new_persistent(TData*data);
void TData_set_variant(TData* data,TVariant* var);
TVariant* TData_variant(TData* data);
char TData_isEqual(TData* d1,TData*d2);
int TData_int_val(TData* d);
TVar TData_value(TData* d);
void TData_set_value(TData* d,  TVar val);
//char TData_is_read_only(TData* d);
//char TData_is_presistent(TData* d);
//void TData_set_readonly(TData*d , char valbool);
//void TData_set_presistent(TData*d , char valbool);
void TData_set_name(TData*d , const char *name);
char* TData_name(TData* d);
TTypes TData_type(TData* d);
//char TData_is_visible(TData*d);
//void TData_set_visible(TData*d,char visible_bool);
void TData_set_type(TData *d, TTypes data_type);
typedef TData TDataInt ;
void TDataInt_init(TDataInt* data,int val);
TDataInt* TDataInt_new_init(int val);
int TDataInt_val(TDataInt* i);

typedef TData TDataDouble ;
void TDataDouble_init(TDataInt* data,double val);
TDataInt* TDataDouble_new_init(double val);
double TDataDouble_val(TDataDouble* i);


#endif // MNTYPES_H
