#ifndef VERTICE_H
#define VERTICE_H

typedef struct no No;

No* criarNo(int id);

void addNomeNo(No* no, char* nome);

void imprimirNo(No* no);

void liberarNo(No* no);

void adicionarConexao(No* no, void* conex, float peso);

float retornaDistanciaS(No* no);

No* retornaPaiNo(No* no); //NO* ...


#endif