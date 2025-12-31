#include "funcoes.h"
#include "array.h"
#include <ctype.h>

// FUNÇÃO PARA ORDENAÇÃO LEXICOGRÁFICA
int compararParaImpressao(const void* a, const void* b) {
    No* noA = *(No**)a;
    No* noB = *(No**)b;
    float distA = retornaDistanciaS(noA);
    float distB = retornaDistanciaS(noB);
    if (distA < distB) return -1;
    if (distA > distB) return 1;
    return strcmp(retornaNomeNo(noA), retornaNomeNo(noB));
}

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Uso: %s <entrada> <saida>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    int cont = 0;
    int ns = -1; 
    char s[256], node_aux[256];
    No* node_s = NULL;
    char buffer[16384]; //buffer de 64K para ler linha por linha
    //setar variaveis de tempo
    clock_t start_time = clock();

    FILE* arq = fopen(argv[1], "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
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

    //MONTAR O GRAFO
    Array* array = criaArray(cont);
    for(int i = 0; i < cont; i++){
        if(fgets(buffer, sizeof(buffer), arq) == NULL) break;

        char* virgula = strchr(buffer, ',');
        if(virgula == NULL) {
             sscanf(buffer, "%s", node_aux);
        } else {
            *virgula = '\0';
            strcpy(node_aux, buffer);
            *virgula = ',';
        }

        No* no_atual = retornaNoArray(array, i);
        addNomeNo(no_atual, node_aux);

        if(strcmp(s, node_aux) == 0) {
            node_s = no_atual;
            ns = i;
        }

        char* ptr = virgula ? virgula + 1 : buffer; 
        for(int j = 0; j < cont; j++){
            while(*ptr && !isdigit(*ptr) && *ptr != '-' && *ptr != '.') ptr++;
            if(!*ptr) break;
            float peso = strtof(ptr, &ptr);
            if(peso > 0 && i != j){
                adicionarConexao(no_atual, retornaNoArray(array, j), peso);
            }
        }
    }

    //FAZER O ALGORITMO DE DIJKSTRA
    //DISTANCIA DO NODE_S SETADA EM 0
    atualizaDistancia(node_s, 0.0);
    trocaPosicaoArray(array, ns, 0);
    for(int i = 0; i < cont; i++){
        if(i > 0) ordenarArray(array, i);
        No* v_atual = retornaNoArray(array, i);
        if(retornaDistanciaS(v_atual) == INFINITY) break;

        Cel* v_aux = retornaCel(retornaWarden(v_atual));
        while(v_aux != NULL){
            No* vizinho = retornaConex(v_aux);
            float peso = retornaDistancia(v_aux);
            float novo = relaxeNo(v_atual, vizinho, peso);
            if(novo > 0) atualizaDistancia(vizinho, novo);
            v_aux = retornaProxCel(v_aux);
        }
    }
    //SAIDA DO ARQUIVO
    No** vetor_saida = malloc(sizeof(No*) * cont);
    for(int i=0; i<cont; i++) vetor_saida[i] = retornaNoArray(array, i);
    qsort(vetor_saida, cont, sizeof(No*), compararParaImpressao);
    FILE* out = fopen(argv[2], "w");
    if(out){
        for(int i=0; i<cont; i++){
            No* at = vetor_saida[i];
            fprintf(out, "SHORTEST PATH TO %s: %s ", retornaNomeNo(at), retornaNomeNo(at));
            if(strcmp(retornaNomeNo(at), s) != 0){
                No* p = retornaPaiNo(at);
                while(p){
                    fprintf(out, "<- %s ", retornaNomeNo(p));
                    if(strcmp(retornaNomeNo(p), s) == 0) break;
                    p = retornaPaiNo(p);
                }
            }
            fprintf(out, "(Distance: %.2f)\n", retornaDistanciaS(at));
        }
        fclose(out);
    }
    //FINALIZAR TEMPO
    clock_t end_time = clock();
    printf("Utilizando Array: %lf\n", ((double)end_time - start_time) / CLOCKS_PER_SEC);
    //LIBERANDO ESTRUTURAS DE DADOS
    free(vetor_saida);
    liberarArray(array);
    fclose(arq);
    return 0;
}