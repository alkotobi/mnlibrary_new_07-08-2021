#ifndef mnsqltable_H
#define mnsqltable_H
#include "mndatabase.h"

#include "mnsql.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef   struct {
    mnrecordset recordset;
    mndatabase* database;
    mnsql* msql;
    mnrecord* fields;    
    size_t record_count;
    char is_active;
}mnsqltable;

mnsqltable* mnsqltable_new(mndatabase* database,
                             const char* table_name,
                             mnrecord *fields,
                             const char *where_sql,
                             const char *order_by_sql,
                             int page_size);
mnsqltable* mnsqltable_new_v1();
int mnsqltable_get_record_count(mnsqltable* table);
void mnsqltable_free(void* table);
void mnsqltable_open(mnsqltable*table);
void mnsqltable_close(mnsqltable*table);
mnsqltable* mnsqltable_clone(mnsqltable* tbl);
char mnsqltable_is_equal(mnsqltable* tbl1,mnsqltable* tbl2);

void mnsqltable_refresh(mnsqltable* table);
mnrecord* mnsqltable_get_record_at_index_ref(mnsqltable* table , TLint index);


#ifdef __cplusplus
}
#endif

#endif // mnsqltable_H
