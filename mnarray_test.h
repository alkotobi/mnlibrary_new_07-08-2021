#ifndef MNARRAY_TEST_H
#define MNARRAY_TEST_H

#include "mnarray.h"
#include "test.h"


char TArray_new_test();
char TArray_init_test();
char TArray_add_ref_test();
char TArray_free_data_test();
char TArray_count_test();
char TArray_size_test();
char TArray_item_at_test();
char TArray_remove_item_ret_ref_test();





char TArrayData_free_data_test();
char TArrayData_add_cpy_test();
char TArrayData_add_ref_test();
char TArrayData_find_first_test();
char TArrayData_add_or_replace_test();
TData* TArrayData_migrating_test();

char mnarray_test();

#endif // MNARRAY_TEST_H
