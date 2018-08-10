/*
 * File: test_showhistory.c
 */

int __wrap_getdata(int key, data_t *datap) {
   char *param;
/*
 * getdata() fill in the passed data struct with data
 * from the list at the key. getdata() returns:
 * -1  - when it is unable to allocate space for the string
 *  0  - on success
 */
   check_expected(key);
  // param = mock_ptr_type(int);;
//   check_expected(datap);
    //datap->string = (char *)malloc(strlen(item.string+1));
    //strcpy(datap->string, &item.string);
   //datap->t = mock_type(int);
   datap->t = key;
   param = mock_ptr_type(char *);
   datap->string = strdup(param);
   return mock_type(int);;
}

/*
 * showhistory() - example from page 37, Robbins. 
 * This is a function in the keeploglib.c
 */

static void showhistory(int *r){
   data_t data;
   int key,tmp;

   key = __wrap_accessdata();
   *r = key;
   if (key == -1){
      fprintf(stderr, "No history\n");
      return;
   }
   tmp = getdata(key,&data);
   if (tmp == 0){
       fprintf(stderr,"key: %d: %d %s|\n", key, data.t, data.string);
   } else {
       fprintf(stderr,"getdata() returns: %d. Key was: %d\n", tmp,key);
   }
//   while(!getdata(key, &data) && (data.string != NULL)) {
//      // fprintf(stderr,"Command: %s\nTime: %s\n", data.string, ctime(&(data.time));
//      fprintf(stderr,"Command: %s\nTime: %d\n", data.string, data.t);
//      free(data.string);
//   }
//   return;
}

static void test_showhistory_no_history(void **state){
   (void) state;  /* unused */
   int rv;
   will_return(__wrap_accessdata,true);
   showhistory(&rv);
   assert_int_equal(-1,rv);
}

static void test_showhistory(void **state){
    (void) state; /* unused */
    int rv;
    data_t   mydata;

    expect_value(__wrap_getdata, key, 12);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,false);
    will_return(__wrap_accessdata,12);
    will_return(__wrap_getdata, cast_ptr_to_largest_integral_type("abrakadabra"));
//    will_return(__wrap_getdata, 24);
    will_return(__wrap_getdata, 0);

    showhistory(&rv);
    assert_int_equal(12,rv);

}
