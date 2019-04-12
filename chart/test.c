#include "../storage/storage.h"
#include "chart.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv){
	temperatures_t temp = malloc(sizeof(temp));
	temp->Tb = 2.3;
	temp->Tw = 0;
	temp->time = 5.6;
	temperatures_t temp2 = malloc(sizeof(temp2));
	temp2->Tb = 0;
	temp2->Tw = 9.8;
	temp2->time = 4.7;

	temperatures_t* tab = malloc( 10 * sizeof *tab);
	tab[0] = temp;
	tab[1] = temp2;
	data_t storage = malloc(sizeof(storage));
	storage->tab = tab;
	storage->size = 10;
	storage->count = 2;

	FILE* fileTw = argc>1 ? fopen(argv[1],"w"):stdout;
	
	fprintf_data(storage,fileTw);
	
	free(temp);
	free(temp2);
	free(tab);
	free(storage);
return 0;
}
