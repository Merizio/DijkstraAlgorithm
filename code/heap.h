#ifndef HEAP_H
#define HEAP_H
#include "vertice.h"

typedef struct heap Heap;

Heap* criaHeap(int tam);

void insereHeap(Heap* h, No* no);

No* retornaNoHeap(Heap* h, int id);

No* removeHeap(Heap* h);

bool vaziaHeap(Heap* h);

int tamanhoHeap(Heap* h);

int tamanhoMaxHeap(Heap* h);

void liberaHeap(Heap* h);

void atualizaHeap(Heap* h, No* no, float dist);

void sort(Heap *h, int tam);

void hsort(Heap *vet, int tam);

#endif