#include "myapp.h"

static double stencil_4p_2d(double *north, double *east, double* south, double *west) {
    double mean = (*north+*east+*south+*west)/4.0;
    printf("north = %f, east = %f, south = %f, west = %f\n", *north, *east, *south, *west);
    printf("Returning %f\n", mean);
    return 5.0;
}
