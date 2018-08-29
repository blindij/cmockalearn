#define ALLOC(s) calloc ( (s),sizeof(char) )
#define FREE(s) free(s)
void test_initialize(void **state){
    size_t nN = N;
    size_t nK = K;
    bool *s;
    real_t g = 2.0;
    real_t Texp = 6.0;
    real_t T = floor(pow(10,Texp));

    s = ALLOC ( N*T * sizeof(bool) );
    real_t *J = ALLOC ( K*N*N * sizeof(real_t) );

    ising_initialize_data(g,nN,nK,Texp,J, s);
    FREE(J);
    FREE(s);
}
