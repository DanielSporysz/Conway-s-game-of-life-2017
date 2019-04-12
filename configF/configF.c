#include "configF.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define perror( parameter, value,  file) fprintf(stderr, "configF module: Parameter \"%s\" is not specified in file \"%s\". Using default value of %lf.\n", parameter, file, value)

void check_parameters( parameters_t l, char *file_name ){ /* Tb Tw mb mw time_step A h cb */
    if( l->Tb == -300){
	perror("Tb", (double)1200, file_name);
	l->Tb = 1200;}
    if( l->Tw == -300){
	perror("Tw", (double)65, file_name);
        l->Tw = 65;}
    if( l->mb == -300){
	perror("mb", (double)0.2, file_name);
        l->mb = 0.2;}
    if( l->mw == -300){
	perror("mw", (double)2.5, file_name);
        l->mw = 2.5;}
    if( l->time_step == -300){
	perror("time_step", (double)0.01, file_name);
        l->time_step = 0.01;}
    if( l->A == -300){
	perror("A", (double)0.0109, file_name);
        l->A = 0.0109;}
    if( l->h == -300){
	perror("h", (double)50, file_name);
        l->h = 50;}
    if( l->cb == -300){
	perror("cb", (double)0.22, file_name);
        l->cb = 0.22;
    }
}

void load_defaults( parameters_t l){
    l->Tb = 1200.00;
    l->Tw = 65.00;
    l->mb = 0.2;
    l->mw = 2.5;
    l->A = 0.0109;
    l->h = 50;
    l->time_step = 0.01;
    l->cb = 0.22;
}

void init_parameters( parameters_t l){
    if( l != NULL){
    l->Tb = -300;
    l->Tw = -300;
    l->mb = -300;
    l->mw = -300;
    l->A = -300;
    l->h = -300;
    l->time_step = -300;
    l->cb = -300;
    }
}

parameters_t read_configuration( char *file_name ){
 
    FILE *in;
    double tmp;
    char *parameter = malloc( 256 * sizeof(char));
    parameters_t pointer = malloc( sizeof( struct _parameters_t  ));

    if( pointer == NULL)
	return pointer;

    init_parameters( pointer );

    in = fopen( file_name, "r");
    if( in == NULL){
	fprintf(stderr, "configF module: Can't Read From the File: \"%s\". Using default value of parameters.\n", file_name);
	load_defaults( pointer);
	free( parameter);
	return pointer;
    }

    while( fscanf( in, "%s %lf", parameter, &tmp) != EOF ){
	if( strcmp( parameter, "Tb") == 0){
	    pointer->Tb = tmp;
	} else if( strcmp( parameter, "Tw") == 0){
            pointer->Tw = tmp;
        } else if( strcmp( parameter, "mb") == 0){
            pointer->mb = tmp;
        } else if( strcmp( parameter, "mw") == 0){
            pointer->mw = tmp;
        } else if( strcmp( parameter, "time_step") == 0){
            pointer->time_step = tmp;
        } else if( strcmp( parameter, "h") == 0){
            pointer->h = tmp;
        } else if( strcmp( parameter, "A") == 0){
            pointer->A = tmp;
        } else if( strcmp( parameter, "cb") == 0){
            pointer->cb = tmp;
        }
	parameter[1]='A';
    }
    check_parameters( pointer, file_name );
    free( parameter );
    fclose(in);
    return pointer;
}
