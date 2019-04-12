#include <stdio.h>
#include <stdlib.h>
#include "../configF/configF.h"
#include "../storage/storage.h"
#include "../approx/splines.h"

void derivate( double Tb, double Tw, double *derivTb, double *derivTw, parameters_t para, spline_t *spline ){
    *derivTb = ( Tw - Tb ) * para->h * para->A / ( para->mb * para->cb );
    *derivTw = ( Tb - Tw ) * para->h * para->A / ( para->mw * splines_eval( spline, Tw ) );
}

int integrate( data_t d, double Tb, double Tw, double time, parameters_t para, spline_t *spline ){

    double derivTb, derivTw;
    derivate(Tb, Tw, &derivTb, &derivTw, para, spline);

    d = add2storage( d, Tb + para->time_step * derivTb, Tw + para->time_step * derivTw, time );
    if( d == NULL )
	fprintf(stderr, "Error while adding data to database in funcion integrate!\n");
    return 0;
}
