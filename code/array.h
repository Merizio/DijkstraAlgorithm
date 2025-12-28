/*
|   TRABALHO PRÁTICO 1 - DIJKSTRA
|   Francisco Vassoler Merizio - 2024102652
|   Rodrigo Mattioli - 2019202335
|   SEGUNDA IMPLEMENTAÇÃO
|   array.h
*/
#ifndef ARRAY_H
#define ARRAY_H

#include "vertice.h"

typedef struct array Array;

Array* criaArray(int tam);

No* retornaNoArray(Array* x, int pos);

void trocaPosicaoArray(Array* x, int p1, int p2);

void ordenarArray(Array* x, int lo);

void liberarArray(Array* x);


#endif