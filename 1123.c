#include <stdio.h>
#include <limits.h>

#define MAXN 250
#define INF 1000000000

int main(void) {
    while (1) {
        int N, M, C, K;
        if (scanf("%d %d %d %d", &N, &M, &C, &K) != 4) return 0;
        if (N==0 && M==0 && C==0 && K==0) break;

        static int w[MAXN][MAXN];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                w[i][j] = (i==j) ? 0 : INF;

        for (int i = 0; i < M; ++i) {
            int U, V, P;
            scanf("%d %d %d", &U, &V, &P);
            if (P < w[U][V]) { w[U][V] = w[V][U] = P; }
        }

        static int rota_restante[MAXN];
        rota_restante[C-1] = 0;
        for (int j = C-2; j >= 0; --j) {
            /* existe estrada direta j <-> j+1 por definição da rota */
            if (w[j][j+1] >= INF) {
                /* se por algum motivo não houver,*/
                rota_restante[j] = INF;
            } else {
                if (rota_restante[j+1] >= INF) rota_restante[j] = INF;
                else rota_restante[j] = w[j][j+1] + rota_restante[j+1];
            }
        }

        static int dist[MAXN];
        static int usado[MAXN];
        for (int i = 0; i < N; ++i) { dist[i] = INF; usado[i] = 0; }
        dist[K] = 0;

        for (int iter = 0; iter < N; ++iter) {
            int u = -1, melhor = INF;
            for (int i = 0; i < N; ++i) {
                if (!usado[i] && dist[i] < melhor) { melhor = dist[i]; u = i; }
            }
            if (u == -1) break;
            usado[u] = 1;

            /* se u é nó da rota, NÃO expandimos seus vizinhos */
            if (u >= 0 && u < C) continue;

            for (int v = 0; v < N; ++v) {
                if (w[u][v] < INF && !usado[v]) {
                    int nd = dist[u] + w[u][v];
                    if (nd < dist[v]) dist[v] = nd;
                }
            }
        }

        int resposta = INF;
        for (int j = 0; j < C; ++j) {
            if (rota_restante[j] >= INF) continue;
            if (dist[j] >= INF) continue;
            int total = dist[j] + rota_restante[j];
            if (total < resposta) resposta = total;
        }

        /* imprimir resultado */
        printf("%d\n", resposta);
    }

    return 0;
}
