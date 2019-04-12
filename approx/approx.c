#include <stdio.h>
#include <stdlib.h>
#include "approx.h"
#include "points.h"
#include "splines.h"

spline_t *init_approx( void ){
    points_t points;
    points.n = 0;
    spline_t *spline;
    FILE *fpoints = fopen( "points.pt", "r");
    if( fpoints == NULL ){
	printf("PLIK SIE ASDASDASD \n");
	exit(1);
    }
    if( read_points_failed(fpoints, &points)){
	fprintf(stderr, "Init_approx: Can't read configuration file for cw chart!\n");
	exit(1);
    }
    fclose(fpoints);
    spline = splines_approximate( &points, 21);
    if( spline == NULL )
	exit(1);

    free_points( points);
    return spline;
}
