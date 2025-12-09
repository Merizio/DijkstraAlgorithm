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
    //printf("Nó: %s\tDist para S:%.2f\n", no->nome, no->dist_s);
    printf("%s ", no->nome);
    imprimeWarden(no->conex);
    printf("\n");
}

void liberarNo(No* no){
    free(no->nome);
    liberaWarden(no->conex);
    free(no);
}

void adicionarConexao(No* no, void* conex, float peso){
    adicionarElemento(no->conex, conex, peso);
}

float retornaDistanciaS(No* no){
    return no->dist_s;
}

No* retornaPaiNo(No* no){
    return no->pai;
}