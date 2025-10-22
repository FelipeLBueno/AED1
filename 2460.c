#include <stdio.h>
#include <stdlib.h>

int main () {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    /* lê fila inicial */
    int *fila = (int*) malloc(sizeof(int) * N);
    if (!fila) return 1;
    for (int i = 0; i < N; ++i) scanf("%d", &fila[i]);

    int M;
    if (scanf("%d", &M) != 1) { free(fila); return 0; }

    /* marcações de quem saiu
       Os identificadores estão entre 1 e 100000 conforme enunciado,
       então podemos usar um vetor booleano de tamanho 100001. */
    enum { MAXID = 100000 };
    /* usamos char para economizar memória; 0 = presente, 1 = saiu */
    char *saiu = (char*) calloc(MAXID + 1, sizeof(char));
    if (!saiu) { free(fila); return 1; }

    for (int i = 0; i < M; ++i) {
        int id;
        scanf("%d", &id);
        if (id >= 1 && id <= MAXID) saiu[id] = 1;
        /* se por segurança o id estivesse fora, ainda marcaríamos em tabela maior;
           mas o enunciado garante o intervalo. */
    }

    /* imprime os que permaneceram, mantendo a ordem original.
       evitamos espaço final extra: imprimimos primeiro elemento sem prefixo
       e os seguintes com um espaço antes. */
    int first_printed = 0;
    for (int i = 0; i < N; ++i) {
        int id = fila[i];
        if (id >= 1 && id <= MAXID && !saiu[id]) {
            if (!first_printed) {
                printf("%d", id);
                first_printed = 1;
            } else {
                printf(" %d", id);
            }
        }
    }
    printf("\n");

    free(fila);
    free(saiu);
    return 0;
}