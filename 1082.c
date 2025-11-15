#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    for (int tc = 1; tc <= N; ++tc) {
        int V, E;
        if (scanf("%d %d", &V, &E) != 2) return 0;

        int matriz[26][26] = {0};
        int visitado[26] = {0};

        //le as E arestas; aceita formatos "ab", "a b", "a b\n"
        for (int i = 0; i < E; ++i) {
            char x, y;
            if (scanf(" %c %c", &x, &y) != 2) return 0;
            int u = x - 'a';
            int v = y - 'a';
            if (u >= 0 && u < V && v >= 0 && v < V) {
                matriz[u][v] = matriz[v][u] = 1;
            }
        }

        printf("Case #%d:\n", tc);

        int componentes = 0;
        int pilha[26];

        for (int i = 0; i < V; ++i) {
            if (!visitado[i]) {
                int topo = 0;
                pilha[topo++] = i;
                visitado[i] = 1;

                int compo[26];
                int compo_size = 0;
                while (topo > 0) {
                    int atual = pilha[--topo];
                    compo[compo_size++] = atual;
                    /* empilha vizinhos não visitados */
                    for (int nb = 0; nb < V; ++nb) {
                        if (matriz[atual][nb] && !visitado[nb]) {
                            visitado[nb] = 1;
                            pilha[topo++] = nb;
                        }
                    }
                }

                /* ordenar vértices da componente em ordem crescente */
                for (int a = 0; a < compo_size; ++a) {
                    for (int b = a + 1; b < compo_size; ++b) {
                        if (compo[a] > compo[b]) {
                            int temp = compo[a];
                            compo[a] = compo[b];
                            compo[b] = temp;
                        }
                    }
                }

                /* imprimir linha do componente com vírgulas e vírgula final */
                for (int k = 0; k < compo_size; ++k) {
                    printf("%c,", 'a' + compo[k]);
                }
                printf("\n");

                ++componentes;
            }
        }

        printf("%d connected components\n\n", componentes);
    }

    return 0;
}
