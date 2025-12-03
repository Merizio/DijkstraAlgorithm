#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char* argv[]){
    /*
    PLANEJAMENTO


    -Ler os dados da entrada
        .Ler o nó que será o "S"
        .Ler todos os Nós, de 0 a N-1
            >Ler o nome do nó
            >Ler todas as relações do nó atual com os outros
        .Colocar em uma matriz de adjacência

    -Transformar em Tad
        .Criar um TAD para lidar com os Nós
        .Nome, ID, dist para S, inicializada como Infinito, Pai
        .Lista de Adj?

    -Criar a Heap
        .Organizar as distâncias em uma heap de prioridade
        .Lista de Adj
        .FixUp/FixDown

    -Fazer Dijkstra
        .Inicializa em S
        .Atualiza as arestas tensas
        .Heap
        .Uma segunda Lista de vertices "Finalizados"

    -Escrever na Saida
        .De S para todos os Nós
        .Aleatoriedade nos caminhos com várias possibilidades
    

    *PSEUDO CÓDIGO ALGORITMO DE DIJKSTRA:

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
        
    Inicializa(G, s)
        for cada vértice v ∈ G.V
            v.pai ← Nil
            v.d ← ∞
            s.d ← 0


    */

}