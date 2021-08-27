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
    Field
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



struct TDataMethods{

};

struct TDataPriv{
    TTypes data_type;
    TVar val;
    char is_read_only;
    char is_presistent;// cant free
    char* name;
    char is_visible;
};

struct TData{
   struct TDataMethods methods;
   struct TDataPriv priv;
   TFVoidPtrHld free_val;
   TFVarVar clone_val;
   TFCharVarVar is_equal;
   TFCharVarVar is_greater;

};

typedef struct TData TData ;
TData* TData_new();
void TData_init(TTypes data_type,TData* data, TVar val, TFVoidPtrHld free_val,
                TFVarVar clone_val,TFCharVarVar is_equal,TFCharVarVar is_greater);
void TData_init_v1(TTypes data_type,TData* data,  TVar val, TFVoidPtrHld free_val);
void TData_init_v2(TTypes data_type,TData* data,  TVar val, TFVoidPtrHld free_val,
                   TFVarVar clone_val);
void TData_clean(TData* data);
void TData_free(TPtrHld data);
TData *TData_clone(TData*data);
void TData_clone_methods(TData* data_src,TData* data_des);
void TData_clone_properties(TData* data_src,TData* data_des);
TData *TData_new_persistent(TData*data);
char TData_isEqual(TData* d1,TData*d2);
int TData_int_val(TData* d);
TVar TData_value(TData* d);
void TData_set_value(TData* d,  TVar val);
char TData_is_read_only(TData* d);
char TData_is_presistent(TData* d);
void TData_set_readonly(TData*d , char valbool);
void TData_set_presistent(TData*d , char valbool);
void TData_set_name(TData*d , const char *name);
char* TData_name(TData* d);
TTypes TData_type(TData* d);
char TData_is_visible(TData*d);
void TData_set_visible(TData*d,char visible_bool);
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
