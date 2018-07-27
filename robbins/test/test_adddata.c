// File: test_adddata.cpp
//
// Code make a mock adddata() and calls the mocked function.
//

/*
 * Mocking adddata() from listlib.
 * adddata() takes a item data_t as argument. It returns
 *  -1 - if the malloc operation fails
 *  0 on success.
 */

int __wrap_adddata(const char *cmd){
   bool success;
   bool mallocfail;

   check_expected_ptr(cmd);

   success = mock_type(bool);
   if ( success == true) {
      return 0;
   }

   mallocfail = mock_type(bool);
   if ( mallocfail == true ) {
      return -1;
   }
}

static void test_adddata(void **state){
   (void) state;    /* unused */
   int rv;
   char *cmd;
   expect_string(__wrap_adddata, cmd, "top");
   will_return(__wrap_adddata, true);

   // Test adddata()
   rv = adddata("top");

   // We expect adddata() to succeed
   assert_int_equal(0,rv);
}
