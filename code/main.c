#include "funcoes.h"

int main(int argc, char* argv[]){
    int d, cont=1;
    float opt;
    char s[15], bomba[6], node_aux[15];
    No* node_s;

    //ABERTURA DE ARQUIVO
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


    //CRIAR A HEAP DE VERTICES
    Heap* heap = criaHeap(cont);
    
    fscanf(arq,"%[^\n~,] ", s);

    for(int i=1;i<=cont;i++){
        fscanf(arq,"%[^\n~,] ", node_aux);
        addNomeNo(retornaNoHeap(heap, i), node_aux);
        if(!strcmp(s, node_aux)) node_s=retornaNoHeap(heap, i);

        for(int j=1;j<=cont;j++){
            if(i==j)    opt=0;
            else if(fscanf(arq,", %f", &opt)!=1) fscanf(arq,"%[^,~\n]", bomba); //CONTROLE DE BOMBAS
            else if(opt>0){
                adicionarConexao(retornaNoHeap(heap, i), retornaNoHeap(heap, j), opt);
                //printf("%.2f -> %d\n", opt, j);                 //DEBUG
            }
            //printf("%.2f -> %d \n", opt, j);                 //DEBUG
        }
        while((d=fgetc(arq))!='\n' && d!=EOF);          //CONTINUAR ATÉ FIM DO ARQUIVO
    }


    //FAZER O ALGORITMO DE DIJKSTRA
    //DISTANCIA DO NODE_S SETADA EM 0
    atualizaHeap(heap, node_s, 0.0);

    while(tamanhoHeap(heap)>0){
        No* v_atual=removeHeap(heap);
        imprimirNo(v_atual);
        Cel* v_aux=retornaCel(retornaWarden(v_atual));
        while(1){
            if(v_aux==NULL) break;
            No* aux = retornaConex(v_aux);

            float peso=relaxeNo(v_atual, aux, retornaDistancia(v_aux));
            if(peso)
                atualizaHeap(heap, aux, peso);

            imprimirNo(aux);
            v_aux=retornaProxCel(v_aux);
        }
        printf("\n");
    }

    //TEORICAMENTE CORRETO, MAS PRECISA ARRUMAR OS INDICES

    //IMPRESSÃO CORRETA
    
       //IMPRESSÃO PARA DEBUG
    printf("Nó S: %s\n", s);
    for(int i=cont;i>=1;i--){
        imprimirNo(retornaNoHeap(heap, i));
    }

    liberaHeap(heap);

    fclose(arq);

    return 0;
}
