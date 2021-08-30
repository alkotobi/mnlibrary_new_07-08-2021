#include "mnrecord_test.h"

char mnrecord_test(){
    print_blue("tetsing mnrecord_new...\n");
    print_blue("testing mnrecord_add_field_byref...\n");
    print_blue("tetsing mnrecord_field_byind_ref...\n");
    NEW_TRASH();
    mnrecord* rcd=mnrecord_new();
    mnfield* fld=mnfield_new_int("ID",0);
    mnrecord_add_field_byref(rcd,fld);
    mnrecord_add_field_byref(rcd,mnfield_new_cloned_cstring("name","Nour"));
    mnrecord_add_field_byref(rcd,mnfield_new_double("price",12.5));
    mnfield* fld1= TO_TRASH_FLD(mnfield_new_int("ID",0));
    mnfield* fld2= TO_TRASH_FLD(mnfield_new_cloned_cstring("name","Nour"));
    mnfield* fld3= TO_TRASH_FLD(mnfield_new_double("price",12.5));
    char res = mnfield_is_equal(mnrecord_field_byind_ref(rcd,2),fld1);
    res=res*mnfield_is_equal(mnrecord_field_byind_ref(rcd,3),fld2);
    res=res*mnfield_is_equal(mnrecord_field_byind_ref(rcd,4),fld3);
    test(res,"working...\n");
    print_blue("tetsing mnrecord_sql_create_table...\n");
    char* sql=mnrecord_sql_create_table(rcd,"Table");
    print_yellow( sql);
    print_blue("\n");
    res=cstring_is_equal(sql,"CREATE TABLE IF NOT EXISTS 'Table'"
                                    " ('ID' INTEGER PRIMARY KEY AUTOINCREMENT,"
                                    "'ID' int,'name' TEXT,'price' double);");
    test(res,"working...\n");
    print_blue("tetsing mnrecord_sql_select_with_clause...\n");
    cstring_free($P(sql));
    sql= mnrecord_sql_select_with_clause_cstring(rcd,"nono",
                                                 0,0,0,0);
    print_yellow(sql);
    print_blue("\n");
    res=cstring_is_equal(sql,"  SELECT ID,name,price FROM nono  where name='touti' ");
    test(res,"working...\n");
    cstring_free($P(sql));
    print_blue("tetsing mnrecord_sql_binding_params...\n");
    sql=mnrecord_sql_binding_params(rcd);
    res=cstring_is_equal(":ID,:name,:price",sql);
    print_yellow(sql);
    print_blue("\n");
    test(res,"workin...\n");
    print_blue("tetsing mnrecord_sql_insert_with_params_cstring...\n");
    cstring_free($P(sql));
    sql=mnrecord_sql_insert_with_params_cstring(rcd,"mimi");
    print_yellow(sql);
    print_blue("\n");
    res=cstring_is_equal("INSERT INTO mimi(ID,name,price) VALUES(:ID,:name,:price)",sql);
    test(res,"workin...\n");

    print_blue("tetsing mnrecord_sql_update_with_params...\n");
    cstring_free($P(sql));
    sql=mnrecord_sql_update_with_params(rcd,"minouna","where ID =0");
    print_yellow(sql);
    print_blue("\n");
    res=cstring_is_equal("UPDATE minouna SET ID = :ID,name = :name,price = :price where ID =0",
                         sql);
    test(res,"workin...\n");

    print_blue("tetsing mnrecord_free...\n");
    mnrecord_free(rcd);
    test(1,"working...\n");

    cstring_free($P(sql));
    EMPTY_TRASH();
    return res;
}
