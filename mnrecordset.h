#ifndef MNRECORDSET_H
#define MNRECORDSET_H
#include "mnrecord.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef TArray mnrecordset;
mnrecordset* mnrecordset_new();
void mnreordset_free(mnrecordset** rdset);
void mnrecordset_add_ref(mnrecordset *rdsset, mnrecord* rds);
void mnrecordset_add_cpy(mnrecordset*rdsset,mnrecord* rds);
mnrecord* mnrecordset_record_by_ind_ref(mnrecordset* rdsset, TLint ind);
void mnrecordset_printf(mnrecordset* rds_set);
mnrecord* mnrecordset_get_current(mnrecordset* rdset);
void mnrecordset_before_scroll(mnrecordset* rds);
void mnrecordset_after_scroll(mnrecordset* rds);


#ifdef __cplusplus
}
#endif


#endif // MNRECORDSET_H
