#include <stdio.h>
#include <stdlib.h>

typedef struct Borda {
    int u, v;
    int w;
} Borda;

// comparador para quick sort e ordena por peso crescente
static int compara_borda(const void *a, const void *b) {
    const Borda *ea = (const Borda*) a;
    const Borda *eb = (const Borda*) b;
    return ea->w - eb->w;
}

static int *parente;
static int *classifica;

static void dentro(int n) {
    parente = (int*) malloc((n + 1) * sizeof(int));
    classifica   = (int*) malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        parente[i] = i;
        classifica[i] = 0;
    }
}

static int achar(int x) {
    if (parente[x] != x) parente[x] = achar(parente[x]);
    return parente[x];
}

static void unir(int a, int b) {
    a = achar(a);
    b = achar(b);
    if (a == b) return;
    if (classifica[a] < classifica[b]) parente[a] = b;
    else if (classifica[b] < classifica[a]) parente[b] = a;
    else { parente[b] = a; classifica[a]++; }
}

static void liberar(void) {
    free(parente);
    free(classifica);
}

int main(void) {
    int M, N;
    while (scanf("%d %d", &M, &N) == 2) {
        if (M == 0 && N == 0) break;

        Borda *Bordas = (Borda*) malloc(sizeof(Borda) * N);
        if (!Bordas) { perror("malloc"); return 1; }

        for (int i = 0; i < N; ++i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            Bordas[i].u = x;
            Bordas[i].v = y;
            Bordas[i].w = z;
        }

        qsort(Bordas, N, sizeof(Borda), compara_borda);

        dentro(M - 1 < 0 ? M : M - 1 ); 
        free(parente); free(classifica);
        dentro(M);

        long long total = 0;
        int levar = 0;
        for (int i = 0; i < N && levar < M - 1; ++i) {
            int a = Bordas[i].u;
            int b = Bordas[i].v;
            if (achar(a) != achar(b)) {
                unir(a, b);
                total += Bordas[i].w;
                levar++;
            }
        }

        printf("%lld\n", total);

        liberar();
        free(Bordas);
    }
    return 0;
}
