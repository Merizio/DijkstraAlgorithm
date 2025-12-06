#include "warden.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cel{
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

void adicionarElemento(Warden* w, int id, float peso){
    Cel* c = malloc(sizeof(Cel));
    c->id=id;
    c->peso=peso;
    c->prox=NULL;

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
        printf("nó %d -> %.2f  ", aux->id, aux->peso);
        //printf(", %.2f", aux->peso);
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

int retornaId(Cel* c){
    return c->id;
}