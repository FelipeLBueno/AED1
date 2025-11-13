#include <stdio.h>
#include <stdlib.h>

typedef struct Borda {
    int para;
    struct Borda *proximo;
} Borda;

// adiciona aresta A -> B (insere no início da lista de A
static void add_Borda(Borda **adjacente, int A, int B) {
    Borda *e = (Borda*) malloc(sizeof(Borda));
    if (!e) { perror("malloc"); exit(1); }
    e->para = B;
    e->proximo = adjacente[A];
    adjacente[A] = e;
}

static int ciclo(int u, Borda **adjacente, int *identif) {
    identif[u] = 1;
    for (Borda *e = adjacente[u]; e != NULL; e = e->proximo) {
        int v = e->para;
        if (identif[v] == 0) {
            if (ciclo(v, adjacente, identif)) return 1;
        } else if (identif[v] == 1) {
            /* encontrou aresta para nó -> ciclo */
            return 1;
        }
    }
    identif[u] = 2;
    return 0;
}

/* libera as listas de adjacenteacência */
static void free_adjacente(Borda **adjacente, int N) {
    for (int i = 1; i <= N; ++i) {
        Borda *e = adjacente[i];
        while (e) {
            Borda *t = e->proximo;
            free(e);
            e = t;
        }
    }
    free(adjacente);
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int N, M;
        if (scanf("%d %d", &N, &M) != 2) return 0;

        /* aloca vetor de cabeças (1..N) */
        Borda **adjacente = (Borda**) malloc((N + 1) * sizeof(Borda*));
        if (!adjacente) { fprintf(stderr, "malloc falhou\n"); return 1; }
        for (int i = 1; i <= N; ++i) adjacente[i] = NULL;

        // lê arestas e insere nas listas
        for (int i = 0; i < M; ++i) {
            int A, B;
            scanf("%d %d", &A, &B);
            if (A >= 1 && A <= N && B >= 1 && B <= N) {
                add_Borda(adjacente, A, B);
            }
        }

        int *identif = (int*) calloc(N + 1, sizeof(int));
        if (!identif) { fprintf(stderr, "calloc falhou\n"); free_adjacente(adjacente, N); return 1; }

        int tem_ciclo = 0;
        for (int u = 1; u <= N; ++u) {
            if (identif[u] == 0) {
                if (ciclo(u, adjacente, identif)) { tem_ciclo = 1; break; }
            }
        }

        printf(tem_ciclo ? "SIM\n" : "NAO\n");

        free(identif);
        free_adjacente(adjacente, N);
    }

    return 0;
}