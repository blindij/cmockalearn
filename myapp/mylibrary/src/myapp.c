#include <stdio.h>
#include "myapp.h"

double stencil_4p_2d(double north, double east, double south, double west) {
    double mean = (north+east+south+west)/4.0;
    return mean;
}
