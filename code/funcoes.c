#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vertice.h"

void lerArquivo(char* nome){
    int d, cont=1;
    float opt;

    //ABERTURA DE ARQUIVO
    FILE* arq;
    arq=fopen(nome, "r");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit;
    }

    //NÓ S
    char node_s[9], bomba[6];
    fscanf(arq,"%[^\n] ", node_s);

    //TESTE PARA ENCONTRAR O NUMERO DE NOS
    char node_aux[9];
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


    //VETOR DE VERTICES
    No** array=malloc(sizeof(No*)*cont);
    int pos_array=0;
    fscanf(arq,"%[^\n~,] ", node_s);

    for(int i=0;i<cont;i++){
        fscanf(arq,"%[^\n~,] ", node_aux);
        No* aux=criarNo(node_aux);

        for(int j=0;j<cont;j++){
            if(i==j)    opt=0;
            else if(fscanf(arq,", %f", &opt)!=1) fscanf(arq,"%[^,~\n]", bomba); //CONTROLE DE BOMBAS
            else if(opt>0){
                adicionarConexao(aux, j, opt);
                //printf("%.2f -> %d\n", opt, j);                 //DEBUG
            }
            //printf("%.2f -> %d \n", opt, j);                 //DEBUG
        }
        while((d=fgetc(arq))!='\n' && d!=EOF);          //CONTINUAR ATÉ FIM DO ARQUIVO
        array[pos_array]=aux;
        pos_array++; 
    }

    printf("Nó S: %s\n", node_s);
    for(int i=0;i<cont;i++){
        imprimirNo(array[i]);
    }

    for(int i=0;i<cont;i++){
        liberarNo(array[i]);
    }
    free(array);
  
    fclose(arq);
}