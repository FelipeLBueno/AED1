#include <stdio.h>
#include <string.h>

#define MAXN 500
#define INF 1000000000

int main(void) {
    int N, E;
    while (scanf("%d %d", &N, &E) == 2) {
        if (N == 0 && E == 0) break;

        static int distancia[MAXN][MAXN];
        static unsigned char alcance[MAXN][MAXN]; /* 0/1 para alcanceability */
        /* inicialização */
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                distancia[i][j] = (i == j) ? 0 : INF;
                alcance[i][j] = (i == j) ? 1 : 0;
            }
        }

        /* lê arestas direcionadas (X -> Y com custo H) */
        for (int i = 0; i < E; ++i) {
            int X, Y, H;
            scanf("%d %d %d", &X, &Y, &H);
            --X; --Y;
            if (H < distancia[X][Y]) distancia[X][Y] = H; /* mantém mínima se houver múltiplas */
            alcance[X][Y] = 1;
        }

        /* Floyd-Warshall sobre alcanceability (fechamento transitivo) */
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                if (alcance[i][k])
                    for (int j = 0; j < N; ++j)
                        if (alcance[k][j])
                            alcance[i][j] = 1;

        /* dentro da mesma SCC (i->j e j->i), comunicação eletrônica é instantânea */
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (alcance[i][j] && alcance[j][i])
                    distancia[i][j] = 0;

        // distancis (menores tempos com links instantâneos
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                if (distancia[i][k] == INF) continue;
                for (int j = 0; j < N; ++j) {
                    if (distancia[k][j] == INF) continue;
                    int nd = distancia[i][k] + distancia[k][j];
                    if (nd < distancia[i][j]) distancia[i][j] = nd;
                }
            }
        }

        /* consulta */
        int K; scanf("%d", &K);
        for (int q = 0; q < K; ++q) {
            int O, D; scanf("%d %d", &O, &D);
            --O; --D;
            if (distancia[O][D] >= INF) printf("Nao e possivel entregar a carta\n");
            else printf("%d\n", distancia[O][D]);
        }

        printf("\n");
    }

    return 0;
}