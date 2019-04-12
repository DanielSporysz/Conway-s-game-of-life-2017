#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./storage/storage.h"
#include "./configF/configF.h"
#include "./integ/integrate.h"
#include "./approx/splines.h"
#include "./approx/approx.h"
#include "./chart/chart.h"

#define PRECISION 0.01 /* uzywane przy szukaniu masy chlodziwa */

void simulate( data_t data, parameters_t par, spline_t *spline){
    double time = par->time_step;
    while( get_lastTb( data ) - get_lastTw( data ) - 1 > 0 ){
	integrate( data, get_lastTb( data ), get_lastTw( data ), time, par, spline);
	time += par->time_step;
    }
}

int main ( int argc, char **argv){
    if ( argc < 2 ){
	fprintf( stdout, "%s: Run program with arguments 'chart' or 'find'\n", argv[0]);
	return 1;
    }

    parameters_t par = read_configuration( "parameters.txt" );
    data_t data = NULL;
    spline_t *spline = init_approx();

    if( strcmp( argv[1], "chart" ) == 0){
	data = add2storage( data, par->Tb, par->Tw, 0);
	simulate( data, par, spline);
	FILE *fout;
	if( (fout = fopen( "Cooling.pt", "w")) == NULL){
	    fprintf(stderr, "%s: Can't write to file \'%s\'!\n", argv[0], "Cooling.pt");
	    goto free;
	}
	fprintf_data( data, fout);
	fclose( fout );
	system("gnuplot gnu_command.bat");
    } else if( strcmp( argv[1], "find") == 0){
	double coolTb = argc > 2 ? atof( argv[2]) : 200;
	double coolTime = argc > 3 ? atof( argv[3]) : 0.4;
	if( par->Tb < coolTb){
	    fprintf(stdout, "Can't cool bar from %g to %g!\n", par->Tb, coolTb);
	    goto free;
	}
	par->mw = PRECISION;
	while( get_lastTime( data ) <= coolTime && get_lastTb(data) < coolTb-2 || get_lastTb(data) > coolTb+2){
	    clear_storage( data );
	    data = NULL;
	    data = add2storage( data, par->Tb, par->Tw, 0);
	    simulate( data, par, spline);
	    par->mw += PRECISION;
	}
    fprintf( stdout, "To cool a bar from %g degrees down to %g in %gs, you'll need %gKg of oil.\n", par->Tb, coolTb, coolTime, par->mw);
    FILE *fout;
        if( (fout = fopen( "Cooling.pt", "w")) == NULL){
            fprintf(stderr, "%s: Can't write to file \'%s\'!\n", argv[0], "Cooling.pt");
            return 1;
        }
        fprintf_data( data, fout);
        fclose( fout );
        system("gnuplot gnu_command.bat");
    } else {
	fprintf(stdout, "Wrong command '%s'! Try using 'chart' or 'find' command.\n", argv[1]);
    }

    free:
    free( par );
    clear_storage( data );
    free_spline( spline );
    return 0;
}
