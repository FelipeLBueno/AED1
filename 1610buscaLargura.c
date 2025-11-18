#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int N, M;
        if (scanf("%d %d", &N, &M) != 2) return 0;

        /* aloca estruturas para lista de adjacência compacta */
        int *cabeca = malloc((N + 1) * sizeof(int));
        int *para   = malloc(M * sizeof(int));
        int *proximo  = malloc(M * sizeof(int));
        int *indeg = calloc((N + 1), sizeof(int)); /* indegree 1..N */

        if (!cabeca || !para || !proximo || !indeg) {
            fprintf(stderr, "memoria\n");
            return 1;
        }

        for (int i = 1; i <= N; ++i) cabeca[i] = -1;

        int e = 0;
        for (int i = 0; i < M; ++i) {
            int A, B;
            scanf("%d %d", &A, &B);
            /* A depende de B -> aresta B -> A */
            para[e] = A;
            proximo[e] = cabeca[B];
            cabeca[B] = e++;
            indeg[A] += 1;
        }

        /* fila para BFS (Kahn): vertices com indegree 0 */
        int *fila = malloc((N + 5) * sizeof(int));
        if (!fila) { fprintf(stderr, "memoria\n"); return 1; }
        int qh = 0, qt = 0;

        for (int v = 1; v <= N; ++v) {
            if (indeg[v] == 0) fila[qt++] = v;
        }

        int processados = 0;
        /* BFS */
        while (qh < qt) {
            int u = fila[qh++];        /* FIFO */
            processados++;
            for (int ei = cabeca[u]; ei != -1; ei = proximo[ei]) {
                int v = para[ei];
                indeg[v]--;
                if (indeg[v] == 0) fila[qt++] = v;
            }
        }

        if (processados == N) printf("NAO\n");
        else printf("SIM\n");

        free(cabeca);
        free(para);
        free(proximo);
        free(indeg);
        free(fila);
    }

    return 0;
}