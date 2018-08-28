#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "iolib.h"

#include "test_iolib.c"

int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_readline_null),
    };

    return cmocka_run_group_tests(tests, NULL,NULL);
}
