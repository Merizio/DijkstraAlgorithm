#include "vertice.h"
#include "warden.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct no{
    char* nome;
    int pai; //REFERENCIA AO PAI COM O INDICE OU COM NO*
    float dist_s;
    Warden* conex;
};

No* criarNo(char* nome){
    No* n = malloc(sizeof(No));
    n->pai=-1;  // n->pai=NULL
    n->dist_s=INFINITY;
    n->nome=strdup(nome);
    n->conex=criarConexao();

    return n;
}

void imprimirNo(No* no){
    printf("Nó: %s\nDist para S:%.2f\n", no->nome, no->dist_s);
    imprimeWarden(no->conex);
}

void liberarNo(No* no){
    free(no->nome);
    liberaWarden(no->conex);
    free(no);
}

void adicionarConexao(No* no, int id, float peso){
    adicionarElemento(no->conex, id, peso);
}

float retornaDistanciaS(No* no){
    return no->dist_s;
}

int retornaPaiNo(No* no){
    return no->pai;
}