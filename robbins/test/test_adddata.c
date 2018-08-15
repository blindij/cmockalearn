// File: test_adddata.cpp
//
// Code make a mock adddata() and calls the mocked function.
//

// Include statements
#include <time.h>   /* provides mktime() and strptime() */

// Function under test
static int adder_process(data_t* tdata){
int rv;
//rv = __wrap_adddata(tdata);
rv = adddata(tdata);

if ( rv == -1){
    fprintf(stderr, "adddata() could not add data due missing storage space - the malloc() failed\n");
    return -1;
}
return 0;
}
/*
* Mocking adddata() from listlib.
* adddata() takes a item data_t as argument. It returns
*  -1 - if the malloc operation fails
*  0 on success.
*/

int __wrap_adddata(data_t *xdata){
bool success;
bool mallocfail;

check_expected(xdata);

    success = mock_type(bool);
    if ( success == true) {
      return 0;
   }
}

static void test_adder_process(void **state){
(void) state;    /* unused */
int rv;
data_t mydata = {
.t=10,
    .string="top",
   };

   expect_memory(__wrap_adddata, xdata, &mydata, sizeof(data_t));
   
   will_return(__wrap_adddata, true);

   // Test adddata()
   rv = adder_process(&mydata);

   // We expect adddata() to succeed
   assert_int_equal(0,rv);
}

static void test_mktime(void **state){
    (void) state;            /* unused */
    size_t strsize;      /* number of chars in timestr */
    time_t caltime1;          /* calendar time */
    time_t *ptrcaltime1 = &caltime1;
    struct tm timestruct;
    struct tm *ptr_timestruct = &timestruct;
    // struct tm timestruct_new;
    //struct tm *ptr_timestruct_new = &timestruct_new;
    struct tm *ptr_timestruct_new;
    char *timestr = "Wed Aug 15 09:44:21 2018";
    char *dateformatstr = "%a %b %d %T %Y";
    char timestr2[64];
    char *ptr_char;

    /*
     * Convert string with time data to a time struct
     */
    ptr_char = strptime(timestr, dateformatstr, ptr_timestruct);

    /*
     * Convert time struct to calendar time
     * and back again to another timestruct
     * but this it is GMT 
     */
    caltime1 = mktime(ptr_timestruct);
    ptr_timestruct_new = gmtime(ptrcaltime1);
    
    /* 
     * Convert new timestruct with GMT to another string
     */
    strsize = strftime(timestr2,64,dateformatstr,ptr_timestruct_new);

    assert_int_equal(24,strsize);
    assert_string_equal("Wed Aug 15 07:44:21 2018", timestr2);
}
