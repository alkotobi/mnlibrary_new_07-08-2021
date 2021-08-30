#include "mnstring.h"



mnstring *mnstring_new(size_t size)
{
    mnstring* self=malloc(sizeof (mnstring));
    self->string =malloc(sizeof(char)*size+1);
    self->string[0]=0;
    self->count=0;
    self->size=size;
    return self;
}

mnstring *mnstring_new_v1(){
    return mnstring_new(ARRAY_MIN_SIZE);
}

void mnstring_free(mnstring **str)
{
    free((*str)->string);
    (*str)->string=0;
    free(*str);
    *str=0;
}

mnstring *mnstring_clone(mnstring *str)
{
    mnstring* string=mnstring_new(str->size);
    for (int i=0;i<str->count ;i++ ) {
        string->string[i]=str->string[i];
    }
    string->count=str->count;
    string->string[str->count]=0;
    return string;
}

char mnstring_is_equal(mnstring *str1, mnstring *str2)
{
    if (str1->count!=str2->count) {
        return 0;
    }
    for (int i=0;i<str1->count ;i++ ) {
        if (str1->string[i]!=str2->string[i]) {
            return 0;
        }
    }
    return 1;
}




void mnstring_free_v0(void* str){
    mnstring_free((mnstring**)&str);
}
mnstring *mnstring_new_from_cstring_ref(char *string){
    if(!string) return mnstring_new_from_cstring_cpy("");
    int count=cstring_count(string);
    mnstring* mstring =mnstring_new(count);
    char* str =string;//cstring_new_copy_with_char_count(string,count);
    mstring->string=str;
    mstring->count=count;
    mstring->size=count;
    return mstring;
}
mnstring *mnstring_new_from_cstring_cpy(const char *string)
{
    if(!string) return mnstring_new_from_cstring_cpy("");
    int count=cstring_count(string);
    char* str =cstring_new_copy_with_char_count(string,count);
    return mnstring_new_from_cstring_ref(str);
}

mnstring *mnstring_new_from_mnstring(const mnstring *str)
{
    if(!str) return mnstring_new_from_cstring_cpy("");
    mnstring* mstring =mnstring_new(str->count);
    char* string =cstring_new_copy_with_char_count(str->string,str->count);

    mstring->string=string;
    mstring->count=str->count;
    mstring->size=str->count;
    return mstring;
}
void *mnstring_new_from_mnstring_v0(void *s)
{
    mnstring* str=s;
    if(!str) return mnstring_new_from_cstring_cpy("");
    mnstring* mstring =mnstring_new(str->count);
    char* string =cstring_new_copy_with_char_count(str->string,str->count);

    mstring->string=string;
    mstring->count=str->count;
    mstring->size=str->count;
    return mstring;
}


mnstring* mnstring_new_from_concat(int strings_count,...)
{
    va_list L;
    int count = 0;
    va_start(L, strings_count);
    for (int i=0; i < strings_count; i++)
    {
        mnstring* str=va_arg(L, mnstring*);
        count = count+(str->count);
    }

    va_end(L);
    mnstring* str=mnstring_new(count);
    int j=0;
    va_start(L, strings_count);

    for (int i=0; i < strings_count; i++)
    {
        char* s=va_arg(L, mnstring*)->string;
        for (int i=0;s[i]!=0 ;i++ ) {
            str->string[j]=s[i];
            j++;
        }
    }
    str->string[j]=0;
    str->count=count;
    va_end(L);
    return str;
}

mnstring* mnstring_new_from_int(int n){
    if(n==0){
        return mnstring_new_from_cstring_cpy("0");
    }
    int neg=0;
    char str[20];
    int i=0;
    if(n<0){
        n=-n;
        neg=1;
    }
    while(n!=0){
        int a=n%10;
        str[i]=a+'0';
        n=(n-a)/10;
        i++;
    }
    str[i]=0;
    mnstring* str1= mnstring_new_from_cstring_cpy(str);
    int j=0;
    for(int i=str1->count-1;i>=0;i--){
        str1->string[j]=str[i];
        j++;
    }
    if (neg) {
        mnstring* str2=str1;
        str1=mnstring_new_from_cstring_cpy(cstring_new_from_concat(2,"-",str1->string));
        mnstring_free(&str2);
    }
    return str1;
}

mnstring* mnstring_new_from_double(double d){
    mnstring* s= mnstring_new(30);
    sprintf(s->string,"%f",d);
    return s;
}
mnstring* mnstring_new_concat_multi(const char *str,...){
    va_list ap;
    int i=0;
    int j=0;
    va_start(ap, str);
    char str1[250];
    TArray* list =TArray_init(TArray_new());
    while(str[i]!='\0'){
        if(str[i]=='%'){
            str1[j]=0;
            TArray_add_mnstring(list,mnstring_new_from_cstring_cpy(str1));
            i++;
            if(str[i]=='s'){
                TArray_add_mnstring(list,mnstring_new_from_cstring_cpy(va_arg(ap, char*)));
            }
            else if(str[i]=='d'){
                TArray_add_mnstring(list, mnstring_new_from_int(va_arg(ap, int)));
            }
            else if(str[i]=='m'){//for mnstring
                mnstring* ss= va_arg(ap, mnstring*);
                TArray_add_mnstring(list,mnstring_clone(ss));
            }
            j=0;
            i++;
            continue;
        }
        str1[j]=str[i];
        j++;
        i++;
    }
    va_end(ap);
    str1[j]=0;
    TArray_add_mnstring(list,mnstring_new_from_cstring_cpy(str1));
    mnstring*s=mnstring_new_from_array(list);
    TArry_clean_mnstring(list);
    TArray_free($P(list));
    return  s;
}

void mnstring_concat(mnstring *str_to, mnstring *str_sub)
{
    int count=str_to->count+str_sub->count;
    int i=str_to->count;
    if(str_to->size<(count)){
        str_to->string=realloc(str_to->string,sizeof (char)*(count+1));
        str_to->size=count;
    }
    int j=0;
    for (;i<count ;i++ ) {
        str_to->string[i]=str_sub->string[j];
        j++;
    }
    str_to->string[count]=0;
    str_to->count=count;
}

void mnstring_concat_msstr_cstr(mnstring *str_to, const char *str_sub)
{
    mnstring* str=mnstring_new_from_cstring_cpy(str_sub);
    mnstring_concat(str_to,str);
    mnstring_free(&str);
}



mnstring *mnstring_new_empty()
{
    return mnstring_new_from_cstring_cpy("");
}

char mnstring_is_empty(mnstring* str){
    return cstring_is_empty(str->string);
}

mnstring *mnstring_new_from_array(TArray *list)
{
    int size=0;
    for (TLint i=0;i<TArray_count(list) ;i++ ) {
        //if (!list->data[1])continue;
        size=size+(TArray_mnstring_at(list,i)->count);
    }
    mnstring*s= mnstring_new(size);
    int j=0;
    for (TLint i=0;i<TArray_count(list) ;i++ ) {
        //if (!list->data[1])continue;
        mnstring* str =TArray_mnstring_at(list,i);
        for (int n=0;n<str->count ;n++ ) {
            s->string[j]=str->string[n];
            j++;
        }
    }
    s->string[j]=0;
    s->count=j;

    return s;
}

TString *TString_new()
{
    TString* str=(TString*)malloc(sizeof (TString));
    assert(str);
    str->count=0;
    str->size=0;
    str->string=0;
    return str;
}

TString *TString_init(TString *str,  char *c_str)
{
    if (!c_str) {
        c_str=cstring_new(ARRAY_MIN_SIZE);
    }
    str->string=c_str;
    str->size=ARRAY_MIN_SIZE;
    return str;
}

void TString_clear(TString *str)
{
    cstring_free($P(str->string));
}

void TString_free(TString **str_hld)
{
    free(*str_hld);
    *str_hld=0;
}

TString *TString_init_with_cloned_cstr(TString *str, const char *c_str)
{
    return TString_init(str,cstring_new_clone(c_str));
}

TString *TString_init_with_empty_cstr(TString *str)
{
    return TString_init(str,0);
}

void TString_clear_free(TString **str_hld)
{
    TString_clear(*str_hld);
    TString_free(str_hld);
}

char mnstring_is_greater(mnstring* str1,mnstring*str2){
    return cstring_is_greater(str1->string,str2->string);
}

TData *TDAta_init_mnstring(TData *data, mnstring *str)
{
    return TData_init(MNString,data,(TVar)str,(TFVoidPtrHld)mnstring_free,
                      (TFVarVar)mnstring_clone,(TFCharVarVar)mnstring_is_equal,
                      (TFCharVarVar)mnstring_is_greater);
}

mnstring *TData_mnstring(TData *data)
{
    return (mnstring*) TData_value(data);
}

mnstring *TArray_add_mnstring(TArray *arr, mnstring *str)
{
    TArray_add(arr,(TVar)str);
    return str;
}

mnstring *TArray_mnstring_at(TArray *arr, TLint index)
{
    return (mnstring*)TArray_item_at(arr,index);
}

void TArry_clean_mnstring(TArray *arr)
{
    TArray_clean(arr,(TFVoidPtrHld)mnstring_free);
}
