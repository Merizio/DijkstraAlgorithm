#ifndef CONEX_H
#define CONEX_H

typedef struct cel Cel;
typedef struct warden Warden;

Warden* criarConexao(int sz);

void adicionarElemento(Warden* w, void* conex, int id, float peso);

void imprimeWarden(Warden* w);

void liberaWarden(Warden* w);

Cel* retornaCel(Warden* w, int id);

int retornaTamWarden(Warden* w);

float retornaDistancia(Cel* c);

void* retornaConex(Cel* c);

#endif