#ifndef MNSQL_H
#define MNSQL_H
#include "mnarray.h"
#include "mnstring.h"

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct mnsql mnsql ;
struct mnsql {
    mnstring* table_name;
    mnstring* fields;
    mnstring* sql_order_by;
    mnstring* sql_where;
    TArray * filters;
    int limit;
    int offset;
    mnstring* sql;
    mnstring* sql_rec_count;


};
//typedef  enum logic_op logic_op  ;
enum logic_op {AND,OR};
mnsql* mnsql_new();
mnsql *mnsql_new_v1(const char* table_name,const char* fields,const char* w_where,const char* w_order_by,int limit,int offset);
void mnsql_free(mnsql** msql);
mnsql *mnsql_clone(mnsql* msql);
char mnsql_is_equal(mnsql* msql1, mnsql* msql2);
mnstring* mnsql_make_sql_ref(mnsql* msql);
void mnsql_add_filter(mnsql* msql,enum logic_op log_oper,const char* filter);
void mnsql_set_where(mnsql* msql,const char* w_where);
void mnsql_set_order(mnsql* msql,const char* w_order);
void mnsql_set_limit(mnsql* msql,int limit,int offset);
void mnsql_set_fields(mnsql* msql,const char* fields);
void mnsql_set_table(mnsql* msql,const char* table_name);
void mnsql_clear_filters(mnsql* msql);

#ifdef __cplusplus
}
#endif


#endif // MNSQL_H
