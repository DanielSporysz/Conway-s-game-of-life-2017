//
// Created by szmurlor on 25.01.17.
//

#ifndef SPLINES_SPLINES_H_H
#define SPLINES_SPLINES_H_H

#include "points.h"
#include "gaus/piv_ge_solver.h"

#include <stdlib.h>

typedef struct {
    int nbase;
    double *c;
    double *x;
} spline_t;

spline_t * splines_approximate(points_t *points, int nbase);
double splines_eval(spline_t * spline, double x);

void free_spline(spline_t * spline);


#endif //SPLINES_SPLINES_H_H
