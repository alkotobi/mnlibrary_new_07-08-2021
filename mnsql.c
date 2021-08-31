#include "mnsql.h"



mnsql *mnsql_new()
{
    mnsql* self=malloc(sizeof(mnsql));

    self->filters =TArray_init(TArray_new());
    self->limit=0;
    self->offset=0;
    self->sql=0;
    self->sql_order_by=0;
    self->table_name=0;
    self->fields=0;
    self->sql_where=0;
    return self;
}

void mnsql_free(mnsql **msql)
{

    mnsql* s=*msql;
    mnstring_free(&s->sql);
    TArry_clean_mnstring(s->filters);
    mnstring_free(&s->sql_order_by);
    mnstring_free(&s->table_name);
    mnstring_free(&s->fields);
    mnstring_free(&s->sql_where);
    free(s);
    *msql=0;
}

mnsql *mnsql_clone(mnsql *msql)
{
    mnsql* s=mnsql_new();
    s->filters=TArray_clone(msql->filters,(TFVarVar)mnstring_clone);
    s->limit=msql->limit;
    s->offset=msql->offset;
    s->sql=mnstring_clone(msql->sql);
    s->sql_order_by=mnstring_clone((msql->sql_order_by));
    s->table_name=mnstring_clone(msql->table_name);
    s->fields=mnstring_clone(msql->fields);
    s->sql_where=mnstring_clone(msql->sql_where);
    return s;
}

char mnsql_is_equal(mnsql *msql1, mnsql *msql2)
{
    return msql1->limit==msql2->limit &&
            msql1->offset==msql2->offset &&
            (TArray_is_equal(msql1->filters,msql2->filters,(TFCharVarVar)mnstring_is_equal)) &&
            (mnstring_is_equal(msql1->sql,msql2->sql))&&
            mnstring_is_equal(msql1->sql_order_by,msql2->sql_order_by) &&
            mnstring_is_equal(msql1->table_name,msql2->table_name) &&
            mnstring_is_equal(msql1->fields,msql2->fields) &&
            mnstring_is_equal(msql1->sql_where,msql2->sql_where) ;
}

mnstring *mnsql_make_sql_ref(mnsql *msql)
{
    TArray* arr=0;
    if (msql->fields==0 || msql->table_name==0) {
        return 0;
    }
    NEW_TRASH();
    mnstring* select_Sql =TO_TRASH_MNS(mnstring_new_concat_multi(" SELECT %m FROM %m ",
                                                                 msql->fields,
                                                                 msql->table_name));
    mnstring* where_sql=0;
    if (msql->sql_where!=0 && !mnstring_is_empty(msql->sql_where)) {
        where_sql =TO_TRASH_MNS(mnstring_new_concat_multi(" WHERE %m ",msql->sql_where));
    }else {
        where_sql=TO_TRASH_MNS(mnstring_new_empty());
    }
    mnstring* order_by =0;
    if (msql->sql_order_by!=0 && !mnstring_is_empty(msql->sql_order_by)) {
        order_by =TO_TRASH_MNS(mnstring_new_concat_multi(" ORDER BY %m ",msql->sql_order_by));
    }else {
        order_by=TO_TRASH_MNS(mnstring_new_empty());
    }
    mnstring* limit_sql=0;
    if (msql->limit!=0 ) {
        limit_sql =TO_TRASH_MNS(mnstring_new_concat_multi(" LIMIT %d OFFSET %d ",
                                                         msql->limit,
                                                         msql->offset));
    }else {
        limit_sql=TO_TRASH_MNS(mnstring_new_empty());
    }

    mnstring* filters=0;
    if (TArray_count(msql->filters)!=0 ) {
         arr=TArray_clone(msql->filters,(TFVarVar)mnstring_clone);
        if (!where_sql || mnstring_is_empty(where_sql)) {
            mnstring_free(TArray_item_at(arr,0));
            TArray_set_item_at(arr,mnstring_new_from_cstring_cpy(" WHERE "),0,0);
        }
        filters =TO_TRASH_MNS(mnstring_new_from_array(arr));
    }else {
        filters=TO_TRASH_MNS(mnstring_new_empty());
    }
    if (msql->sql) {
        mnstring_free(&msql->sql);
    }
    if (msql->sql) mnstring_free(&msql->sql);
    msql->sql=mnstring_new_from_concat(5,select_Sql,where_sql,filters,order_by,limit_sql);
    if (msql->sql_rec_count) mnstring_free(&msql->sql_rec_count);
    msql->sql_rec_count=mnstring_new_concat_multi("SELECT COUNT() as count from %m %m",
                                                  msql->table_name,where_sql);
    if (arr) {
    TArray_clean(arr,(TFVoidPtrHld)mnstring_free);
    TArray_free($P(arr));
    }
    EMPTY_TRASH();
    return msql->sql;
}

mnsql *mnsql_new_v1(const char *table_name,
                    const char *fields,
                    const char *w_where,
                    const char *w_order_by
                    , int limit,
                    int offset)
{
    mnsql* msql=mnsql_new();
    msql->fields=mnstring_new_from_cstring_cpy(fields);
    msql->limit=limit;
    msql->offset=offset;
    msql->sql_order_by=mnstring_new_from_cstring_cpy(w_order_by);
    msql->sql_where=mnstring_new_from_cstring_cpy(w_where);
    msql->table_name=mnstring_new_from_cstring_cpy(table_name);
    msql->sql=0;
    msql->sql_rec_count=0;
    mnsql_make_sql_ref(msql);
    return msql;
}

void mnsql_add_filter(mnsql* msql,enum logic_op log_oper, const char *filter)
{
    if (log_oper==AND) {
        TArray_add_mnstring(msql->filters,mnstring_new_from_cstring_cpy(" AND "));
    }
    else if (log_oper==OR) {
        TArray_add_mnstring(msql->filters,mnstring_new_from_cstring_cpy(" OR "));
    }else{
        return;
    }
    TArray_add_mnstring(msql->filters,mnstring_new_from_cstring_cpy(filter));
    mnsql_make_sql_ref(msql);
}

void mnsql_set_where(mnsql *msql, const char *w_where)
{
    if (msql->sql_where) {
        mnstring_free(&msql->sql_where);
    }
    msql->sql_where=mnstring_new_from_cstring_cpy(w_where);
    mnsql_make_sql_ref(msql);
}

void mnsql_set_order(mnsql *msql, const char *w_order)
{
    if (msql->sql_order_by) {
        mnstring_free(&msql->sql_order_by);
    }
    msql->sql_order_by=mnstring_new_from_cstring_cpy(w_order);
    mnsql_make_sql_ref(msql);
}

void mnsql_set_limit(mnsql *msql, int limit, int offset)
{
    msql->limit=limit;
    msql->offset=offset;
    mnsql_make_sql_ref(msql);
}

void mnsql_set_fields(mnsql *msql, const char *fields)
{
    if (msql->fields) {
        mnstring_free(&msql->fields);
    }
    msql->fields=mnstring_new_from_cstring_cpy(fields);
    mnsql_make_sql_ref(msql);
}

void mnsql_set_table(mnsql *msql, const char *table_name)
{
    if (msql->table_name) {
        mnstring_free(&msql->table_name);
    }
    msql->table_name=mnstring_new_from_cstring_cpy(table_name);
    mnsql_make_sql_ref(msql);
}

void mnsql_clear_filters(mnsql *msql)
{
    TArray_clean(msql->filters,(TFVoidPtrHld)mnsql_free);
    mnsql_make_sql_ref(msql);
}
