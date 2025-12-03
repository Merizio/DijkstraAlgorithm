#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    printf("%s\n", node_s);

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


    //MATRIZ DE ADJACENCIA
    fscanf(arq,"%[^\n~,] ", node_aux);

    float** adj=malloc(sizeof(float*)*cont);
    for(int i=0;i<cont;i++){
        adj[i]=malloc(sizeof(float)*cont);
    }


    for(int i=0;i<cont;i++){
        //COLOCAR ESSE NOME DO NÓ NO TAD NÓ FUTURO
        fscanf(arq,"%[^\n~,] ", node_aux);
        //printf("\nNÓ:%s->%d ", node_aux, i);          //DEBUG
        for(int j=0;j<cont;j++){
            if(i==j)    adj[i][j]=0;
            else if(fscanf(arq,", %f", &adj[i][j])!=1){ //CONTROLE DE BOMBAS 
                adj[i][j]=-1;
                fscanf(arq,"%[^,~\n]", bomba);
            }
            //printf("%d ", adj[i][j]);                 //DEBUG
        }
        while((d=fgetc(arq))!='\n' && d!=EOF);          //CONTINUAR ATÉ FIM DO ARQUIVO
    }



    //IMPRIMIR A MATRIZ DE ADJACENCIA (DEBUG)
    for(int i=0;i<cont;i++){
        printf("node_%d", i);
        for(int j=0;j<cont;j++){
            if(adj[i][j]==-1) printf(", bomba");       //SE QUISER DIFERENCIAR AS BOMBAS
            else if(i!=j) printf(", %.2f", adj[i][j]); //SE QUISER MOSTRAR APENAS AS LIGAÇÕES
            //printf(", %.2f", adj[i][j]);             //MATRIZ DE ADJACENCIA COMPLETA
        }
        printf("\n");
    }


    //LIBERAR MATRIZ DE ADJ (ATUALMENTE)
    for(int i=0;i<cont;i++){
        free(adj[i]);
    }
    free(adj);

    fclose(arq);
}