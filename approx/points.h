#ifndef POINTS_H
#define POINTS_H

#include <stdio.h>

typedef struct {
		int n;
		double *x;
		double *y;
} points_t;

int read_points_failed ( FILE* inf, points_t *pts);
double points_min_x(points_t *points);
double points_max_x(points_t *points);
points_t * points_linspace(double a, double b, int n);
void free_points( points_t pts);

#endif
