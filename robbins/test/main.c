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

#include "test_accessdata.c"
#include "test_adddata.c"
#include "test_showhistory.c"

/* A test cast that does nothing and succeeds */
static void null_test_success(void **state) {
   (void) state; /* unused */
   
}

int main(void){
   const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_accessdata_empty),
      cmocka_unit_test(test_accessdata_firsttime),
      cmocka_unit_test(test_adder_process),
      cmocka_unit_test(test_showhistory),
      //cmocka_unit_test(null_test_success),
   };

   return cmocka_run_group_tests(tests, NULL, NULL);
}
