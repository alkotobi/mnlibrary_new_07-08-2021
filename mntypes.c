#include "mntypes.h"

TVar TValues_new(TLint size){
    TValues arr =(TValues)calloc(size,sizeof(TVar));
    assert(arr);
    return arr;
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
    d->clone_val=0;
    d->is_equal=0;
    d->is_greater=0;
    d->var=0;
    return d;
}

TData* TData_init(TTypes data_type, TData *data, TVar val,
                  TFVoidPtrHld free_val, TFVarVar clone_val,
                  TFCharVarVar is_equal, TFCharVarVar is_greater)
{
    data->clone_val=clone_val;
    data->is_equal=is_equal;
    data->is_greater=is_greater;
    data->var=TVariant_init(TVariant_new(),data_type,val,NAMELESS,free_val);
    return data;

}

void TData_clean(TData *data)
{
    TVariant_clean(data->var);
    TVariant_free(&data->var);
}

void TData_free(TPtrHld data)
{
    free(*data);
    *data=0;
}


TData* TData_clone(TData *data)
{
    assert(data->clone_val);
    TData* d = TData_new();
    TVariant* var=TVariant_clone(TData_variant(data),data->clone_val);
    TData_set_variant(d,var);
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
    return d;
}

TVariant* TData_variant(TData* data){
    return data->var;
}

TVariant* TData_set_variant(TData* data,TVariant* var){
    TVariant* v = TData_variant(data);
    data->var=var;
    return v;
}
void TData_clone_methods(TData *data_src, TData *data_des)
{
    data_des->clone_val=data_src->clone_val;
    data_des->var->free_me=data_src->var->free_me;
    data_des->is_equal=data_src->is_equal;
    data_des->is_greater=data_src->is_greater;
}

void TData_clone_properties(TData* data_src,TData* data_des){
    TData_set_name(data_des,TData_name(data_src));
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

TVar TData_set_value(TData *d, TVar val)
{
    return TVariant_set_value(d->var,val);
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


char* TData_to_new_cstring(TData* data){
    return TVariant_to_new_cstring(TData_variant(data));
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

TVar TVariant_set_value(TVariant *var, TVar value)
{
    TVar v =0;
    if(var){
        v =var->val;
        var->val=value;
    }

    return v;
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

TVariant *TVariant_clone(TVariant *var, TFVarVar clone_val)
{
    return TVariant_init(TVariant_new(),
                         TVariant_type(var),clone_val(TVariant_value(var)),
                         TVariant_name(var),var->free_me);
}

TVariant *TVariant_init_int(TVariant* var,int n)
{
    int* i=(int*)malloc(sizeof (int));
    assert(i);
    *i=n;
    var->val=i;
    var->data_type=Int;
    var->free_me= int_free;
    return var;
}


int TVariant_int(TVariant *var)
{
    return *(int*) var->val;
}

TVariant *TVariant_init_double(TVariant *var, double n)
{
    double* i=(double*)malloc(sizeof (double));
    assert(i);
    *i=n;
    var->val=i;
    var->data_type=Double;
    var->free_me= double_free;
    return var;
}

double TVariant_double(TVariant *var)
{
    return *(double*)var->val;
}

void TData_free_name(char** name_hld){
    free(*name_hld);
    *name_hld=0;
}
TVariant *TVariant_init_cstring(TVariant *var, const char *str)
{
    var->val=TData_clone_name(str);
    var->free_me=(TFVoidPtrHld)TData_free_name;
    var->data_type=CString;
    return var;
}

char *TVariant_cstring(TVariant *var)
{
    return (char*) var->val;
}

char* TVariant_to_new_cstring(TVariant* var){
    //TODO:test TVariant_to_new_cstring
    char* str=0;
    switch (TVariant_type(var)) {
    case Int:
        str=cstring_new_fill_with_char(' ',INT_PRINT_SIZE);
        char s[25] ;
        sprintf(s,"%d",TVariant_int(var));
        cstring_replace_sub_string_at(TCstringSize_init(str,INT_PRINT_SIZE),s,0);
        return str;
        break;
    case CString:
        str=cstring_new_fill_with_char(' ',STRING_PRINT_SIZE);
        cstring_replace_sub_string_at(TCstringSize_init(str,STRING_PRINT_SIZE),TVariant_cstring(var),0);
        return str;
        break;
    case Double:

        str=cstring_new_fill_with_char(' ',DOUBLE_PRINT_SIZE);
        char s1[50] ;
        sprintf(s1,"%f",TVariant_double(var));
        cstring_replace_sub_string_at(TCstringSize_init(str,DOUBLE_PRINT_SIZE),s1,0);
        return str;
        break;
    default:
        assert(0);
        break;

    }
}





TLint cstring_count(const char *str)
{
    if (!str) {
        return 0;
    }
    TLint j;j=0;
    for(;;){
        if(str[j]=='\0'){
            break;
        }
        j++;
    }
    return j;
}

TLint cstring_size(const char* str){
    return cstring_count(str)+1;
}

char* cstring_new(TLint size){
    char* str = (char*)malloc(sizeof (char)*(size+1));
    str[0]=0;
    assert(str);
    return str;
}

char* cstring_new_fill_with_char(char character,TLint size){
    char* str = cstring_new(size);
    str[size]=0;
    for (TLint i=0;i<size;i++) {
        str[i]=character;

    }
    return str;
}

char* cstring_replace_sub_string_at(TCstringSize str_src,char* str_sub,TLint index){
    assert(index<str_src.size);
    for (TLint i=index;i<str_src.size ; i++) {
        if (str_sub[i-index]==0) {
            return str_src.cstring;
        }
        str_src.cstring[i]=str_sub[i-index];
    }
    str_src.cstring[str_src.size]=0;
    return str_src.cstring;
}

char *cstring_new_clone(const  char *str)
{
    if (!str) {
        return 0;
    }
    int size=cstring_size(str);
    char* str2=malloc(sizeof (char)*size);
    assert(str2);
    for(int i=0;str[i]!=0;i++){
        str2[i]=str[i];

    }
    str2[size-1]=0;
    return str2;
}

char *cstring_new_copy_with_char_count(const char *str, int char_count)
{
    char* str2=malloc(sizeof (char)*(char_count+1));
    for(int i=0;i<char_count;i++){
        str2[i]=str[i];

    }
    str2[char_count]=0;
    return str2;
}

char cstring_is_equal(const char *str1, const char *str2)
{
    int count1= cstring_count(str1);
    int count2= cstring_count(str2);
    if (count1!=count2){
        return 0;
    }
    for (int i=0;i<count1 ;i++ ) {
        if(str1[i]!=str2[i]){
            return 0;
        }
    }
    return 1;
}
char *cstring_new_from_concat_with_nl(char ** str_list,size_t strings_count){
    size_t count=0;
    for (size_t i=0; i < strings_count; i++)
    {
        count = count+cstring_count(str_list[i]);
    }
    char* str=malloc(sizeof(char)*((count+1)+strings_count));
    int j=0;

    for (size_t i=0; i < strings_count; i++)
    {
        char* s=str_list[i];
        for (int i=0;s[i]!=0 ;i++ ) {
            str[j]=s[i];
            j++;
        }
        str[j]='\n';
        j++;
    }
    str[j]=0;
    return str;
}
char *cstring_new_from_concat_v1(char ** str_list,size_t strings_count){
    size_t count=0;
    for (size_t i=0; i < strings_count; i++)
    {
        count = count+cstring_count(str_list[i]);
    }
    char* str=malloc(sizeof(char)*(count+1));
    int j=0;

    for (size_t i=0; i < strings_count; i++)
    {
        char* s=str_list[i];
        for (int i=0;s[i]!=0 ;i++ ) {
            str[j]=s[i];
            j++;
        }
    }
    str[j]=0;
    return str;
}
char *cstring_new_from_concat(int strings_count,...)
{
    va_list L;
    int count = 0;
    va_start(L, strings_count);
    for (int i=0; i < strings_count; i++)
    {
        count = count+cstring_count(va_arg(L, char*));
    }

    va_end(L);
    char* str=malloc(sizeof(char)*(count+1));
    int j=0;
    va_start(L, strings_count);

    for (int i=0; i < strings_count; i++)
    {
        char* s=va_arg(L, char*);
        for (int i=0;s[i]!=0 ;i++ ) {
            str[j]=s[i];
            j++;
        }
    }
    str[j]=0;
    va_end(L);
    return str;
}

char cstring_is_empty(const char *str)
{
    return cstring_is_equal(str,"");
}

void cstring_free(void **str)
{
    free(*str);
    *str=0;
}

char cstring_is_greater(const char *str1, const char *str2)
{
    int len1=cstring_count(str1);
    int len2=cstring_count(str2);
    int len = len1<len2? len1:len2;
    for (int i =0;i<len ;i++ ) {
        if (str1[i]==str2[i]) {
            continue;
        }
        if(str1[i]<str2[i]) {
            return 0;
        }else{
            return 1;
        }
    }
    return 0;
}

void cstring_add_chars(TCstring str,TCstring chars){
    //TODO: cstring_add_chars redesign to avoid errors
    TLint str_count=cstring_count(str);
    TLint chars_count = cstring_count(chars);
    TLint j=0;
    TLint i = str_count;
    for (;i<str_count+chars_count ;i++ ) {
        str[i]=chars[j];
        j++;
    }
    str[i]=0;

}

TData* TData_init_cstring(TData* data, const char* str){
    return  TData_init (CString,data,(TVar)str,cstring_free,
                        (TFVarVar)cstring_new_clone,
                        (TFCharVarVar)cstring_is_equal,
                        (TFCharVarVar)cstring_is_greater);
}


char* TData_cstring(TData* d){
    return   (TCstring) TData_value(d);
}





TCstringSize TCstringSize_init(char *str, TLint size)
{
    TCstringSize s;
    s.cstring=str;
    s.size=size;
    return s;
}


//TString

TString *TString_new(){
    TString * str =(TString*)malloc(sizeof (TString));
    assert(str);
    str->count=0;
    str->size=0;
    str->cstring=0;
    return str;
}
TString *TString_init(TString *str, char *cstring)
{
    str->count=cstring_count(cstring);
    str->size =str->count;
    str->cstring=cstring_new_clone(cstring);
    return str;
}

void TString_clean(TString *str)
{
    free(str->cstring);
    str->cstring=0;
    str->count=0;
    str->size=0;
}

void TString_free(TString **str_hld)
{
    free(*str_hld);
    *str_hld=0;
}

TString *TString_insert_sub_at(TString *str_src, char *str_sub, int index)
{
    int sub_count=cstring_count(str_sub);
    if (str_src->count) {

    }
}

int TString_count(TString *str)
{
    return str->count;
}

void TString_set_count(TString *str, int count)
{
    str->count=count;
}

int TString_size(TString *str)
{
    return str->size;
}

void TString_set_size(TString *str, int size)
{
    str->size=size;
}

char *Tstring_cstring(TString *str)
{
    return str->cstring;
}

void TString_set_cstring(TString *str, char *cstring)
{
    str->cstring=cstring;
}
