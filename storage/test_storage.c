#include <stdio.h>
#include "storage.h"

int main ( int argc, char **argv){
    data_t data = NULL;

    int i;
    printf("%s: Dodaje do bazy 444 kolejnych liczb zaczynajac od 1 dla Tb, Tw i czasu\n", argv[0]);
    for(i=0; i< 444; i++)
	data = add2storage( data, i, i, i);
    
    printf("Zawartosc bazy danych:\n");
    for(i=0; i<data->count; i++)
	printf("Tb: %lf, Tw: %lf, Time: %lf\n", data->tab[i]->Tb, data->tab[i]->Tw, data->tab[i]->time);

    clear_storage( data );

    return 0;
}
