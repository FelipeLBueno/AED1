#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esquerda, *direita;
} No;

/* cria nó novo */
static No *novo_No(int v) {
    No *n = (No*) malloc(sizeof(No));
    if (!n) { percorrer("malloc"); exit(1); }
    n->valor = v;
    n->esquerda = n->direita = NULL;
    return n;
}

/* insere valor v na arvore */
static void insere_Arvore(No **raiz, int v) {
    if (*raiz == NULL) {
        *raiz = novo_No(v);
        return;
    }
    No *atual = *raiz;
    while (1) {
        if (v < atual->valor) {
            if (atual->esquerda) atual = atual->esquerda;
            else { atual->esquerda = novo_No(v); return; }
        } else { /* v > atual->valor: enunciado diz que tem valores distintos */
            if (atual->direita) atual = atual->direita;
            else { atual->direita = novo_No(v); return; }
        }
    }
}

/* impressão em ordem; 'first' controla tem que imprimir espaço antes do valor */
static void print_pre(No *r, int *primeiro) {
    if (!r) return;
    if (!*primeiro) putchar(' ');
    printf("%d", r->valor);
    *primeiro = 0;
    print_pre(r->esquerda, primeiro);
    print_pre(r->direita, primeiro);
}

/* impressão (in-order) */
static void print_in(No *r, int *primeiro) {
    if (!r) return;
    print_in(r->esquerda, primeiro);
    if (!*primeiro) putchar(' ');
    printf("%d", r->valor);
    *primeiro = 0;
    print_in(r->direita, primeiro);
}

/* impressão em pós-ordem */
static void print_post(No *r, int *primeiro) {
    if (!r) return;
    print_post(r->esquerda, primeiro);
    print_post(r->direita, primeiro);
    if (!*primeiro) putchar(' ');
    printf("%d", r->valor);
    *primeiro = 0;
}

/* libera todos os nós (post-order) */
static void free_tree(No *r) {
    if (!r) return;
    free_tree(r->esquerda);
    free_tree(r->direita);
    free(r);
}

int main(void) {
    int C;
    if (scanf("%d", &C) != 1) return 0;

    for (int tc = 1; tc <= C; ++tc) {
        int N;
        scanf("%d", &N);
        No *raiz = NULL;

        for (int i = 0; i < N; ++i) {
            int v; scanf("%d", &v);
            insere_Arvore(&raiz, v);
        }

        printf("Case %d:\n", tc);

        int primeiro;

        /* Pré-ordem */
        printf("Pre.: ");
        primeiro = 1;
        print_pre(raiz, &primeiro);
        putchar('\n');

        /* In-ordem */
        printf("In..: ");
        primeiro = 1;
        print_in(raiz, &primeiro);
        putchar('\n');

        /* Pós-ordem */
        printf("Post: ");
        primeiro = 1;
        print_post(raiz, &primeiro);
        putchar('\n');

        putchar('\n'); /* linha em branco após cada caso */

        free_tree(raiz);
    }

    return 0;
}