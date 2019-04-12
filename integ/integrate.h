#ifndef _INTEG_H
#define _INTEG_H

#include "../storage/storage.h"
#include "../configF/configF.h"
#include "../approx/splines.h"

void derivate( double Tb, double Tw, double *derivTb, double *derivTw, parameters_t para,  spline_t *spline);
int integrate( data_t d, double Tb, double Tw, double time, parameters_t para,  spline_t *spline );

#endif
