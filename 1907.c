#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    //aloca espaço para a imagem e um array
    int total = N * M;
    char *grid = malloc(total);
    if (!grid) return 0;
    char *visualizar = calloc(total, 1);
    if (!visualizar) { free(grid); return 0; }

    // lê N*M caracteres '.', 'o'
    int ch;
    for (int i = 0; i < total; ++i) {
        do {
            ch = getchar();
            if (ch == EOF) break;
        } while (ch != '.' && ch != 'o');
        if (ch == EOF) {
            /*entrada inesperada, preencher com 'o' (preto) */
            grid[i] = 'o';
        } else {
            grid[i] = (char)ch;
        }
    }

    /* fila armazena índices achatados r*M + c */
    int *fila = malloc(sizeof(int) * total);
    if (!fila) { free(grid); free(visualizar); return 0; }

    int dr[4] = { -1, 0, 1, 0 };
    int dc[4] = { 0, 1, 0, -1 };
    int componentes = 0;

    for (int indice = 0; indice < total; ++indice) {
        if (grid[indice] == '.' && !visualizar[indice]) {
            /* nova componente encontrada */
            componentes++;
            int cabeca = 0, fim = 0;
            visualizar[indice] = 1;
            fila[fim++] = indice;

            /* BFS para marcar toda a componente */
            while (cabeca < fim) {
                int cur = fila[cabeca++];
                int r = cur / M;
                int c = cur % M;
                for (int k = 0; k < 4; ++k) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                        int Nindice = nr * M + nc;
                        if (!visualizar[Nindice] && grid[Nindice] == '.') {
                            visualizar[Nindice] = 1;
                            fila[fim++] = Nindice;
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", componentes);

    free(grid);
    free(visualizar);
    free(fila);
    return 0;
}