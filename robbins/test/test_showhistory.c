/*
 * File: test_showhistory.c
 */

int __wrap_getdata(int key, data_t *datap) {

/*
 * getdata() fill in the passed data struct with data
 * from the list at the key. getdata() returns:
 * -1  - when it is unable to allocate space for the string
 *  0  - on success
 */
   check_expected(key);
   check_expected(datap);

   return 0;
}

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
   while(!getdata(key, &data) && (data.string != NULL)) {
      // fprintf(stderr,"Command: %s\nTime: %s\n", data.string, ctime(&(data.time));
      fprintf(stderr,"Command: %s\nTime: %d\n", data.string, data.t);
      free(data.string);
   }
}

static void test_showhistory(void **state){
   (void) state;  /* unused */
   int rv;
   will_return(__wrap_accessdata,true);
   showhistory(&rv);
   assert_int_equal(-1,rv);
}
