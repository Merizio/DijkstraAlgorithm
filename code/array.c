#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "array.h"

struct array{
    No** array_no;
    int n;
};

Array* criaArray(int tam){
    Array* array = malloc(sizeof(Array));
    array->n=tam;
    array->array_no=malloc(sizeof(No*)*array->n);
    for(int i=0;i<array->n;i++){
        array->array_no[i]=criarNo(i);
    }

    return array;
}

No* retornaNoArray(Array* x, int pos){
    return x->array_no[pos];
}

void trocaPosicaoArray(Array* x, int p1, int p2){
    No* aux = x->array_no[p1];
    x->array_no[p1]=x->array_no[p2];
    x->array_no[p2]=aux;
}

static int comparar (const void * a1, const void * a2){
    No* n1 = *(No**)a1;
    No* n2 = *(No**)a2;

    float f1 = retornaDistanciaS(n1);
    float f2 = retornaDistanciaS(n2);
    if(f1<=f2) return -1;
    else if(f1>f2)return 1;
    return 0;
}

void ordenarArray(Array* x, int lo){
    qsort(x->array_no+lo, x->n-lo, sizeof(No*), comparar);
}

void liberarArray(Array* x){
    for(int i=0;i<x->n;i++){
        liberarNo(x->array_no[i]);
    }
    free(x->array_no);
    free(x);
}