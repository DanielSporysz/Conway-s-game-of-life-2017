#include<stdio.h>
#include<stdlib.h>
#include "chart.h"

void fprintf_data(data_t data, FILE* fout){
    if( fout == NULL ){
	fprintf( stderr, "chart.c: Recived bad pointer to file!\n");
	exit(1);
    }
    if( data == NULL ){
	fprintf( stderr, "chart.c: Recived bad pointer to structure data_t!\n");
	exit(1);
    }
    int i;
    for( i=0; i < data->count; i++)
	fprintf( fout ,"%g %g %g\n", data->tab[i]->time, data->tab[i]->Tb, data->tab[i]->Tw );
}
