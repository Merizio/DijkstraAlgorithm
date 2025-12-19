#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "array.h"

struct array{
    No** array_no;
    int n;
};

Array* criaArray(int tam){
    Array* array = malloc(sizeof(Array));
    array->n=tam;
    array->array_no=malloc(sizeof(No*)*array->n);
    for(int i=0;i<array->n;i++){
        array->array_no[i]=criarNo(i);
    }

    return array;
}

No* retornaNoArray(Array* x, int pos){
    return x->array_no[pos];
}

void trocaPosicaoArray(Array* x, int p1, int p2){
    No* aux = x->array_no[p1];
    x->array_no[p1]=x->array_no[p2];
    x->array_no[p2]=aux;
}

static int comparar (const void * a1, const void * a2){
    No* n1 = *(No**)a1;
    No* n2 = *(No**)a2;

    float f1 = retornaDistanciaS(n1);
    float f2 = retornaDistanciaS(n2);
    if(f1<f2) return -1;
    else if(f1>f2)return 1;
    return 0;
}

void ordenarArray(Array* x, int lo){
    qsort(x->array_no+lo, x->n-lo, sizeof(No*), comparar);
}

int completarArray(Array* x, FILE* arq){
    int d, cont=1, ns;
    float opt;
    char s[15], bomba[6], node_aux[15];
    No* node_s;

    printf("%d\n", x->n);

    fscanf(arq,"%[^\n~,] ", s);

    printf("%s\n", s);

    for(int i=0;i<x->n;i++){
        fscanf(arq,"%[^\n~,] ", node_aux);
        addNomeNo(x->array_no[i], node_aux);
        if(!strcmp(s, node_aux)) {node_s=x->array_no[i];ns=i;}

        for(int j=0;j<cont;j++){
            if(i==j)    opt=0;
            else if(fscanf(arq,", %f", &opt)!=1) fscanf(arq,"%[^,~\n]", bomba); //CONTROLE DE BOMBAS
            else if(opt>0){
                adicionarConexao(x->array_no[i], x->array_no[j], opt);
            }
        }
        while((d=fgetc(arq))!='\n' && d!=EOF);          //CONTINUAR ATÉ FIM DO ARQUIVO
    }

    return ns;
}

/*void execDijkstra(Array* x, FILE* arq, ){
    //FAZER O ALGORITMO DE DIJKSTRA
    //DISTANCIA DO NODE_S SETADA EM 0
    atualizaDistancia(node_s, 0);
    //troca(array[ns], array[0]);
    No* aux = array[ns];
    array[ns]=array[0];
    array[0]=aux;

    //imprimirNo(array[0]);

    for(int i=0;i<cont;i++){
        if(i>0) qsort(array+i, cont-i, sizeof(No*), comparar);

        No* v_atual=array[i];
        Cel* v_aux=retornaCel(retornaWarden(v_atual));
        while(1){
            if(v_aux==NULL) break;
            No* aux = retornaConex(v_aux);

            float peso=relaxeNo(v_atual, aux, retornaDistancia(v_aux));
            if(peso)
                atualizaDistancia(aux, peso);

            //imprimirNo(aux);
            v_aux=retornaProxCel(v_aux);
        }
    }
}*/

void liberarArray(Array* x){
    for(int i=0;i<x->n;i++){
        liberarNo(x->array_no[i]);
    }
    free(x->array_no);
    free(x);
}