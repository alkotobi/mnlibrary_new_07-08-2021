#include "mnrecord.h"

void mnrecord_prv_init(struct mnrecord_prv* prv){
    prv->flds=0;
    prv->is_changed=0;
    prv->is_deleted=0;
    prv->is_new=0;
}

mnrecord* mnrecord_new_v0(){
    mnrecord* rcd= malloc(sizeof (mnrecord));
    assert(rcd);
    mnrecord_prv_init(&rcd->prv);
    rcd->prv.flds =TArray_new();
    return rcd;
}


mnrecord *mnrecord_new()
{
    mnrecord* rcd= mnrecord_new_v0();
    mnfield* fld=mnfield_new_int(RECORD_ID,-1);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    fld=mnfield_new_int(MASTER_ID,-1);
    mnfield_set_generated(fld,1);
    mnrecord_add_field_byref(rcd,fld);
    fld=mnfield_new_int(IS_EDITED,0);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    fld=mnfield_new_int(IS_NEW,1);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    fld=mnfield_new_int(IS_DELETED,0);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    return rcd;

}

mnrecord* mnrecord_new_no_id(){
    mnrecord* rcd= mnrecord_new_v0();
    mnfield* fld=mnfield_new_int(IS_EDITED,0);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    fld=mnfield_new_int(IS_NEW,0);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    fld=mnfield_new_int(IS_DELETED,0);
    mnfield_set_generated(fld,0);
    mnrecord_add_field_byref(rcd,fld);
    return rcd;
}

void mnrecord_free(mnrecord* record){
    TFields_clean(record->prv.flds);
    TArray_free($P(record->prv.flds));
    free(record);
}

void mnrecord_printf(mnrecord* record){
    int a=0;
    TCstring str;
    double d;
    for (TLint i=0;i<(TArray_count(mnrecord_fields(record))) ;i++ ) {
        if (!TField_is_generated(TFields_item_at(mnrecord_fields(record),i))) {
            continue;
        }
        mnfield* fld = mnrecord_field_byind_ref(record,i);
        switch (TField_type(fld)) {
        case CString:
            str=mnfield_cstring_val_ref(fld);
            printf(" %s  ",str);
            break;
        case Int:
            a=mnfield_int_val(fld);
            printf(" %d  ",a);
            break;
        case Double:
            d=mnfield_double_val(fld);
            printf(" %f  ",d);
            break;
        default:break;
        }
    }
    printf("\n");
}

void mnrecord_printf_title(mnrecord* record){
    for (TLint i=0;i<(TArray_count(mnrecord_fields(record)))  ;i++ ) {
        if (TField_is_generated(mnrecord_field_byind_ref(record,i))) {
            char* str=TField_name(mnrecord_field_byind_ref(record,i));
            printf("%s   ",str);
        }


    }
    printf("\n");
}
void mnrecord_add_field_byref(mnrecord* self,mnfield* field){
    TFields_add(mnrecord_fields(self),field);
}

void mnrecord_add_field_bycpy(mnrecord* self,mnfield* field){
    TFields_add(mnrecord_fields(self),mnfield_clone(field));
}

mnfield* mnrecord_field_byind_ref(mnrecord* self,TLint ind){
    if (ind>=TArray_count(mnrecord_fields(self)) || ind<0) {
        return 0;
    }
    return  TFields_item_at(mnrecord_fields(self),ind);
}

mnfield* mnrecord_field_byname_ref(mnrecord* self, const char* name){
   return TFields_item_by_name(mnrecord_fields(self),name);
}
//TODO: test



void mnrecord_set_field_val_by_name(mnrecord* record, const char* field_name,
                                     TData *val){
    mnfield* fld =mnrecord_field_byname_ref(record,field_name);
     TField_set_data(fld,val);
}
char mnrecord_set_field_val_int(mnrecord *record, const char* field_name, int val){
    mnfield* fld =mnrecord_field_byname_ref(record,field_name);
    if (fld) {
        mnfield_setval_int(fld,val);
    }
    return fld!=0;
}
char mnrecord_set_field_val_cstring(mnrecord *record, const char* field_name, const char* val){
    mnfield* fld =mnrecord_field_byname_ref(record,field_name);
    if (fld) {
        mnfield_setval_cstring(fld,val);
    }
    return fld!=0;
}
char mnrecord_set_field_val_mnstring(mnrecord *record,
                                     const char* field_name,
                                     const char *val){
    mnfield* fld =mnrecord_field_byname_ref(record,field_name);
    if (fld) {
        mnfield_setval_cstring(fld,val);
    }
    return fld!=0;
}
char mnrecord_set_field_val_double(mnrecord *record, const char* field_name, double val){
    mnfield* fld =mnrecord_field_byname_ref(record,field_name);
    if (fld) {
        mnfield_setval_double(fld,val);
    }
    return fld!=0;
}

double mnrecord_get_field_val_double(mnrecord *record, const char *field_name)
{
    mnfield* fld= mnrecord_field_byname_ref(record,field_name);

    return mnfield_double_val(fld);
}
int mnrecord_get_field_val_int(mnrecord *record, const char* field_name){
    mnfield* fld= mnrecord_field_byname_ref(record,field_name);

    return mnfield_int_val(fld);
}
char* mnrecord_get_field_val_cstring_ref(mnrecord *record, const char* field_name){
    mnfield* fld= mnrecord_field_byname_ref(record,field_name);

    return mnfield_cstring_val_ref(fld);
}

char *mnrecord_get_field_val_mnstring_ref(mnrecord *record,
                                              const char* field_name){
    mnfield* fld= mnrecord_field_byname_ref(record,field_name);

    return mnfield_cstring_val_ref(fld);
}
char *mnrecord_sql_fields(mnrecord *record)
{
    TCstrings* strs= TCstrings_init(TCstrings_new());
    for(TLint i=0;i<(mnrecord_count(record));i++){
        if(!TField_is_generated(mnrecord_field_byind_ref(record,i))) continue;
        TCstrings_add_clone(strs,(TField_name(mnrecord_field_byind_ref(record,i))));
        if(i!=mnrecord_count(record)-1)
            TCstrings_add_clone(strs,(","));
    }
    TCstring sql = TCstrings_concat(strs,"");
    TCstrings_clean(strs);
    TCstrings_free(&strs);

    return sql;
}
char *mnrecord_sql_select(mnrecord* record, char *table_name){
    char* fields=mnrecord_sql_fields(record);
    char* sql =TCstrings_concat_multi(" SELECT %s FROM %s ",fields,table_name);
    cstring_free($P(fields));
    return sql;

}



char *mnrecord_sql_select_with_clause(mnrecord* record,
                                          char *table_name,
                                          char *where_sql, char *order_by,
                                          int limit, int offset){
    TCstrings* strs_tmp =TCstrings_init(TCstrings_new());
    if(!where_sql) {
        where_sql =TCstrings_add(strs_tmp,cstring_new(1));
    }
    if(!order_by){
        order_by=TCstrings_add(strs_tmp,cstring_new(1));
    }
    char* select =TCstrings_add(strs_tmp,mnrecord_sql_select(record,table_name));
    char* limit_sql=0 ;
    if(limit){
        limit_sql=TCstrings_add(strs_tmp,TCstrings_concat_multi(" LIMIT %d OFFSET %d ",limit,offset));
    }else
    {
        limit_sql = TCstrings_add(strs_tmp,cstring_new(1));
    }
    char* sql = TCstrings_concat_multi(" %s %s %s %s",select,where_sql,order_by,limit_sql);

    TCstrings_clean_free(&strs_tmp);
    return sql;
}

char *mnrecord_sql_create_table(mnrecord *record,const char* table_name)
{
    // clone record and keep only generated fields
    mnrecord* rcd =mnrecord_new_v0();
    for (TLint i=0;i<mnrecord_count(record) ;i++ ) {

        if(!mnrecord_is_field_at_generated(record,i)) continue;
        mnrecord_add_field_bycpy(rcd,mnrecord_field_byind_ref(record,i));
    }
    TLint i=0;
    char* str=TCstrings_concat_multi("CREATE TABLE IF NOT EXISTS '%s%s",
                                            table_name,"' (");
    if(cstring_is_equal(mnrecord_field_at_name(rcd,0),"ID")){
        cstring_add(&str,"'ID' INTEGER PRIMARY KEY AUTOINCREMENT,");
        i=1;
    }


    for(;i<mnrecord_count(rcd);i++){

        mnfield* fld=mnrecord_field_byind_ref(rcd,i);
        TTypes type=TField_type(fld);
        char* strType;
        switch (type) {
        case CString:
            strType =cstring_new_clone("TEXT");
            break;
        case Int:
            strType =cstring_new_clone("int");
            break;
        case Double:
            strType =cstring_new_clone("double");
            break;

        default:
            strType =0;
            break;
        }


        char* str1=TCstrings_concat_multi("'%s%s%s",TField_name(fld),"' ",strType);
        cstring_free($P(strType));
        if(!(i==mnrecord_count(rcd)-1)){
            cstring_add(&str1,",");
        }
        cstring_add(&str,str1);
    }

    cstring_add(&str,");");
    mnrecord_free(rcd);
    return str;

}

char *mnrecord_sql_insert_with_params(mnrecord* record, const char *table_name){
    // INSERT INTO TABLE_NAME(fld,..) VALUES(?,...)
     TCstrings* strs_tmp =TCstrings_init(TCstrings_new());
    char* sql= TCstrings_concat_multi(
                "INSERT INTO %s(%s) VALUES(%s)",
                table_name,TCstrings_add(strs_tmp,mnrecord_sql_fields(record)),
                TCstrings_add(strs_tmp,mnrecord_sql_binding_params(record)));

    TCstrings_clean_free(&strs_tmp);
    return sql;
}

char *mnrecord_sql_binding_params(mnrecord *record)
{
    char* sql =cstring_new(1);
    for(TLint i=0;i<mnrecord_count(record);i++){
        if(!mnrecord_is_field_at_generated(record,i)) continue;
        cstring_add(&sql,":");
        cstring_add(&sql,mnrecord_field_at_name(record,i));
        if(i!=mnrecord_count(record)-1)
            cstring_add(&sql,",");
    }
    //sql->string[sql->last_char_pos]=' ';
    return sql;
}


char mnrecord_is_equal(mnrecord *rcd1, mnrecord *rcd2)
{
    if (mnrecord_count(rcd1)!=mnrecord_count(rcd2)) {
        return 0;
    }
    for (TLint i=0;i<mnrecord_count(rcd1) ;i++ ) {
        if (!mnfield_is_equal(mnrecord_field_byind_ref(rcd1,i),
                              mnrecord_field_byind_ref(rcd2,i))) {
            return 0;
        }
    }
    return 1;
}

char *mnrecord_sql_select_with_clause_cstring(mnrecord *record, const char *table_name,
                                                  const char *where_sql,
                                                  const char *order_by,
                                                  int limit, int offset)
{
    TCstrings* strs_tmp =TCstrings_init(TCstrings_new());
    char* sql=mnrecord_sql_select_with_clause(record,
                                                 TCstrings_add_clone(strs_tmp,table_name),
                                                 TCstrings_add_clone(strs_tmp,(where_sql)),
                                                 TCstrings_add_clone(strs_tmp,(order_by)),
                                                 limit,offset);

    TCstrings_clean_free(&strs_tmp);
    return sql;

}

char *mnrecord_sql_insert_with_params_cstring(mnrecord *record, const char *table_name)
{
    char* sql=mnrecord_sql_insert_with_params(record,table_name);
    return sql;
}

char *mnrecord_sql_update_with_params(mnrecord *record, const char *table_name,
                                      const char *where_close)
{
    /*
 UPDATE table_name
 SET column1 = value1, column2 = value2, ...
 WHERE condition;
      */
    char* str=TCstrings_concat_multi("%s %s SET ","UPDATE",table_name);
    for (TLint i=0;i<mnrecord_count(record) ;i++ ) {
        mnfield* fld=mnrecord_field_byind_ref(record,i);
        if (!TField_is_generated(fld)) {
            continue;
        }
        char s[(cstring_count(TField_name(fld))*2)+10];//=fld->name->string;
        sprintf(s,"%s = :%s", TField_name(fld),TField_name(fld));
        if (i==mnrecord_count(record)-1) {
            sprintf(s,"%s = :%s ", TField_name(fld),TField_name(fld));
        }else {
            sprintf(s,"%s = :%s,", TField_name(fld),TField_name(fld));
        }
        cstring_add(&str,s);

    }
    if (where_close) {
        cstring_add(&str,where_close);
    }
    return str;
}

mnrecord *mnrecord_clone(mnrecord *recor)
{
    mnrecord* rds=recor;
    mnrecord* record=mnrecord_new_v0();
    for (TLint i =0;i<mnrecord_count(rds) ;i++ ) {
        mnrecord_add_field_bycpy(record,mnrecord_field_byind_ref(rds,i));
    }
    return record;

}

mnrecord *mnrecord_clone_generated(mnrecord *recor){
    mnrecord* rds=recor;
    mnrecord* record=mnrecord_new_v0();
    for (TLint i =0;i<mnrecord_count(rds) ;i++ ) {
        if (mnrecord_is_field_at_generated(rds,i)) {
            mnrecord_add_field_bycpy(record,mnrecord_field_byind_ref(rds,i));
        }
    }
    return record;
}

int mnrecord_get_id(mnrecord *rdc)
{
    return mnrecord_get_field_val_int(rdc,RECORD_ID);
}


TArray* mnrecord_fields(mnrecord* rdc){
    return rdc->prv.flds;
}

TLint mnrecord_count(mnrecord *rdc)
{
    return TArray_count( mnrecord_fields(rdc));
}


char mnrecord_is_field_at_generated(mnrecord *rdc, TLint index)
{
    return TField_is_generated(mnrecord_field_byind_ref(rdc,index));
}

char *mnrecord_field_at_name(mnrecord *rdc, TLint index)
{
   return TField_name(mnrecord_field_byind_ref(rdc,index));
}
