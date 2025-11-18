#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    int u, v;
    int w;
} Edge;

static int cmpBorda(const void *a, const void *b) {
    const Edge *ea = (const Edge*)a;
    const Edge *eb = (const Edge*)b;
    if (ea->w < eb->w) return -1;
    if (ea->w > eb->w) return 1;
    return 0;
}

int *array_Prox;
int *array_Classe;

int procura(int x) {
    int p = array_Prox[x];
    if (p != x) array_Prox[x] = procura(p);
    return array_Prox[x];
}

int uniao(int a, int b) {
    a = procura(a);
    b = procura(b);
    if (a == b) return 0;
    if (array_Classe[a] < array_Classe[b]) {
        array_Prox[a] = b;
    } else if (array_Classe[b] < array_Classe[a]) {
        array_Prox[b] = a;
    } else {
        array_Prox[b] = a;
        array_Classe[a]++;
    }
    return 1;
}

int main(void) {
    int m, n;
    while (scanf("%d %d", &m, &n) == 2) {
        if (m == 0 && n == 0) break;

        Edge *bordas = malloc(sizeof(Edge) * n);
        if (!bordas) return 1;

        ll total = 0;
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            bordas[i].u = x;
            bordas[i].v = y;
            bordas[i].w = z;
            total += (ll)z;
        }

        /* ordenar arestas por peso */
        qsort(bordas, n, sizeof(Edge), cmpBorda);

        /* inicializar DSU (cidades identificadas 0..m-1 no enunciado) */
        array_Prox = malloc(sizeof(int) * m);
        array_Classe   = malloc(sizeof(int) * m);
        if (!array_Prox || !array_Classe) return 1;
        for (int i = 0; i < m; ++i) {
            array_Prox[i] = i;
            array_Classe[i] = 0;
        }

        ll mst = 0;
        int usado = 0;
        for (int i = 0; i < n && usado < m - 1; ++i) {
            int u = bordas[i].u;
            int v = bordas[i].v;
            if (uniao(u, v)) {
                mst += (ll)bordas[i].w;
                usado++;
            }
        }

        printf("%lld\n", total - mst);

        free(bordas);
        free(array_Prox);
        free(array_Classe);
    }

    return 0;
}