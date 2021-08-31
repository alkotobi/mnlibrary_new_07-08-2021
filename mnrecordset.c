#include "mnrecordset.h"


mnrecordset *mnrecordset_new()
{
    mnrecordset* r= TArray_init(TArray_new());
    return r;
}

void mnrecordset_add_ref(mnrecordset* rdsset, mnrecord *rds)
{
    TArray_add(rdsset,rds);
}

void mnrecordset_add_cpy(mnrecordset *rdsset, mnrecord *rds)
{
    TArray_add(rdsset,mnrecord_clone(rds));
}

mnrecord *mnrecordset_record_by_ind_ref(mnrecordset *rdsset, TLint ind)
{
    if (ind>=TArray_count(rdsset)) {
        return 0;
    }
    return (mnrecord*)TArray_item_at(rdsset,ind);
}







void mnrecordset_printf(mnrecordset *rds_set)
{
    mnrecord_printf_title(mnrecordset_record_by_ind_ref(rds_set,0));
    for (TLint i=0;i<TArray_count(rds_set) ;i++ ) {
        mnrecord* rcd= mnrecordset_record_by_ind_ref(rds_set,i);
        mnrecord_printf(rcd);
    }
}


void mnreordset_free(mnrecordset **rdset)
{
    TArray_clean(*rdset,(TFVoidPtrHld)mnrecord_free_v0);
    TArray_free($P(rdset));
}

mnrecord *mnrecordset_get_current(mnrecordset *rdset)
{
    return mnrecordset_record_by_ind_ref(rdset,TArray_index(rdset));
}

//void mnrecordset_before_scroll(mnrecordset *rds)
//{
//    //MNDOEVENT(rds,on_before_scroll);
//}

//void mnrecordset_after_scroll(mnrecordset *rds)
//{
//   // MNDOEVENT(rds,on_after_scroll);
//}
