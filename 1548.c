#include <stdio.h>
#include <stdlib.h>

/* comparador para qsort: ordem decrescente */
static int cmp_desc(const void *pa, const void *pb) {
    int a = *(const int*)pa;
    int b = *(const int*)pb;
    if (a < b) return 1;
    if (a > b) return -1;
    return 0;
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0; /* número de casos */

    for (int tc = 0; tc < T; ++tc) {
        int M;
        if (scanf("%d", &M) != 1) return 0;

        /* aloca vetores de tamanho M */
        int *orig = (int*) malloc(sizeof(int) * M);
        int *sorted = (int*) malloc(sizeof(int) * M);
        if (!orig || !sorted) {
            fprintf(stderr, "Erro de alocacao\n");
            return 1;
        }

        /* lê notas na ordem de chegada */
        for (int i = 0; i < M; ++i) {
            scanf("%d", &orig[i]);
            sorted[i] = orig[i]; /* copia para ordenar */
        }

        /* ordena em ordem decrescente (quem tem maior nota fica na frente) */
        qsort(sorted, M, sizeof(int), cmp_desc);

        /* conta quantos permaneceram na mesma posição */
        int unchanged = 0;
        for (int i = 0; i < M; ++i) {
            if (orig[i] == sorted[i]) ++unchanged;
        }

        printf("%d\n", unchanged);

        free(orig);
        free(sorted);
    }

    return 0;
}