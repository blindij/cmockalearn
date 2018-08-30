#define ALLOC(s) calloc ( (s),sizeof(char) )
#define FREE(s) free(s)

#include <errno.h>
#include <unistd.h>
#include <math.h>

void test_initialize(void **state){
    int i,bw,myfd,totalwritten;
    size_t nN = N;
    size_t nK = K;
    bool *s;
    totalwritten = 0;
    real_t g = 2.0;
    real_t Texp = 6.0;
    real_t T = floor(pow(10,Texp));

    s = ALLOC ( N*T * sizeof(bool) );
    real_t *J = ALLOC ( K*N*N * sizeof(real_t) );

    ising_initialize_data(g,nN,nK,Texp,J, s);

    myfd = open("tmp/initdata", O_CREAT | O_WRONLY);
    for(i=0;i<1;i++) {
        bw = write(myfd,J,K*N*N*sizeof(real_t));
        if ( bw == -1) printf("Errno: %d\n", errno);
        totalwritten += bw;
    }
    close(myfd);
    fprintf(stderr,"The VectorOneNorm: %e\n", vectornormone(J,K*N*N));
    fprintf(stderr,"The VectorTwoNorm: %e\n", vectornormtwo(J,K*N*N));
    FREE(J);
    FREE(s);
    assert_int_equal(10000,totalwritten);
}
