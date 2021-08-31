/*
 * mndatabase.c
 *
 *  Created on: ٠٣‏/٠٥‏/٢٠٢١
 *      Author: merhab
 */

#include "mndatabase.h"


/*
 * mnsqlite
 *
 *  Created on: ٠٣‏/٠٥‏/٢٠٢١
 *      Author: merhab
 */
mnsqlite_params *mnsqlite_params_new(const char *path, char *user, char *pass)
{
    mnsqlite_params* par= malloc(sizeof (mnsqlite_params));
    par->pass=mnstring_new_from_cstring_cpy(pass);
    par->user=mnstring_new_from_cstring_cpy(user);
    par->path=mnstring_new_from_cstring_cpy(path);
    return par;
}

void mnsqlite_params_free(mnsqlite_params *params)
{
    mnstring_free(&params->pass);
    mnstring_free(&params->path);
    mnstring_free(&params->user);
    free(params);
}

mnsqlite *mnsqlite_new(mnsqlite_params* params)
{
    mnsqlite* database= malloc(sizeof (mnsqlite));

    sqlite3* db;
    int res = sqlite3_open(params->path->string,&db);
    if(res!=MN_OK){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        free(database);
        return 0;
    }
    database->sqlite_db =db;
    database->sqlite_params=mnsqlite_params_clone(params);
    return database;
}



char mnsqlite_free(mnsqlite* database)
{
    mnsqlite_params_free(database->sqlite_params);
    database->sqlite_params=0;
    int res =sqlite3_close(database->sqlite_db);
    database->sqlite_db=0;
    free(database);
    database=0;

    if(res==SQLITE_OK) return 1;
    else return 0;

}


char mnsqlite_db_exec(mnsqlite* database,const char* sql){
    char *err_msg = 0;
    sqlite3* db=database->sqlite_db;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }
    sqlite3_free(err_msg);
    return 1;
}

int mnsqlite_last_insert_id(mnsqlite* database){
    sqlite3* db=database->sqlite_db;
    return  sqlite3_last_insert_rowid(db);
}

mnrecord* mnsqlite_first_record(mnsqlite* database,const char* sql){
    mnrecord* record= mnrecord_new_v0();
    sqlite3_stmt* stmt;
    const char* tail ;
    sqlite3* db=database->sqlite_db;

    int res=sqlite3_prepare_v2(db,sql,-1,&stmt,&tail);
    if(res!=SQLITE_OK){
        //recordset=0;
        return 0 ;
    }
    int col_count=sqlite3_column_count(stmt);
    if (sqlite3_step(stmt)==SQLITE_ROW) {
        for(int i=0;i<col_count;i++){

            if(sqlite3_column_type(stmt,i)==SQLITE_INTEGER){
                mnfield* field=mnfield_new_int((char*)sqlite3_column_name(stmt,i),sqlite3_column_int(stmt,i));
                mnrecord_add_field_byref(record,field);
                continue;
            }else if(sqlite3_column_type(stmt,i)==SQLITE_TEXT){
                mnfield* field=mnfield_new_cloned_cstring((char*)sqlite3_column_name(stmt,i),
                                                   (char*)sqlite3_column_text(stmt,i));
                mnrecord_add_field_byref(record,field);
                continue;
            }else if(sqlite3_column_type(stmt,i)==SQLITE_FLOAT){
                mnfield* field=mnfield_new_double((char*)sqlite3_column_name(stmt,i),sqlite3_column_double(stmt,i));
                mnrecord_add_field_byref(record,field);
                continue;
            }
        }
    }
    sqlite3_finalize(stmt);
    return record;
}



mnrecordset *mnsqlite_get_data(mnsqlite *database, const char *sql)
{    
    mnrecordset* recordset= mnrecordset_new();
    mnsqlite_add_data_to_recordset(recordset,database,sql);
    return recordset;
}

void mnsqlite_add_data_to_recordset(mnrecordset* recordset,mnsqlite* database, const char *sql){

    sqlite3_stmt* stmt;
    const char* tail ;
    sqlite3* db=database->sqlite_db;

    int res=sqlite3_prepare_v2(db,sql,-1,&stmt,&tail);
    if(res!=SQLITE_OK){
        return  ;
    }
    int col_count=sqlite3_column_count(stmt);
    while(sqlite3_step(stmt)==SQLITE_ROW){
        mnrecord* record= mnrecord_new_v0();
        for(int i=0;i<col_count;i++){

            if(sqlite3_column_type(stmt,i)==SQLITE_INTEGER){
                mnfield* field=mnfield_new_int((char*)sqlite3_column_name(stmt,i),sqlite3_column_int(stmt,i));
                mnrecord_add_field_byref(record,field);
                continue;
            }else if(sqlite3_column_type(stmt,i)==SQLITE_TEXT){
                mnfield* field=mnfield_new_cloned_cstring((char*)sqlite3_column_name(stmt,i),
                                                   (char*)sqlite3_column_text(stmt,i));
                mnrecord_add_field_byref(record,field);
                continue;
            }else if(sqlite3_column_type(stmt,i)==SQLITE_FLOAT){
                mnfield* field=mnfield_new_double((char*)sqlite3_column_name(stmt,i),sqlite3_column_double(stmt,i));
                mnrecord_add_field_byref(record,field);
                continue;
            }
        }
        mnrecordset_add_ref(recordset,record);
    }
    sqlite3_finalize(stmt);
}


mnsqlite_params *mnsqlite_params_clone(mnsqlite_params *params)
{
    mnsqlite_params* par=mnsqlite_params_new(params->path->string,
                                             params->user->string,
                                             params->pass->string);
    return par;
}


/*
 * mnsqlite
 *
 *  Created on: ٠٣‏/٠٥‏/٢٠٢١
 *      Author: merhab
 */


mndatabase *mndatabase_new(db_drivers driver, void *connection_params,const char *name)
{
    mndatabase* database=malloc(sizeof (mndatabase));
    if (name) {
        database->name=mnstring_new_from_cstring_cpy(name);
    }else{
        database->name=mnstring_new_from_cstring_cpy(DEFAULT_SQLITE_DB);
    }

    if(driver== SQLITE){
        database->connection=mnsqlite_new(connection_params);
    }else if (driver==MYSQL) {

    }else{

    }
    database->driver=driver;
    return database;


}

void mndatabase_free(mndatabase* database){
    if(database->driver== SQLITE){
        mnsqlite_free(database->connection);
    }else if (database->driver==MYSQL) {

    }else{

    }
}


char mndatabase_is_valid(mndatabase *self)
{
    if (self->connection) return 1;
    return 0;
}

char mndatabase_exec(mndatabase *self, mnstring *sql)
{
    switch (self->driver) {
    case SQLITE:
        return mnsqlite_db_exec((mnsqlite*)self->connection,sql->string);
        break;
    case MYSQL:
        break;
    }
    return 1;
}

mnrecordset *mndatabase_get_data(mndatabase *self, const char *sql)
{
    mnrecordset* recordset=mnrecordset_new();
    mndatabase_add_data_to_recordset(recordset,self,sql);
    return recordset;
}

void mndatabase_add_data_to_recordset(mnrecordset* recordset,mndatabase* self, const char* sql){
    switch (self->driver) {
    case SQLITE:
        mnsqlite_add_data_to_recordset(recordset,(mnsqlite*)self->connection,sql);
        break;
    case MYSQL:
        return ;
        break;
    }

}

//TODO:test mndatabase_bind_params_and_exec
static char mndatabase_bind_params_and_exec(mndatabase *db, mnrecord *record,mnstring* sql){
    if (db->driver==SQLITE) {
        sqlite3* sqlitedb=((mnsqlite*)db->connection)->sqlite_db;
        sqlite3_stmt* rds;
        const char* tail;
        int res;
        res=sqlite3_prepare_v2(sqlitedb,sql->string,-1,&rds,&tail);
        if(!(res==MN_OK)){
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(sqlitedb));
            sqlite3_finalize(rds);
            return 0;
        }
        int j=1;
        for(TLint i=0;i<mnrecord_count(record);i++){
            mnfield* field=mnrecord_field_byind_ref(record,i);
            if(!TField_is_generated(field)){
                continue;
            }
            int val;
            const char* text;
            switch (TField_type(field)) {
            case CString:
                text =((char*) mnfield_cstring_val_cpy(field));
                sqlite3_bind_text(rds,j,text,-1,0);
                break;
            case Int:
                val=(mnfield_int_val(field));
                sqlite3_bind_int(rds,j,val);
                break;
            case Double:
                sqlite3_bind_double(rds,j,mnfield_double_val(field));
                break;

             default:
                assert(0);
                break;
            }
            j++;
        }
        res= sqlite3_step(rds);
        if(res==MN_DONE){
            sqlite3_finalize(rds);
            mnfield_setval_int(mnrecord_field_byind_ref(record,0),sqlite3_last_insert_rowid(sqlitedb));
            return sqlite3_last_insert_rowid(sqlitedb);
        }
        sqlite3_finalize(rds);
        return 0;

    }else if (db->driver==MYSQL) {

    }else {

    }
    return 1;
}

//TODO: test mndatabase_last_insert_id
int mndatabase_last_insert_id(mndatabase* db){
    if (db->driver==SQLITE) {
        mnsqlite* sqlitedb=((mnsqlite*)db->connection);
        return mnsqlite_last_insert_id(sqlitedb);
    }
    return -1;
}

mnrecord* mndatabase_first_record(mndatabase* db,const char* sql){
    if (db->driver==SQLITE) {
        mnsqlite* sqlitedb=((mnsqlite*)db->connection);
        return mnsqlite_first_record(sqlitedb,sql);
    }
    return 0;
}

//TODO: mndatabase_insert_record
char mndatabase_insert_record(mndatabase *db, mnrecord *record,const char *table_name)
{
    mnstring* sql=mnstring_new_from_cstring_ref(
                mnrecord_sql_insert_with_params(record,table_name));
    char ret= mndatabase_bind_params_and_exec(db,record,sql);
    if (!ret) {
        return ret;
    }
    int last_id =mndatabase_last_insert_id(db);
    //mninteger l_id=mninteger_new_v2(last_id);
    mnrecord_set_field_val_by_name(record,RECORD_ID,TDataInt_new_init(last_id));
    mnstring_free(&sql);
    return ret;
}

//TODO: test mndatabase_update_record
char mndatabase_update_record(mndatabase *db, mnrecord *record, const char *table_name)
{
    mnstring* where_sql =mnstring_new_concat_multi("WHERE ID=%d",
                                                   mnfield_int_val(mnrecord_field_byname_ref(record,"ID")));
    mnstring* sql=mnstring_new_from_cstring_ref(mnrecord_sql_update_with_params(record,table_name,where_sql->string));
    char ret=mndatabase_bind_params_and_exec(db,record,sql);
    mnstring_free(&where_sql);
    mnstring_free(&sql);
    return ret;

}

/*
 *
 * SQL_TABLE
 *
 */
mnrecord *mndatabase_login_info_record_new()
{
    mnrecord* record =mnrecord_new();
    mnrecord_add_field_byref(record,mnfield_new_cloned_cstring("name",""));
    mnrecord_add_field_byref(record,mnfield_new_cloned_cstring("user",""));
    mnrecord_add_field_byref(record,mnfield_new_cloned_cstring("password",""));
    mnrecord_add_field_byref(record,mnfield_new_cloned_cstring("full_path",""));
    return record;
}
