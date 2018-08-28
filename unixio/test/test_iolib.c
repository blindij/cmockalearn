#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

 // int readline(int fd, char *buf, int nbytes);
/*
 * A test case which does nothing and succeeds
 */
 static void test_readline_null(void **state) {
    (void) state;  /* unused */
 }

 static void test_readline(void **state) {
    (void) state; /* unused */
    int bytesread, myfd;
    char mybuf[100];

    myfd = open("tmp/nintynine.txt", O_RDONLY);
    bytesread = readline(myfd, mybuf, sizeof(mybuf));
    close(myfd);
    assert_int_equal(72,bytesread);
 }
