/*
 * mndatabase.h
 *
 *  Created on: ٠٣‏/٠٥‏/٢٠٢١
 *      Author: merhab
 */

#ifndef MNDATABASE_H_
#define MNDATABASE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "mnstring.h"
#include "mnrecordset.h"
#include "sqlite3.h"
#include <stdio.h>


#define MN_ROW         100
#define MN_OK            0
#define MN_DONE        101
#define DEFAULT_SQLITE_DB "default_sqlite"


typedef struct{
    mnstring* path;
    mnstring* user;
    mnstring* pass;
}mnsqlite_params;
mnsqlite_params* mnsqlite_params_new(const char *path, char*user, char*pass);
void mnsqlite_params_free(mnsqlite_params* params);
mnsqlite_params* mnsqlite_params_clone(mnsqlite_params* params);

typedef struct{
    sqlite3* sqlite_db;
    mnsqlite_params* sqlite_params;
}mnsqlite;



char mnsqlite_free(mnsqlite* database);
mnsqlite *mnsqlite_new(mnsqlite_params *params);
char mnsqlite_db_exec(mnsqlite* database,const char* sql);
//TODO: int maybe not enough for ID
int mnsqlite_last_insert_id(mnsqlite* database);
mnrecord *mnsqlite_first_record(mnsqlite* database, const char* sql);
mnrecordset* mnsqlite_get_data(mnsqlite* database, const char *sql);
void mnsqlite_add_data_to_recordset(mnrecordset* recordset,mnsqlite* database, const char *sql);




typedef enum{SQLITE=0,MYSQL=1}db_drivers;



typedef struct{
    db_drivers driver;
    void* connection;
    mnstring* name;
}mndatabase;


void mndatabase_free(mndatabase* database);
char mndatabase_is_valid(mndatabase* self);
char mndatabase_exec(mndatabase* self,mnstring* sql);
//TODO:in case int is not enough for the id
int mndatabase_last_insert_id(mndatabase* db);
mnrecord *mndatabase_first_record(mndatabase* db,const char* sql);
char mndatabase_insert_record(mndatabase* db,mnrecord* record,const char* table_name);
char mndatabase_update_record(mndatabase* db,mnrecord* record,const char* table_name);
mnrecordset* mndatabase_get_data(mndatabase* self, const char* sql);
void mndatabase_add_data_to_recordset(mnrecordset* recordset,mndatabase* self, const char* sql);
mndatabase* mndatabase_new(db_drivers driver, void* connection_params,const char* name);




/*
 * database info
 */

mnrecord* mndatabase_login_info_record_new();


#ifdef __cplusplus
}
#endif

#endif /* MNDATABASE_H_ */
