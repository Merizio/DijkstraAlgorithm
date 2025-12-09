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
        int* pai = (int*) aux->conex;
        printf("nó %d -> %.2f ", *pai, aux->peso);
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

Cel* retornaCel(Warden* w, int indice){
    Cel* aux=w->prim;
    for(int i=0;i<indice;i++){
        aux=aux->prox;
        if(aux==NULL) return NULL;
    }
    return aux;
}

float retornaDistancia(Cel* c){
    return c->peso;
}

void* retornaConex(Cel* c){
    return c->conex;
}