#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    int contar;
    struct No *esquerda, *direita;
} No;

No* novoNo(int v) {
    No* n = (No*) malloc(sizeof(No));
    n->valor = v;
    n->contar = 1;
    n->esquerda = n->direita= NULL;
    return n;
}

/* Insere valor em ordem na árvore */
No* inserir(No* raiz, int v) {
    if (raiz == NULL) return novoNo(v);
    if (v < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, v);
    else if (v > raiz->valor)
        raiz->direita= inserir(raiz->direita, v);
    else
        raiz->contar++; // valor repetido
    return raiz;
}

/* impressão ordem crescente) */
void imprimir(No* raiz, int *primeiro) {
    if (!raiz) return;
    imprimir(raiz->esquerda, primeiro);
    for (int i = 0; i < raiz->contar; i++) {
        if (!*primeiro) printf(" ");
        printf("%d", raiz->valor);
        *primeiro = 0;
    }
    imprimir(raiz->direita, primeiro);
}

/* Libera memória */
void liberar(No* raiz) {
    if (!raiz) return;
    liberar(raiz->esquerda);
    liberar(raiz->direita);
    free(raiz);
}

int main() {
    int NC;
    scanf("%d", &NC);

    while (NC--) {
        int N;
        scanf("%d", &N);
        No* raiz = NULL;

        for (int i = 0; i < N; i++) {
            int h;
            scanf("%d", &h);
            raiz = inserir(raiz, h);
        }

        int primeiro = 1;
        imprimir(raiz, &primeiro);
        printf("\n");

        liberar(raiz);
    }

    return 0;
}
