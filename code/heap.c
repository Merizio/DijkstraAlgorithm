/*
|   TRABALHO PRÁTICO 1 - DIJKSTRA
|   Francisco Vassoler Merizio - 2024102652
|   Rodrigo Mattioli - 2019202335
|   PRIMEIRA E TERCEIRA IMPLEMENTAÇÃO
|   heap.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"

struct heap{
    No* *array; //vetor de vertices
    int atual; //tamanho atual
    int n; //tamanho maximo
};

Heap* criaHeap(int tam){
    Heap* h=malloc(sizeof * h);
    h->n=tam+1;
    h->array=malloc(sizeof(No*)*h->n);

    h->array[0]=NULL;
    for(int i=1;i<h->n;i++){
        h->array[i]=criarNo(i);
    }

    h->atual=h->n-1;

    return h;
}

static void fixup(Heap* h, int pos){
    while(pos>1 && (retornaDistanciaS(h->array[pos/2])>retornaDistanciaS(h->array[pos]))){
        No* aux = h->array[pos/2];
        h->array[pos/2]=h->array[pos];
        h->array[pos]=aux;

        atualizaId(h->array[pos/2], (pos/2));
        atualizaId(h->array[pos], pos);

        pos=pos/2;
    }
}
static void fixdown(Heap* h, int pos, int k){
    while(2*k<=pos){
        int j = 2*k;
        if(j<pos && (retornaDistanciaS(h->array[j])>retornaDistanciaS(h->array[j+1]))){
            j++;
        }

        if (retornaDistanciaS(h->array[k]) <= retornaDistanciaS(h->array[j])) {
            break;
        }
        No* aux = h->array[k];
        h->array[k]=h->array[j];
        h->array[j]=aux;
        atualizaId(h->array[k], k);
        atualizaId(h->array[j], j);

        k=j;
    }
}

void insereHeap(Heap* h, No* no){
    if(h->atual==h->n){
        printf("Erro! Heap Lotada!\n");
    }
    h->atual++;
    h->array[h->atual]=no;

    fixup(h, h->atual);
}

No* retornaNoHeap(Heap* h, int id){
    return h->array[id];
}


No* removeHeap(Heap* h){
    No* n = h->array[1];
    h->array[1]=h->array[h->atual];
    h->array[h->atual]=n;

    h->atual--;

    fixdown(h, h->atual, 1);

    return n;
}

bool vaziaHeap(Heap* h){
    if(h->atual==0)return true;
    return false;
}

int tamanhoHeap(Heap* h){
    return h->atual;
}
int tamanhoMaxHeap(Heap* h){
    return h->n;
}

void liberaHeap(Heap* h){
    for(int i=0;i<h->n;i++){
        if(h->array[i]!=NULL) liberarNo(h->array[i]);
    }
    free(h->array);
    free(h);
}

void atualizaHeap(Heap* h, No* no, float dist){
    atualizaDistancia(no, dist);
    fixup(h, retornaIdNo(no));
    //fixdown(h, id);
}

void sort(Heap *vet, int tam){
    for(int i=2;i<tam;i++){
        int j=i;
        while (j>=2){
            if(retornaDistanciaS(vet->array[j]) < retornaDistanciaS(vet->array[j-1])) break;
            No* n = vet->array[j];
            vet->array[j]=vet->array[j-1];
            vet->array[j-1]=n;
            j--;
        }       
    }
}

void hsort(Heap *vet, int tam) {
    int N = tam;
    for (int i = 0; i <= tam; i++)
        fixup(vet, i); // "Top-down" heap construction.
    while (N > 1) { // Sort down.
        No* temp = vet->array[1];
        vet->array[1] = vet->array[N];
        vet->array[N] = temp;

        fixdown(vet, --N, 1);
    }
}