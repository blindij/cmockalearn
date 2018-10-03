#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "ising_main.h"
#include "ising_parameters.h"
#include "iolib.h"

#include "test_iolib.c"
#include "test_initialize.c"

int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_readline_null),
        cmocka_unit_test(test_readline),
        cmocka_unit_test(test_initialize),
    };

    return cmocka_run_group_tests(tests, NULL,NULL);
}
