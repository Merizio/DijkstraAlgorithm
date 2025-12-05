#ifndef CONEX_H
#define CONEX_H

typedef struct cel Cel;
typedef struct warden Warden;

Warden* criarConexao();

void adicionarElemento(Warden* w, int id, float peso);

void imprimeWarden(Warden* w);

void liberaWarden(Warden* w);

Cel* retornaCel(Warden* w, int indice);

float retornaDistancia(Cel* c);

int retornaId(Cel* c);


#endif