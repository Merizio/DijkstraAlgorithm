#ifndef CONEX_H
#define CONEX_H

typedef struct cel Cel;
typedef struct warden Warden;

Warden* criarConexao();

void adicionarElemento(Warden* w, void* conex, float peso);

void imprimeWarden(Warden* w);

void liberaWarden(Warden* w);

Cel* retornaCel(Warden* w);

Cel* retornaProxCel(Cel* w);

float retornaDistancia(Cel* c);

void* retornaConex(Cel* c);

#endif