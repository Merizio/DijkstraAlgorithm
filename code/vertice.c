/*
|   TRABALHO PRÁTICO 1 - DIJKSTRA
|   Francisco Vassoler Merizio - 2024102652
|   Rodrigo Mattioli - 2019202335
|   GERAL
|   vertice.c
*/
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
    No* pai;
    float dist_s;
    bool finalizado;
    Warden* conex;
};

//CRIAR NÓ COM ID, SEM NOME
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

//ADD O NOME PARA O NÓ POSTERIORMENTE
void addNomeNo(No* no, char* nome){
    no->nome=strdup(nome);
}

//IMPRIME INFORMAÇÕES DO NÓ (DEBUG)
void imprimirNo(No* no){
    printf("%d: %s\tDist para S:%.2f\n", no->id, no->nome, no->dist_s);
    //printf("%s ", no->nome);
    //imprimeWarden(no->conex);
    //printf("\n");
}

//LIBERA A ESTRUTURA E AS SUAS CONEXÕES
void liberarNo(No* no){
    if(no->nome!=NULL)free(no->nome);
    liberaWarden(no->conex);
    free(no);
}

//ADD CONEXÃO A LISTA DE CONEXÕES
void adicionarConexao(No* no, void* conex, float peso){
    adicionarElemento(no->conex, conex, peso);
}

//ATUALIZA DISTANCIA DO NÓ PARA S COM UMA NOVA DISTANCIA
void atualizaDistancia(No* no, float dist){
    no->dist_s=dist;
}

//RETORNA DISTANCIA DO NÓ PARA O NODE_S
float retornaDistanciaS(No* no){
    return no->dist_s;
}

//RETORNA O ID DO NÓ
int retornaIdNo(No* no){
    return no->id;
}

//ALTERA O ID DO NÓ (POSIÇÃO NO ARRAY)
void atualizaId(No* no, int id){
    no->id=id;
}

//ALTERA A REFERÊNCIA DO PAI DE UM NÓ
static void atualizaPai(No* no, No* pai){
    no->pai=pai;
}

//RETORNA O PAI DO NÓ
No* retornaPaiNo(No* no){
    return no->pai;
}

//RETORNA O NOME DO NÓ
char* retornaNomeNo(No* no){
    return no->nome;
}

//FUNÇÃO DE RELAXAMENTO PARA DIJKSTRA
float relaxeNo(No* n1, No* n2, float d_1to2){
    //PARA POSSIBILIDADE DE DIFERENTES CAMINHOS PARA UM MESMO CAMINHO MÍNIMO
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

//RETORNA A LISTA DE CONEXÕES
Warden* retornaWarden(No* no){
    return no->conex;
}

//SINALIZAR QUE UM NÓ JÁ FOI TERMINADO NO ALGORITMO
void finalizarNo(No* no){
    no->finalizado=true;
}

// RETORNA O STATUS DE FINALIZAÇÃO DO NÓ
bool estadoNo(No* no){
    return no->finalizado;
}