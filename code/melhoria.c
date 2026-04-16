/*
|   TRABALHO PRÁTICO 1 - DIJKSTRA
|   Francisco Vassoler Merizio - 2024102652
|   Rodrigo Mattioli - 2019202335
|   TERCEIRA IMPLEMENTAÇÃO
|   main.c
*/
#include "funcoes.h"

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Uso: %s <entrada> <saida>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    int d, cont=0;
    float opt;
    char s[20], bomba[10], node_aux[20];
    No* node_s = NULL;
    char buffer[65536]; //buffer de 64K para ler linha por linha

     //setar variaveis de tempo
    //clock_t start = clock();

    //ABERTURA DE ARQUIVO DE ENTRADA
    FILE* arq=fopen(argv[1], "r");
    if(arq==NULL){
        printf("Erro ao abrir o arquivo\n");
        exit;
    }

    //ABERTURA DE ARQUIVO DE ENTRADA
    if(fgets(buffer, sizeof(buffer), arq) == NULL) exit(1);
    sscanf(buffer, "%s", s);
    long pos_dados = ftell(arq);
    while(fgets(buffer, sizeof(buffer), arq) != NULL) {
        char temp[256];
        if(sscanf(buffer, "%s", temp) == 1) cont++;
    }

    fseek(arq, pos_dados, SEEK_SET);

    //CRIAR A HEAP DE VERTICES
    Heap* heap = criaHeap(cont);

    for(int i = 1; i <= cont; i++){
        //LEITURA DA LINHA INTEIRA PARA O BUFFER
        if(fgets(buffer, sizeof(buffer), arq) == NULL) break;
        char* virgula = strchr(buffer, ',');
        if(virgula == NULL) {
             sscanf(buffer, "%s", node_aux);
        } else {
            *virgula = '\0';
            strcpy(node_aux, buffer);
            *virgula = ','; 
        }
        //ATUALIZAR O NOME DO NÓ
        No* no_atual = retornaNoHeap(heap, i);
        addNomeNo(no_atual, node_aux);
        if(strcmp(s, node_aux) == 0) {
            node_s = no_atual;
        }

        //CRIAR A HEAP DE VERTICES
        char* ptr = virgula ? virgula + 1 : buffer; 
        for(int j = 1; j <= cont; j++){
            if(i!=j){
                //CHEGAR ATÉ A PROXIMA CONEXÃO
                while(*ptr && !isdigit(*ptr) && *ptr != 'b' && *ptr != '-' && *ptr != '.') ptr++;
                if(!*ptr) break;   
                float peso;

                //CONTROLE DE BOMBAS
                if(strncmp(ptr, "bomba", 5) == 0){
                    peso = 0.0f;
                    ptr += 5;
                }
                else {
                    peso = strtof(ptr, &ptr);
                }
                
                if(peso > 0 && i != j){
                    adicionarConexao(no_atual, retornaNoHeap(heap, j), peso);
                }
            }
        }
    }

    if(node_s == NULL){
        printf("Erro: No de origem '%s' nao encontrado.\n", s);
        liberaHeap(heap);
        fclose(arq);
        exit(1);
    }


    //DISTANCIA DO NODE_S SETADA EM 0
    atualizaHeap(heap, node_s, 0.0);

    //FAZER O ALGORITMO DE DIJKSTRA
    while(tamanhoHeap(heap)>0){
        No* v_atual=removeHeap(heap); //EXTRAI MINIMO
        finalizarNo(v_atual);

        if(retornaDistanciaS(v_atual) == INFINITY) continue;
        Cel* v_aux=retornaCel(retornaWarden(v_atual));//LISTA DE CONEXÕES

        while(v_aux!=NULL){
            No* aux = retornaConex(v_aux);
            
            if(!estadoNo(aux)){ //ANALISE SE PRECISA TESTAR O RELAXAMENTO
                float peso=relaxeNo(v_atual, aux, retornaDistancia(v_aux));
                if(peso)
                    atualizaHeap(heap, aux, peso);
            }

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

    //IMPRESSÃO
    for(int i = cont; i>=1;i--){
        No* no_atual=retornaNoHeap(heap, i);
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

    //finalizar tempo
    //clock_t end = clock();
    //double seconds=((double)end-start)/CLOCKS_PER_SEC;
    //printf("Utilizando Heap: %lf\n", seconds);

    //LIBERANDO ESTRUTURAS DE DADOS
    liberaHeap(heap);
    fclose(out);
    fclose(arq);

    return 0;
}
