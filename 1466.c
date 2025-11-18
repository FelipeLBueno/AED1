#include <stdio.h>
#include <stdlib.h>

/* Nó da árvore */
typedef struct No {
    int valor;
    struct No *esquerda, *direita;
} No;

/* Cria um novo nó com valoror v */
static No* novo_No(int v) {
    No *p = (No*) malloc(sizeof(No));
    if (!p) { perror("malloc"); exit(1); }
    p->valor = v;
    p->esquerda = p->direita = NULL;
    return p;
}

int main(void) {
    int C;
    if (scanf("%d", &C) != 1) return 0;

    for (int tc = 1; tc <= C; ++tc) {
        int N;
        if (scanf("%d", &N) != 1) return 0;

        /* Vetor para guardar ponteiros dos nós alocados, para liberar depois */
        No **criado = malloc(sizeof(No*) * N);
        int criado_cnt = 0;

        No *raiz = NULL;

        for (int i = 0; i < N; ++i) {
            int x; scanf("%d", &x);
            if (raiz == NULL) {
                raiz = novo_No(x);
                criado[criado_cnt++] = raiz;
                continue;
            }
            /* inserção iterativa em BST (não recursiva) */
            No *atual = raiz;
            while (1) {
                if (x < atual->valor) {
                    if (atual->esquerda == NULL) {
                        No *p = novo_No(x);
                        atual->esquerda = p;
                        criado[criado_cnt++] = p;
                        break;
                    } else {
                        atual = atual->esquerda;
                    }
                } else { /* x > atual->valor, valorores distintos garantidos */
                    if (atual->direita == NULL) {
                        No *p = novo_No(x);
                        atual->direita = p;
                        criado[criado_cnt++] = p;
                        break;
                    } else {
                        atual = atual->direita;
                    }
                }
            }
        }

        /* BFS por níveis: fila simples */
        No **fila = malloc(sizeof(No*) * (N > 1 ? N : 1));
        int qCabeca = 0, qFim = 0;
        if (raiz != NULL) fila[qFim++] = raiz;

        printf("Case %d:\n", tc);

        /* imprimir elementos no formato pedido (sem espaço final) */
        int comeco = 1;
        while (qCabeca < qFim) {
            No *u = fila[qCabeca++];
            if (!comeco) printf(" ");
            printf("%d", u->valor);
            comeco = 0;
            if (u->esquerda)  fila[qFim++] = u->esquerda;
            if (u->direita) fila[qFim++] = u->direita;
        }
        printf("\n\n");

        /* libera memória dos nós e da fila */
        for (int i = 0; i < criado_cnt; ++i) free(criado[i]);
        free(criado);
        free(fila);
    }

    return 0;
}
