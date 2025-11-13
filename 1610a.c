#include <stdio.h>
#include <stdlib.h>

int N;
unsigned char *matriz; // matriz de adjacência
int *identif;

/* retorna 1 se encontrar ciclo a partir de u, 0 caso contrário */
int dfs_cycle(int u) {
    identif[u] = 1;
    unsigned char *row = matriz + (size_t)u * N; /* ponteiro para a linha u */
    for (int v = 0; v < N; ++v) {
        if (!row[v]) continue; /* sem aresta u->v */
        if (identif[v] == 1) {
            return 1;
        } else if (identif[v] == 0) {
            if (dfs_cycle(v)) return 1;
        }
    }
    identif[u] = 2;
    return 0;
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int M;
        if (scanf("%d %d", &N, &M) != 2) return 0;

        /* alocação da matrizriz (N*N bytes). verificar overflow/limite simples */
        size_t necessario = (size_t)N * (size_t)N;
        //evitando malloc catastrófico.
        if (necessario > 200000000U) {
            fprintf(stderr, "N grande demais para representação por matrizes: N=%d\n", N);
            return 1;
        }

        matriz = (unsigned char*) calloc(necessario, sizeof(unsigned char));
        if (!matriz) { fprintf(stderr, "Falha na alocacao da matrizes\n"); return 1; }

        identif = (int*) calloc(N, sizeof(int));
        if (!identif) { fprintf(stderr, "Falha na alocacao\n"); free(matriz); return 1; }

        /* lê as M dependências e marca matriz[A-1][B-1] = 1 (A -> B) */
        for (int i = 0; i < M; ++i) {
            int A, B;
            scanf("%d %d", &A, &B);
            if (A < 1 || A > N || B < 1 || B > N) continue;
            matriz[(size_t)(A-1) * N + (B-1)] = 1;
        }

        /* detecta ciclo: para cada vértice branco faz DFS */
        int ciclo = 0;
        for (int u = 0; u < N; ++u) {
            if (identif[u] == 0) {
                if (dfs_cycle(u)) { ciclo = 1; break; }
            }
        }

        if (ciclo) printf("SIM\n"); else printf("NAO\n");

        free(matriz);
        free(identif);
    }

    return 0;
}