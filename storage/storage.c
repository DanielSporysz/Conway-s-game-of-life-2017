#include <stdlib.h>
#include <stdio.h>
#include "storage.h"
#include <math.h>

#define DEFAULT_SIZE 4

data_t init_storage( void ){
    data_t d = malloc( sizeof( struct data ));
    d->tab = malloc( DEFAULT_SIZE * sizeof( temperatures_t ));
    if( d == NULL || d->tab == NULL ){
	fprintf(stderr, "init_storage: Memory allocation error at inizalizing data\n");
	exit(1);
    }
    d->size = DEFAULT_SIZE;
    d->count = 0;
    return d;
}

void make_storage_bigger( data_t d ){
    d->tab = realloc( d->tab, 2 * d->size * sizeof( struct temperatures ));
    if( d->tab == NULL){
	fprintf(stderr, "make_storage_bigger: Out of memory!\n");
	exit(1);
    }
    d->size*=2;
}

data_t add2storage( data_t d, double Tb, double Tw, double time){
    if( d == NULL )
	d = init_storage();
    if( d->count == d->size )
	make_storage_bigger( d );

    d->tab[ d->count ] = malloc( sizeof( struct temperatures ));
    if( d->tab == NULL){
	fprintf(stderr, "add2storage: Out of memory!\n");
	exit(1);
    }
    d->tab[ d->count ]->Tb = Tb;
    d->tab[ d->count ]->Tw = Tw;
    d->tab[ d->count ]->time = time;
    d->count++;

    return d;
}

double get_lastTb( data_t d){
    if( d == NULL)
	return INFINITY;
    return d->tab[ d->count - 1 ]->Tb;
}

double get_lastTw( data_t d){
    if( d == NULL)
	return INFINITY;
    return d->tab[ d->count - 1 ]->Tw;
}
double get_lastTime( data_t d){
    if( d == NULL)
	return INFINITY;
    return d->tab[ d->count - 1 ]->time;
}

void clear_storage( data_t d){
    if( d == NULL)
	return;
    int i;
    for(i=0; i<d->count; i++)
	free( d->tab[i] );
    free( d->tab );
    free( d );
}
