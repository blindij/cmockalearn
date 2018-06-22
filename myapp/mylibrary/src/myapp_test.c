#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h"
#include <stdio.h>

/* #include "myapp.h" */
#include "myapp.h"

/*
 * test_stencil2d must be added here
 * Write it like test_add():
 * Ensure add() adds two integers correctly. 
 static void test_add(void **state) {
*         (void) state;   <-- unused
*
*            assert_int_equal(add(3, 3), 6);
*            assert_int_equal(add(3, -3), 0);
*}
*/

/*
 * stencil_4p_2d calculates the average of 
 * four floats passed as reference, typically 
 * neighbouring values, 4-point stencil
 */

static void test_stencil_4p_2d(void **state){
    (void) state;  /* is unused */
    double res = 1.0;
    double a= 4.0;
    double b = 2.0;
    double c = 6.0;
    double d = 8.0;
    res = stencil_4p_2d(a,b,c,d);
    assert_true( res == 5.0);
    double a2d[3][3] = { {1.0,2.0,3.0},{4.0,5.0,6.0},{7.0,8.0,9.0}};
    res = stencil_4p_2d(a2d[0][1],a2d[1][2],a2d[2][1],a2d[1][0] );
    assert_true(res == 5.0);
    /* assert_float_equal(stencil_4p_2d(pfa, pfb, pfc, pfd), 5.0); */
}

int main(void) {
   const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_stencil_4p_2d)
   };
   return cmocka_run_group_tests(tests, NULL, NULL);
}
