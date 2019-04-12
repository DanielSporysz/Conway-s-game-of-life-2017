#ifndef _STORAGE_H
#define _STORAGE_H

typedef struct temperatures{
    double Tb;
    double Tw;
    double time;
} *temperatures_t;

typedef struct data{
    temperatures_t *tab;
    int size;
    int count;
} *data_t;

void make_storage_bigger( data_t d);
data_t add2storage( data_t d, double Tb, double Tw, double time);
data_t init_storage( void );
double get_lastTb( data_t d);
double get_lastTw( data_t d);
double get_lastTime( data_t d);
void clear_storage( data_t d);

#endif
