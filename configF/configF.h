#ifndef CONFIGF_H_
#define CONFIGF_H_

typedef struct _parameters_t{
    double Tb;
    double Tw;
    double mb;
    double mw;
    double time_step;
    double h;
    double A;
    double cb;
} *parameters_t;

parameters_t read_configuration( char *file_name);

#endif
