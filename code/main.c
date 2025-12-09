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
    No** array=malloc(sizeof(No*)*cont);
    for(int i=0;i<cont;i++){
        No* aux=criarNoId(i);
        array[i]=aux;
    }

    fscanf(arq,"%[^\n~,] ", node_s);

    for(int i=0;i<cont;i++){
        fscanf(arq,"%[^\n~,] ", node_aux);
        addNomeNo(array[i], node_aux);

        for(int j=0;j<cont;j++){
            if(i==j)    opt=0;
            else if(fscanf(arq,", %f", &opt)!=1) fscanf(arq,"%[^,~\n]", bomba); //CONTROLE DE BOMBAS
            else if(opt>0){
                adicionarConexao(array[i], array[j], opt);
                //printf("%.2f -> %d\n", opt, j);                 //DEBUG
            }
            //printf("%.2f -> %d \n", opt, j);                 //DEBUG
        }
        while((d=fgetc(arq))!='\n' && d!=EOF);          //CONTINUAR ATÉ FIM DO ARQUIVO
    }

    //IMPRESSÃO PARA DEBUG
    printf("Nó S: %s\n", node_s);
    for(int i=0;i<cont;i++){
        imprimirNo(array[i]);
    }


    //FAZER O ALGORITMO DE DIJKSTRA


    //LIBERAR TODAS AS ESTRUTURAS
    for(int i=0;i<cont;i++){
        liberarNo(array[i]);
    }
    free(array);
  
    fclose(arq);

    return 0;
}