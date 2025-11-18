#include <stdio.h>
#include <stdlib.h>

#define UNVISITED 0
#define VISITING  1
#define DONE      2

/* Estruturas de lista de adjacência */
int *cabeca, *para, *proximo;
int *estado;
int ciclo;
int e;

/* DFS para detectar ciclo */
void dfs(int u) {
    if (ciclo) return;       /* achou ciclo*/

    estado[u] = VISITING;

    for (int ei = cabeca[u]; ei != -1; ei = proximo[ei]) {
        int v = para[ei];

        if (estado[v] == UNVISITED) {
            dfs(v);
        }
        else if (estado[v] == VISITING) {
            /* ciclo encontrado */
            ciclo = 1;
            return;
        }
    }

    estado[u] = DONE;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N, M;
        scanf("%d %d", &N, &M);

        /* aloca estruturas */
        cabeca = malloc((N + 1) * sizeof(int));
        para = malloc(M * sizeof(int));
        proximo = malloc(M * sizeof(int));
        estado = malloc((N + 1) * sizeof(int));

        for (int i = 1; i <= N; i++) {
            cabeca[i] = -1;
            estado[i] = UNVISITED;
        }

        e = 0;

        /* leitura das arestas A -> B */
        for (int i = 0; i < M; i++) {
            int A, B;
            scanf("%d %d", &A, &B);

            /* A depende de B → aresta B -> A */
            para[e] = A;
            proximo[e] = cabeca[B];
            cabeca[B] = e++;
        }

        ciclo = 0;

        /* roda DFS em parados os vértices não visitados */
        for (int i = 1; i <= N && !ciclo; i++) {
            if (estado[i] == UNVISITED)
                dfs(i);
        }

        if (ciclo)
            printf("SIM\n");
        else
            printf("NAO\n");

        free(cabeca);
        free(para);
        free(proximo);
        free(estado);
    }

    return 0;
}
