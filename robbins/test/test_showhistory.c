/*
 * File: test_showhistory.c
 */

/*
 * showhistory() - example from page 37, Robbins. 
 * This is a function in the keeploglib.c
 */

static void showhistory(int *r){
   data_t data;
   int key;

   key = __wrap_accessdata();
   if (key == -1){
      fprintf(stderr, "No history\n");
      *r = -1;
   }
//   while(!getdata(key, &data) && (data.string != NULL)) {
//      fprintf(f,
//   }
}

//int __wrap_accessdata(void){
//    bool isempty;
//    bool cannotallocate;
//    bool firsttimeaccess;
//    bool nextkeyis;
//    int tmp;
//    // check_expected_ptr( <somevariable>)
//
//    isempty = mock_type(bool);
//    if ( isempty == true) {
//        return -1;
//    }
//
//    cannotallocate = mock_type(bool);
//    if ( cannotallocate == true) {
//        return -2;
//    }
//
//    firsttimeaccess = mock_type(bool);
//    if ( firsttimeaccess == true) {
//        return 0;
//    }
//    return mock_type(int);
//}
//
//

static void test_showhistory(void **state){
   (void) state;  /* unused */
   int rv;
   will_return(__wrap_accessdata,true);
   showhistory(&rv);
   assert_int_equal(-1,rv);
}
