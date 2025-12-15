#ifndef VERTICE_H
#define VERTICE_H
#include "warden.h"

typedef struct no No;

No* criarNo(int id);

void addNomeNo(No* no, char* nome);

void imprimirNo(No* no);

void liberarNo(No* no);

void adicionarConexao(No* no, void* conex, float peso);

void atualizaDistancia(No* no, float dist);

float retornaDistanciaS(No* no);

int retornaIdNo(No* no);

void atualizaId(No* no, int id);

No* retornaPaiNo(No* no); //NO* ...

Warden* retornaWarden(No* no);

char* retornaNomeNo(No* no);

float relaxeNo(No* n1, No* n2, float d_1to2);

int comparaNo(const void* n1, const void* n2);


#endif