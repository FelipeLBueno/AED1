#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;

    /* lemos blocos enquanto N != 0 */
    while (scanf("%d", &N) == 1 && N != 0) {
        for (;;) {
            int first;
            if (scanf("%d", &first) != 1) return 0; /* EOF inesperado */

            /* linha com '0' indica fim do bloco atual */
            if (first == 0) {
                putchar('\n'); /* linha em branco após cada bloco */
                break;
            }

            /* lemos a permutação (first já lido) */
            int *target = (int*) malloc(sizeof(int) * N);
            if (!target) return 1;
            target[0] = first;
            for (int i = 1; i < N; ++i) {
                scanf("%d", &target[i]);
            }

            /* simulacao com pilha em vetor */
            int *stack = (int*) malloc(sizeof(int) * N);
            if (!stack) { free(target); return 1; }
            int topo = 0;        /* topo da pilha (número de elementos) */
            int next = 1;        /* próximo vagão a entrar (1..N) */
            int possible = 1;    /* flag */

            for (int i = 0; i < N; ++i) {
                int want = target[i];
                /* empilha até poder retirar o elemento desejado */
                while ((topo == 0 || stack[topo - 1] != want) && next <= N) {
                    stack[topo++] = next++;
                }
                /* se topo corresponde ao desejado, desempilha; senão impossível */
                if (topo > 0 && stack[topo - 1] == want) {
                    --topo; /* pop */
                } else {
                    possible = 0;
                    break;
                }
            }

            if (possible) printf("Yes\n");
            else printf("No\n");

            free(target);
            free(stack);
        }
    }

    return 0;
}