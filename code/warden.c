/*
|   TRABALHO PRÁTICO 1 - DIJKSTRA
|   Francisco Vassoler Merizio - 2024102652
|   Rodrigo Mattioli - 2019202335
|   GERAL
|   warden.c
*/
#include "warden.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cel{
    void* conex;
    int id;
    float peso;
    Cel* prox;
};

struct warden{
    Cel* prim;
    Cel* ult;
    int total;
};

Warden* criarConexao(){
    Warden* w=malloc(sizeof(Warden));

    w->prim=w->ult=NULL;
    w->total=0;

    return w;
}

void adicionarElemento(Warden* w, void* conex, float peso){
    Cel* c = malloc(sizeof(Cel));
    c->conex=conex;
    c->peso=peso;
    c->prox=NULL;
    c->id=w->total;

    if(w->prim==NULL){
        w->prim=w->ult=c;
    }
    else{
        w->ult->prox=c;
        w->ult=c;
    }
    w->total++;
}

void imprimeWarden(Warden* w){
    Cel* aux = w->prim;
    while(aux!=NULL){
        printf("nó %d -> %.2f ", aux->id, aux->peso);
        aux=aux->prox;
    }
}

void liberaWarden(Warden* w){
    Cel* aux = w->prim;
    Cel* sec;
    while(aux!=NULL){
        sec=aux;
        aux=aux->prox;
        free(sec);
    }
    free(w);
}

Cel* retornaCel(Warden* w){
    return w->prim;
}
Cel* retornaProxCel(Cel* w){
    return w->prox;
}

float retornaDistancia(Cel* c){
    return c->peso;
}

void* retornaConex(Cel* c){
    if(c==NULL)return NULL;
    return c->conex;
}