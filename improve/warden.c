#include "warden.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct cel{
    void* conex;
    int id;
    float peso;
};

struct warden{
    Cel** array_conex;
    int total;
};

Warden* criarConexao(int sz){
    Warden* w=malloc(sizeof(Warden));
    w->array_conex=calloc(sz, sizeof(Cel*));
    w->total=sz;

    return w;
}

void adicionarElemento(Warden* w, void* conex, int id, float peso){
    Cel* c = malloc(sizeof(Cel));
    c->conex=conex;
    c->peso=peso;
    c->id=id;

    w->array_conex[id]=c;
}

void imprimeWarden(Warden* w){

    for(int i=0;i<w->total;i++){
        if(w->array_conex[i]!=NULL){
            printf("nó %d -> %.2f ", w->array_conex[i]->id, w->array_conex[i]->peso);
        }
    }
    printf("\n");
}

void liberaWarden(Warden* w){

    for(int i=0;i<w->total;i++){
        if(w->array_conex[i]!=NULL){
           free(w->array_conex[i]);
        }
    }
    free(w->array_conex);
    free(w);
}

Cel* retornaCel(Warden* w, int id){
    return w->array_conex[id];
}

float retornaDistancia(Cel* c){
    return c->peso;
}

void* retornaConex(Cel* c){
    if(c==NULL)return NULL;
    return c->conex;
}