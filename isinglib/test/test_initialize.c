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

    assert_true(fabs(275.3139 - vectornormone(J,K*N*N)) < 0.0005);
    assert_true(fabs(9.742474 - vectornormtwo(J,K*N*N)) < 0.0005);
    FREE(J);
    FREE(s);
}

