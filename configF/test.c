#include <stdio.h>
#include <stdlib.h>
#include "configF.h"

int main(int argc, char **argv){
    if( argc < 2){
	printf("%s: Missing file operand\n", argv[0]); 
	return 1;
    }
    parameters_t par;
    par = read_configuration( argv[1] );
    
    printf("From file \"%s\":\n", argv[1]);
    printf("Tb = \t%f\n", par->Tb);
    printf("Tw = \t%f\n", par->Tw);
    printf("mb = \t%f\n", par->mb);
    printf("mw = \t%f\n", par->mw);
    printf("A = \t%f\n", par->A);
    printf("h = \t%f\n", par->h);
    printf("cb = \t%f\n", par->cb);
    printf("time_step = %f\n", par->time_step);

    free( par );

    return 0;
}
