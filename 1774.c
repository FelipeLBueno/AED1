#include <stdio.h>
#include <stdlib.h>

#define MAX_ROTEADORES 70

// Estrutura para representar um cabo
typedef struct {
    int o; // Roteador de origem
    int d; // Roteador de destino
    int preco;
} Aresta;

// Vetor para o armazenar o pai de cada roteador
int pai[MAX_ROTEADORES];

int comparar(const void *a, const void *b) {
    return ((Aresta*)a)->preco - ((Aresta*)b)->preco;
}

// Encontra a raiz do conjunto do roteador i
int find(int i) {
    if (pai[i] == i)
        return i;
    //aponta direto para o avô/raiz
    return pai[i] = find(pai[i]);
}

// Une dois conjuntos
void join(int i, int j) {
    int raiz_i = find(i);
    int raiz_j = find(j);
    
    if (raiz_i != raiz_j) {
        pai[raiz_i] = raiz_j;
    }
}

int main() {
    int R, C;
    
    // Leitura de Roteadores e Cabos
    scanf("%d %d", &R, &C);

    Aresta *arestas = (Aresta*) malloc(C * sizeof(Aresta));

    for (int i = 0; i < C; i++) {
        scanf("%d %d %d", &arestas[i].o, &arestas[i].d, &arestas[i].preco);
    }

    for (int i = 1; i <= R; i++) {
        pai[i] = i;
    }

    //ordena as arestas pelo menor preço
    qsort(arestas, C, sizeof(Aresta), comparar);

    int custo_total = 0;
    int arestas_selecionadas = 0;

    for (int i = 0; i < C; i++) {
        // Verifica se os roteadores o e d já estão conectados
        if (find(arestas[i].o) != find(arestas[i].d)) {
            // Se não estiverem, "compra" o cabo
            join(arestas[i].o, arestas[i].d);
            custo_total += arestas[i].preco;
            arestas_selecionadas++;
        }

        if (arestas_selecionadas == R - 1) {
            break;
        }
    }

    printf("%d\n", custo_total);

    free(arestas);
    return 0;
}