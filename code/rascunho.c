#include "funcoes.h"

int main(int argc, char* argv[]){
    srand(time(NULL));
    int d, cont=1, ns;
    float opt;
    char s[15], bomba[6], node_aux[15];
    No* node_s;

    //ABERTURA DE ARQUIVO DE ENTRADA
    FILE* arq;
    arq=fopen(argv[1], "r");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit;
    }

    //TESTE PARA ENCONTRAR O NUMERO DE NOS
    fscanf(arq,"%[^\n] ", s);
    fscanf(arq,"%[^\n~,] ", node_aux);
    while(1){
        while(fscanf(arq,", %f", &opt)==1){
            cont++;
        }
        //CONTROLE PARA BOMBA
        fscanf(arq,"%[^,]", bomba);
        if(strcmp(bomba, "bomba")!=0) break;
        cont++;
    }
    rewind(arq);

    //CRIAR UM VETOR DE VERTICES
    Array* array = criaArray(cont);

    fscanf(arq,"%[^\n~,] ", s);
    printf("%s\n", s);

    ns=completarArray(array, arq);

    //FAZER O ALGORITMO DE DIJKSTRA
    //DISTANCIA DO NODE_S SETADA EM 0
    atualizaDistancia(node_s, 0);
    //troca(array[ns], array[0]);

    printf("%d\n", ns);
    
    trocaPosicaoArray(array, ns, 0);

    printf("%s\n", s);

    //imprimirNo(array[0]);

    for(int i=0;i<cont;i++){
        if(i>0) ordenarArray(array, i);

        No* v_atual=retornaNoArray(array, i);
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

    //ABERTURA DO ARQUIVO DE SAÍDA
    FILE* out;
    out=fopen(argv[2], "w");
    if(out==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit;
    }

    for(int i=0; i<cont;i++){
        No* no_atual=retornaNoArray(array, i);
        fprintf(out, "SHORTEST PATH TO %s: %s ", retornaNomeNo(no_atual), retornaNomeNo(no_atual));
        if(!strcmp(retornaNomeNo(no_atual), retornaNomeNo(node_s))) fprintf(out, "<- %s ", retornaNomeNo(node_s));
        No* no_pai=retornaPaiNo(no_atual);
        while(1){
            if(no_pai==NULL) break;
            fprintf(out, "<- %s ", retornaNomeNo(no_pai));
            no_pai=retornaPaiNo(no_pai);
        }
        fprintf(out, "(Distance: %.2f)\n", retornaDistanciaS(no_atual));
    }

    liberarArray(array);

    return 0;
}