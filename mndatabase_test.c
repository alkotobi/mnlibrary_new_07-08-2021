#include "mndatabase_test.h"




char mndatabase_test()
{
    NEW_TRASH();
    mnrecord *rdc=mnrecord_new();
    mnrecord_add_field_byref(rdc,mnfield_new_int("age",15));
    mnrecord_add_field_byref(rdc,mnfield_new_cloned_cstring("name","NONO"));

    print_blue("tetsing connection to sqlite db...\n");
    mnsqlite_params* params=mnsqlite_params_new("/Users/merhab/Desktop/testdb.db",0,0);
    mndatabase* db=mndatabase_new(SQLITE,params,0);
    test(db!=0,"working\n");
    print_blue("tetsing create table...\n");
    char res=mndatabase_exec(db,TO_TRASH_MNS(
                                 mnstring_new_from_cstring_ref(
                                     mnrecord_sql_create_table(rdc,"me"))));
    test(res,"working\n");
    print_blue("tetsing insert record in a table...\n");
    res=mndatabase_insert_record(db,rdc,"me");
    test(res!=0,"working\n");
    mnrecord_printf_title(rdc);
    mnrecord_printf(rdc);
    printf("the ID is: %d\n", mnfield_int_val(mnrecord_field_byname_ref(rdc,RECORD_ID)));
    print_blue("tetsing update record...\n");
    mnrecord_set_field_val_int(rdc,"age",99999);
    mnrecord_set_field_val_int(rdc,"ID",7);
    mndatabase_update_record(db,rdc,"me");
    mnrecord_printf(rdc);
    test(1,"working\n");
    printf("the ID is: %d\n", mnfield_int_val(mnrecord_field_byname_ref(rdc,RECORD_ID)));

    print_blue("tetsing getdata from a table...\n");
    mnrecordset* rcd_set=mndatabase_get_data(db,"select * from me");
    mnrecordset_printf(rcd_set);
    test(1,"working\n");
    print_blue("tetsing get first record ...\n");
    mnrecord* first_record=mndatabase_first_record(db,"select * from me");
    mnrecord_printf(first_record);
    mnrecord_free(first_record);
    test(1,"working\n");
    print_blue("tetsing get record count ...\n");
    first_record=mndatabase_first_record(db,"select count() from me");
    mnrecord_printf(first_record);
    mnrecord_free(first_record);
    test(1,"working\n");
    print_blue("tetsing mnsql_table ...\n");
    mnsqltable* table =mnsqltable_new(db,"me",rdc,0,0,10);
    mnsqltable_open(table);
    mnrecord * rd=mnsqltable_get_record_at_index_ref(table,21);
    mnrecord_printf(rd);
    mnrecordset_printf(&table->recordset);
    print_blue("tetsing mnrecordset MNTOSTRING_CPY ...\n");
   // printf("%s\n",mnrecordset_printf(&table->recordset));

    mnrecord_free(rdc);
    mnsqlite_params_free(params);
    mndatabase_free(db);
    EMPTY_TRASH();
    return 1;
}
