#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PONTOS 4005
#define MAX_NOME 50

typedef struct No {
    int vertice;
    struct No* prox;
} No;

No* grafo[MAX_PONTOS];
char nomes[MAX_PONTOS][MAX_NOME];
int total_nomes = 0;

void adicionarAresta(int u, int v) {
    No* novo = (No*)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = grafo[u];
    grafo[u] = novo;

    novo = (No*)malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = grafo[v];
    grafo[v] = novo;
}

int obterID(char* s) {
    // Procura se o nome já existe
    for (int i = 0; i < total_nomes; i++) {
        if (strcmp(nomes[i], s) == 0) {
            return i;
        }
    }
    // Se não existe, cadastra um novo
    strcpy(nomes[total_nomes], s);
    return total_nomes++;
}

//algoritmo de (BFS)
int bfs(int inicio, int fim, int n_pontos) {
    int distancia[MAX_PONTOS];
    int fila[MAX_PONTOS]; 
    int frente = 0, tras = 0;

    for (int i = 0; i < n_pontos; i++) {
        distancia[i] = -1;
    }

    // Configura o ponto inicial
    distancia[inicio] = 0;
    fila[tras++] = inicio;

    while (frente < tras) {
        int u = fila[frente++];

        if (u == fim) return distancia[u];

        // Percorre vizinhos
        No* aux = grafo[u];
        while (aux != NULL) {
            int v = aux->vertice;
            if (distancia[v] == -1) { // Se não foi visitado
                distancia[v] = distancia[u] + 1;
                fila[tras++] = v; // Insere na fila
            }
            aux = aux->prox;
        }
    }
    return -1;
}

int main() {
    int P, L;
    char s1[MAX_NOME], s2[MAX_NOME];

    // Inicializa o grafo com NULL
    for (int i = 0; i < MAX_PONTOS; i++) grafo[i] = NULL;

    scanf("%d %d", &P, &L);

    // Leitura das ligações
    for (int i = 0; i < L; i++) {
        scanf("%s %s", s1, s2);
        int u = obterID(s1);
        int v = obterID(s2);
        adicionarAresta(u, v);
    }

    int id_entrada = obterID("Entrada");
    int id_queijo = obterID("*");
    int id_saida = obterID("Saida");

    //da Entrada até o Queijo (*)
    int dist1 = bfs(id_entrada, id_queijo, total_nomes);
    
    // Queijo (*) até a Saida
    int dist2 = bfs(id_queijo, id_saida, total_nomes);

    // soma dos dois percursos
    printf("%d\n", dist1 + dist2);

    return 0;
}