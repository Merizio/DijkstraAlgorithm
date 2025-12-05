#ifndef VERTICE_H
#define VERTICE_H

typedef struct no No;

No* criarNo(char* nome);

void imprimirNo(No* no);

void liberarNo(No* no);

void adicionarConexao(No* no, int id, float peso);

float retornaDistanciaS(No* no);

int retornaPaiNo(No* no); //NO* ...


#endif