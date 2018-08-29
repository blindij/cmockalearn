#include <stdlib.h>
#include <stdbool.h>

#ifdef REAL_T
typedef REAL_T real_t;
#else
typedef double real_t;
#endif

//void ising_initialize_data ( real_t g, size_t N, size_t K, real_t Texp );

#define J(i,j,k) J[(i)*N*N+(j)*N+(k)]
extern real_t *restrict J;
#define S(n,t) s[(n)*T+(t)]
extern bool *s;
