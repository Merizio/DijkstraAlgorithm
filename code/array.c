/*
|   TRABALHO PRÁTICO 1 - DIJKSTRA
|   Francisco Vassoler Merizio - 2024102652
|   Rodrigo Mattioli - 2019202335
|   SEGUNDA IMPLEMENTAÇÃO
|   array.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "array.h"

struct array{
    No** array_no;
    int n;
};

//CRIA UM ARRAY DE TAMANHO tam JÁ COM TODOS OS NÓS INICIALIZADOS COM ID
Array* criaArray(int tam){
    Array* array = malloc(sizeof(Array));
    array->n=tam;
    array->array_no=malloc(sizeof(No*)*array->n);
    for(int i=0;i<array->n;i++){
        array->array_no[i]=criarNo(i);
    }

    return array;
}

//RETORNA POSIÇÃO DO ARRAY
No* retornaNoArray(Array* x, int pos){
    return x->array_no[pos];
}

//FUNÇÃO BÁSICA DE EXCH
void trocaPosicaoArray(Array* x, int p1, int p2){
    No* aux = x->array_no[p1];
    x->array_no[p1]=x->array_no[p2];
    x->array_no[p2]=aux;
}

//FUNÇÃO UTILIZADA PARA VERSÕES COM QSORT
static int comparar (const void * a1, const void * a2){
    No* n1 = *(No**)a1;
    No* n2 = *(No**)a2;

    float f1 = retornaDistanciaS(n1);
    float f2 = retornaDistanciaS(n2);
    if(f1<=f2) return -1;
    else if(f1>f2)return 1;
    return 0;
}

//FUNÇÃO DE "EXTRAIR MINIMO" PARA A VERSÃO DE ARRAY
void ordenarArray(Array* x, int lo){
    //qsort(x->array_no+lo, x->n-lo, sizeof(No*), comparar);

    //UMA ITERAÇÃO DO SELECTION SORT
    float min;
    int pos;
    for(int i=lo;i<x->n;i++){
        if(retornaDistanciaS(x->array_no[i])<min || i==lo){
            min=retornaDistanciaS(x->array_no[i]);
            pos=i;
        }
    }
    trocaPosicaoArray(x, lo, pos);
}

//LIBERA TODA A ESTRUTURA
void liberarArray(Array* x){
    for(int i=0;i<x->n;i++){
        liberarNo(x->array_no[i]);
    }
    free(x->array_no);
    free(x);
}