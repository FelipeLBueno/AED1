#include <stdio.h>
#include <string.h>

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int comeco, V, A;
        if (scanf("%d", &comeco) != 1) return 0;
        if (scanf("%d %d", &V, &A) != 2) return 0;

           //7x7 = 49, alocando 50
        int matriz[50][50];
        memset(matriz, 0, sizeof(matriz));
        int unico = 0;

        for (int i = 0; i < A; ++i) {
            int u, v;
            if (scanf("%d %d", &u, &v) != 2) return 0;
            int a = (u < v) ? u : v;
            int b = (u < v) ? v : u;
            if (!matriz[a][b]) {
                matriz[a][b] = 1;
                ++unico;
            }
        }

        /* mínimo de movimentos = 2 * (número de arestas distintas) */
        printf("%d\n", 2 * unico);
    }

    return 0;
}