#ifndef MNRECORD_H
#define MNRECORD_H
#include "mnfield.h"
#ifdef __cplusplus
extern "C"
{
#endif

//typedef mnarray mnrecord;
struct mnrecord_prv{
    char is_new;
    char is_changed;
    char is_deleted;
    TFields* flds;
};

void mnrecord_prv_init(struct mnrecord_prv* prv);
typedef struct{

   struct mnrecord_prv prv;
} mnrecord;


#define RECORD_ID "ID"
#define MASTER_ID "MASTER_ID"
#define IS_EDITED "IS_EDITED"
#define IS_NEW "IS_NEW"
#define IS_DELETED "IS_DELETED"

mnrecord* mnrecord_new();
mnrecord* mnrecord_new_v0();
mnrecord* mnrecord_new_no_id();
void mnrecord_free(mnrecord *record);
void mnrecord_free_v0(mnrecord **record);
void mnrecord_printf(mnrecord* record);
void mnrecord_printf_title(mnrecord* record);
void mnrecord_add_field_byref(mnrecord* self,mnfield* field);
void mnrecord_add_field_bycpy(mnrecord* self,mnfield* field);
mnfield* mnrecord_field_byind_ref(mnrecord* self, TLint ind);
mnfield* mnrecord_field_byname_ref(mnrecord* self, const char *name);
void mnrecord_set_field_val_by_name(mnrecord *record, const char* field_name, TData *val);
char mnrecord_set_field_val_int(mnrecord *record, const char* field_name, int val);
char mnrecord_set_field_val_cstring(mnrecord *record, const char* field_name, const char* val);
char mnrecord_set_field_val_mnstring(mnrecord *record,
                                     const char* field_name,
                                     const char* val);
char mnrecord_set_field_val_double(mnrecord *record, const char* field_name, double val);

int mnrecord_get_field_val_int(mnrecord *record, const char* field_name);
char* mnrecord_get_field_val_cstring_ref(mnrecord *record, const char* field_name);
char* mnrecord_get_field_val_mnstring_ref(mnrecord *record,
                                     const char* field_name);
double mnrecord_get_field_val_double(mnrecord *record, const char* field_name);
char *mnrecord_sql_fields(mnrecord *record);
char* mnrecord_sql_select(mnrecord* record,char* table_name);
char* mnrecord_sql_select_with_clause(mnrecord* record,
                                          char* table_name,
                                          char* where_sql,
                                          char *order_by,
                                          int limit, int offset);
char* mnrecord_sql_select_with_clause_cstring(mnrecord* record,
                                                  const char* table_name,
                                                  const char* where_sql,
                                                  const char *order_by,
                                                  int limit, int offset);
char *mnrecord_sql_create_table(mnrecord *record, const char *table_name);
char *mnrecord_sql_binding_params(mnrecord *record);
char* mnrecord_sql_insert_with_params(mnrecord* record,const char *table_name);
char* mnrecord_sql_insert_with_params_cstring(mnrecord* record,const char* table_name);
char* mnrecord_sql_update_with_params(mnrecord* record,const char* table_name,
                                          const char *where_close);
mnrecord *mnrecord_clone(mnrecord *recor);
mnrecord *mnrecord_clone_generated(mnrecord *recor);
char mnrecord_is_equal(mnrecord* rcd1,mnrecord* rcd2);
int mnrecord_get_id(mnrecord* rdc);
TLint mnrecord_count(mnrecord* rdc);
TArray* mnrecord_fields(mnrecord* rdc);
char mnrecord_is_field_at_generated(mnrecord* rdc,TLint index);
char* mnrecord_field_at_name(mnrecord* rdc,TLint index);




typedef mnrecord TRecord ;
TRecord* TRecord_new();
TRecord* TRecord_init(TRecord* record);

#ifdef __cplusplus
}
#endif

#endif // MNRECORD_H
