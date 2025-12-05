#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "vertice.h"

int main(int argc, char* argv[]){

    No* n = criarNo("node_0");

    adicionarConexao(n,0,5);
    adicionarConexao(n,1,12);
    adicionarConexao(n,2,2.2);
    adicionarConexao(n,3,2);
    adicionarConexao(n,4,1.34);
    adicionarConexao(n,5,0);
    adicionarConexao(n,6,1);
    adicionarConexao(n,7,1.5);

    imprimirNo(n);

    liberarNo(n);
    return 0;
}