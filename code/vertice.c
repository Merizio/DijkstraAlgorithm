#include "vertice.h"
#include "warden.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct no{
    int id;
    char* nome;
    No* pai; //REFERENCIA AO PAI COM O INDICE OU COM NO*
    float dist_s;
    bool finalizado;
    Warden* conex;
};

No* criarNo(int id){
    No* n = malloc(sizeof(No));
    n->pai=NULL;
    n->dist_s=INFINITY;
    n->id=id;
    n->nome=NULL;
    n->conex=criarConexao();
    n->finalizado=false;
    return n;
}

void addNomeNo(No* no, char* nome){
    no->nome=strdup(nome);
}

void imprimirNo(No* no){
    printf("%d: %s\tDist para S:%.2f\n", no->id, no->nome, no->dist_s);
    //printf("%s ", no->nome);
    //imprimeWarden(no->conex);
    //printf("\n");
}

void liberarNo(No* no){
    free(no->nome);
    liberaWarden(no->conex);
    free(no);
}

void adicionarConexao(No* no, void* conex, float peso){
    adicionarElemento(no->conex, conex, peso);
}

void atualizaDistancia(No* no, float dist){
    no->dist_s=dist;
}

float retornaDistanciaS(No* no){
    return no->dist_s;
}

int retornaIdNo(No* no){
    return no->id;
}

void atualizaId(No* no, int id){
    no->id=id;
}

static void atualizaPai(No* no, No* pai){
    no->pai=pai;
}

No* retornaPaiNo(No* no){
    return no->pai;
}

char* retornaNomeNo(No* no){
    return no->nome;
}

float relaxeNo(No* n1, No* n2, float d_1to2){
    int n = rand();
    if(n%2==0){
        if((retornaDistanciaS(n1)+d_1to2)<retornaDistanciaS(n2)){
            atualizaPai(n2, n1);
            return retornaDistanciaS(n1)+d_1to2;
        }
    }else{
        if((retornaDistanciaS(n1)+d_1to2)<=retornaDistanciaS(n2)){
            atualizaPai(n2, n1);
            return retornaDistanciaS(n1)+d_1to2;
        }
    }

    return 0.0;
}

Warden* retornaWarden(No* no){
    return no->conex;
}

void finalizarNo(No* no){
    no->finalizado=true;
}

bool estadoNo(No* no){
    return no->finalizado;
}