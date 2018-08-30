#define _XOPEN_SOURCE 500
#include "ising_main.h"
#include "ising_parameters.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


#include <errno.h>
#include <unistd.h>


void seed_uint64 ( uint64_t seed );
uint64_t random_uint64 ( void );
real_t random_uniform_real ( void );
real_t random_normal_real ( void );


int readline(int fd, char *buf, int nbytes) {
    int numread = -1;
    int returnvalue;

    while (numread < nbytes - 1) {
        returnvalue = read(fd, buf + numread, 1);
        if ((returnvalue == -1) && (errno == EINTR))
            continue;
        if ((returnvalue == 0) && (numread == 0))
            return 0;
        if (returnvalue == 0)
            break;
        if (returnvalue == -1)
            return -1;
        numread++;
        if (buf[numread-1] == '\n') {
            buf[numread] = '\0';
            return numread;
        }
    }
    errno = EINVAL;
    return - 1;
}
                
                            
void ising_initialize_data ( real_t g, size_t myN, size_t myK, real_t Texp, real_t *J ,bool *s) {
    seed_uint64 (1);
    size_t T = floor ( pow ( 10, Texp ) );
    real_t sigma = g / sqrt ( myN * myK );
    for ( size_t i=0; i<K; i++ )
        for ( size_t j=0; j<myN; j++ )
            for ( size_t k=0; k<myN; k++ )
                J[(i)*N*N+(j)*N+(k)] = random_normal_real() * sigma;
                //J(i,j,k) = random_normal_real() * sigma;
    #define Sot(i,j) sot[(i)*N+(j)]
    int8_t *sot = malloc ( myK*myN * sizeof(int8_t) );
    for ( size_t i=0; i<myK; i++ )
        for ( size_t j=0; j<myN; j++ )
            Sot(i,j) = (random_uniform_real()<0.5) ? 1 : -1;

    real_t *H = malloc ( myN * sizeof(real_t) );
    for ( size_t i=0; i<T; i++ )
    {
        memset ( H, 0, myN * sizeof(real_t) );
        for ( size_t k=0; k<myK; k++ )
            for ( size_t y=0; y<myN; y++ )
                for ( size_t x=0; x<myN; x++ )
                    H[y] += J[(k)*N*N+(y)*N+(x)] * Sot(k,x);
        // Sot[1:,:] = Sot[:-1,:]
        for ( size_t k=myK-1; k>0; k-- )
            for ( size_t y=0; y<myN; y++ )
                Sot(k,y) = Sot(k-1,y);

        for ( size_t x=0; x<myN; x++ )
            Sot(0,x) = -1 + 2 * (( random_uniform_real() <
                (exp(H[x])/(2.0*cosh(H[x]))) ) ? 1:0);
        for ( size_t x=0; x<myN; x++ )
            s[(x)*T+(i)] = (Sot(0,x) > 0);
            //S(x,i) = (Sot(0,x) > 0);
    }
    free ( H );
    free ( sot );
}


static uint64_t rseed = 0;
void seed_uint64 ( uint64_t seed ) {
    rseed = seed;
}
uint64_t random_uint64 ( void )
{
    rseed ^= rseed >> 12; // a
    rseed ^= rseed << 25; // b
    rseed ^= rseed >> 27; // c
    return rseed * UINT64_C(2685821657736338717);
}

real_t random_uniform_real ( void )
{
    return (real_t)random_uint64() / (real_t) UINT64_MAX;
}

real_t random_normal_real ( void )
{
    /* Return one half of the Box-Muller transform */
    real_t u1, u2;
    u1 = random_uniform_real();
    u2 = random_uniform_real();
    return sqrt ( -2.0 * log(u1) ) * cos ( 2*M_PI*(real_t)u2 );
}

real_t vectornormone(real_t *J, size_t size){
    real_t result;
    int i;
    result = 0.0;
    for(i=0;i<size;i++)
        result += fabs(J[i]);
    return result;
}

real_t vectornormtwo(real_t *J, size_t length){
    real_t result,tmp;
    int i;
    result= 0.0;
    for(i=0;i<length;i++)
        result += pow(fabs(J[i]),2.0);
    return sqrt(result);
}
