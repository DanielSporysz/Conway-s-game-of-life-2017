#include <stdio.h>
#include "approx.h"
#include "splines.h"
#include "points.h"

int main( int argc, char **argv){
    spline_t *spline = init_approx();
    
    int i; 
    double T = 20;
    for(i=0; i < 10; i++){
	printf("Dla Tw = %lf -> cw = %lf\n", T, splines_eval( spline, T));
	T += 100;
    }

    free_spline(spline);

    return 0;
}
