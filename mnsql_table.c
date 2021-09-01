#include "mnsql_table.h"


mnsqltable* mnsqltable_new_v1(){
    mnsqltable * self= malloc(sizeof (mnsqltable)) ;
    TArray_init( &self->recordset);
    TArray_set_index(&self->recordset,0);
    self->is_active=0;


    return self;

}
mnsqltable *mnsqltable_new(mndatabase *database, const char *table_name,
                           mnrecord *fields,const char* where_sql,
                           const char* order_by_sql, int page_size)
{
    NEW_TRASH();
    mnsqltable * self= mnsqltable_new_v1();
    self->msql=mnsql_new_v1(table_name,
                            (TO_TRASH_MNS(mnstring_new_from_cstring_ref(
                                              mnrecord_sql_fields(fields))))->string,
                            where_sql,
                            order_by_sql,page_size,0);
    //mnsql_make_sql_ref(table->msql);
    self->database=database;
    self->fields=mnrecord_clone(fields);
    self->record_count=mnsqltable_get_record_count(self);
    TArray_set_index(&self->recordset,0);
    self->is_active=0;
    EMPTY_TRASH();
    return self;

}

int mnsqltable_get_record_count(mnsqltable* table){

    mnrecord* rdc=mndatabase_first_record(table->database,table->msql->sql_rec_count->string);
    int n= mnfield_int_val(mnrecord_field_byname_ref(rdc,"count"));
    mnrecord_free(rdc);
    return n;
}

void mnsqltable_free(void *table)
{
    mnsqltable* tbl=(mnsqltable*) table;
    mnsql_free(&(tbl->msql));
    mnrecord_free(tbl->fields);
    free(table);
}

void mnsqltable_open(mnsqltable *table)
{
    if(table->is_active){
        return;
    }
    mnsql_make_sql_ref(table->msql);
    mndatabase_add_data_to_recordset(&table->recordset,
                                     table->database,
                                     table->msql->sql->string);

}

void mnsqltable_close(mnsqltable *table)
{
    TArray_clean(&table->recordset,(TFVoidPtrHld)mnrecord_free_v0);
    mnsql_set_limit(table->msql,table->msql->limit,0);
    TArray_set_index(&table->recordset,0);
    table->is_active=0;
}



void mnsqltable_refresh(mnsqltable *table)
{
    mnsqltable_close(table);
    mnsqltable_open(table);
}

mnrecord *mnsqltable_get_record_at_index_ref(mnsqltable *table, TLint index)
{
    if (index >TArray_count(&table->recordset)-1 || index<0) {
        return 0;
    }

    while (index >TArray_count(&table->recordset)-1) {
        mnsql_set_limit(table->msql,table->msql->limit,TArray_count(&table->recordset));
        mndatabase_add_data_to_recordset(&table->recordset,
                                         table->database,
                                         table->msql->sql->string);

    }
    return  mnrecordset_record_by_ind_ref(&table->recordset,index);
}

void on_master_scroll(void*sender,void* receiver){
    if (sender) {

    }
    mnsqltable* tbl=receiver;
    mnsqltable_refresh(tbl);
}



mnsqltable *mnsqltable_clone(mnsqltable *tbl)
{
    return mnsqltable_new(tbl->database,
                          tbl->msql->table_name->string,
                          tbl->fields,tbl->msql->sql_where->string,
                          tbl->msql->sql_order_by->string,
                          tbl->msql->limit);
}

char mnsqltable_is_equal(mnsqltable *tbl1, mnsqltable *tbl2)
{
    return tbl1->database==tbl2->database &&
            mnsql_is_equal(tbl1->msql,tbl2->msql);
}
