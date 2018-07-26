#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "listlib.h"
#include "listuser_test_wrap.h"

/*
 * Here is a mocked listlib object. We start out with testing accessdata
 *
 * accessdata() will return:
 -1   - list is empty
 0    - allocated space, but unusde (first traversal)
 [1.. - first empty slot for a key
 *
 */

int __wrap_accessdata(void){
    bool isempty;
    bool cannotallocate;
    bool firsttimeaccess;
    bool nextkeyis;
    int tmp;
    // check_expected_ptr( <somevariable>)

    isempty = mock_type(bool);
    if ( isempty == true) {
        return -1;
    }

    cannotallocate = mock_type(bool);
    if ( cannotallocate == true) {
        return -2;
    }

    firsttimeaccess = mock_type(bool);
    if ( firsttimeaccess == true) {
        return 0;
    }
    return mock_type(int);
}

static int list_process(void){
    int rv;
    rv = accessdata();
    if ( rv < 0 ){
        fprintf(stderr, "accessdata() cannot give key:%d. Either is the list empty or the allocation of space for traversal keys has failed.\n",rv);
        return -1;
    }

    return rv;
}

static void test_accessdata_empty(void **state){
    (void) state; /* unused */
    int rv;
    will_return(__wrap_accessdata,true);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata, -5);
    rv=list_process();
    assert_int_equal(-1,rv);

}

static void test_accessdata_firsttime(void **state){
    (void) state;  /* unused */
    int rv;
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,true);
    // will_return(__wrap_accessdata,1);
    rv = list_process();
    assert_int_equal(0,rv);

}

static void test_accessdata(void **state){
    (void) state;  /* unused */
    int rv;
    /*
     *
     */
    // expect_any(accessdata, void);
    /*
     * We expect the accessdata to return 10 as the next free key
     */
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata, 12);
     /*
      * test  list process
      */
    rv = list_process();

    /*
     * We expect to receive a valid key
     */ 
    assert_int_equal(12,rv);
}


/* A test cast that does nothing and succeeds */
static void null_test_success(void **state) {
   (void) state; /* unused */
   
}

int main(void){
   const struct CMUnitTest tests[] = {
      //cmocka_unit_test(test_accessdata_empty),
      cmocka_unit_test(test_accessdata_firsttime),
      cmocka_unit_test(test_accessdata),
      //cmocka_unit_test(null_test_success),
   };

   return cmocka_run_group_tests(tests, NULL, NULL);
}
