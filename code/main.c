#include "funcoes.h"

int main(int argc, char* argv[]){
    int d, cont=1;
    float opt;
    char node_s[15], bomba[6], node_aux[15];

    //ABERTURA DE ARQUIVO
    FILE* arq;
    arq=fopen(argv[1], "r");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit;
    }

    //TESTE PARA ENCONTRAR O NUMERO DE NOS
    fscanf(arq,"%[^\n] ", node_s);
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
    
    fscanf(arq,"%[^\n~,] ", node_s);

    for(int i=1;i<=cont;i++){
        fscanf(arq,"%[^\n~,] ", node_aux);
        addNomeNo(retornaNoHeap(heap, i), node_aux);

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

    atualizaDistancia(retornaNoHeap(heap, 3), 15);
    atualizaHeap(heap, 3);


    //IMPRESSÃO PARA DEBUG
    printf("Nó S: %s\n", node_s);
    for(int i=1;i<=cont;i++){
        imprimirNo(retornaNoHeap(heap, i));
        //imprimirNo(array[i]);
    }


    //FAZER O ALGORITMO DE DIJKSTRA
    /*
    -Transformar o char node_S em um nó propriamente dito node_s

    Dijkstra(G, w, s)
        Inicializa(G, s)
        S ← ∅
        ConstruaFilaPrioridade(Q, G.V )
        while Q 6= ∅
            u ← ExtrairMinimo(Q)
            S ← S ∪ {u}
            for cada vértice v adjacentes à u
                Relaxe(u, v)
                DecresçaChave(Q, v, d[v])
    */

    liberaHeap(heap);

    fclose(arq);

    return 0;
}
