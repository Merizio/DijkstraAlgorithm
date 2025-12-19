#ifndef ARRAY_H
#define ARRAY_H

#include "vertice.h"

typedef struct array Array;

Array* criaArray(int tam);

No* retornaNoArray(Array* x, int pos);

void trocaPosicaoArray(Array* x, int p1, int p2);

void ordenarArray(Array* x, int lo);

int completarArray(Array* x, FILE* arq);

void liberarArray(Array* x);


#endif