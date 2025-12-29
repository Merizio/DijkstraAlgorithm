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

//CRIAR LISTA ENCADEADA DE CONEXÕES
Warden* criarConexao(){
    Warden* w=malloc(sizeof(Warden));

    w->prim=w->ult=NULL;
    w->total=0;

    return w;
}

//ADICIONAR UM NÓ NA LISTA DE CONEXÕES
void adicionarElemento(Warden* w, void* conex, float peso){
    //CRIAR A CELULA DO NÓ
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

//IMPRIMIR A LISTA DE CONEXÕES (DEBUG)
void imprimeWarden(Warden* w){
    Cel* aux = w->prim;
    while(aux!=NULL){
        printf("nó %d -> %.2f ", aux->id, aux->peso);
        aux=aux->prox;
    }
}

//LIBERAR A LISTA DE CONEXÕES SEM LIBERAR OS NÓS
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

//RETORNA O PRIMEIRO NÓ DA LISTA ENCADEADA
Cel* retornaCel(Warden* w){
    return w->prim;
}
//RETORNA OS PRÓXIMOS NÓS RESPECTIVOS
Cel* retornaProxCel(Cel* w){
    return w->prox;
}

//RETORNA A DISTANCIA DE UM NÓ A PARA UM NÓ B
float retornaDistancia(Cel* c){
    return c->peso;
}

//RETORNA O NÓ CONTIDO NA CÉLULA
void* retornaConex(Cel* c){
    if(c==NULL)return NULL;
    return c->conex;
}