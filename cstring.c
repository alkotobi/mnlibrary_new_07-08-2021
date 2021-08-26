#include "cstring.h"


TLint cstring_count(const char *str)
{
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
void cstring_init_Tdata(TData* data, const char* str){
    TData_init (CString,data,(TVar)str,cstring_free,
                (TFVarVar)cstring_new_clone,
                (TFCharVarVar)cstring_is_equal,
                (TFCharVarVar)cstring_is_greater);
}

TData *cstring_new_TData(const char* str)
{
    TData* data= TData_new();
    cstring_init_Tdata(data,str);
    return data;
}

TData cstring_to_TData(TCstring str)
{
    TData data;
    cstring_init_Tdata(&data,str);
    return data;
}

TCstring cstring_from_TData_ref(TData* data){

    return  (TCstring) TData_value(data);
}
TCstring cstring_from_TData_cpy(TData* data){
    return  cstring_new_clone( (TCstring) TData_value(data));
}

TCstrings *TCstrings_new()
{
    return TArray_new();
}

void TCstrings_init(TCstrings *str_list)
{
    TArray_init(str_list);
}

void TCstrings_clean(TCstrings *str_list){
    TArray_clean(str_list,cstring_free);
}

void TCstrings_free(TCstrings **str_list)
{
    free(*str_list);
    *str_list=0;
}

void TCstrings_add(TCstrings *str_list, TCstring str)
{
    TArray_add(str_list,str);
}

TCstring TCstrings_concat(TCstrings *str_list, TCstring end_line)
{
    TLint end_lines_count=cstring_count(end_line)*TArray_count(str_list);
    TLint char_count=TCstrings_char_count(str_list);
    TCstring str =(TCstring) malloc(sizeof (char)*(end_lines_count+char_count+1));
    assert(str);
    for (TLint i=0;i<TArray_count(str_list) ;i++ ) {
        cstring_add_chars(str,TArray_item_at(str_list,i));
        cstring_add_chars(str,end_line);
    }
    return str;

}

TLint TCstrings_char_count(TCstrings *str_list)
{
    TLint char_count=0;
    for (TLint i=0;i<TArray_count(str_list) ;i++ ) {
        char_count=char_count+ cstring_count(TCstrings_item_at(str_list,i));
    }
    return char_count;
}

TCstring TCstrings_item_at(TCstrings *str_list, TLint index)
{
    return (TCstring)TArrayData_item_at(str_list,index);
}


char* TCstrings_concat_multi(const char *str,...){
    va_list ap;
    int i=0;
    int j=0;
    va_start(ap, str);
    char* str1 =cstring_new(250);
    TCstrings* list =TCstrings_new();
    TCstrings_init(list);
    while(str[i]!='\0'){
        if(str[i]=='%'){
            str1[j]=0;
            TCstrings_add(list,cstring_new_clone(str1));
            i++;
            if(str[i]=='s'){
                char*s =cstring_new_clone(va_arg(ap, char*));
                TCstrings_add(list,s);
            }
            else if(str[i]=='d'){
                char* s = cstring_new(200);
                sprintf(s,"%d",va_arg(ap, int));
                TCstrings_add(list,s);
            }
            else if(str[i]=='f'){//for mnstring
                char* s = cstring_new(200);
                sprintf(s,"%f",va_arg(ap, double));
                TCstrings_add(list,s);
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
    TCstrings_add(list,str1);
    char*s=TCstrings_concat(list,"");
    TCstrings_clean(list);
    TCstrings_free(&list);
    return  s;
}
