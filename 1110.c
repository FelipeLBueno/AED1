#include <stdio.h>
#include <stdlib.h>

/* Fil a circular simples baseada em vetor.
   Capacidade é n+5 para evitar ambiguidades entre cabeça/cauda. */
typedef struct {
    int *data;
    int cap;   /* capacidade física do buffer */
    int cabeca;  /* índice do primeiro elemento */
    int cauda;  /* índice logo após o último elemento */
} fila;

/* cria fila com capacidade 'cap' */
static fila *criar_Fila(int cap) {
    fila *q = (fila*) malloc(sizeof(fila));
    if (!q) return NULL;
    q->data = (int*) malloc(sizeof(int) * cap);
    if (!q->data) { free(q); return NULL; }
    q->cap = cap;
    q->cabeca = 0;
    q->cauda = 0;
    return q;
}

/* libera fila */
static void free_Fila(fila *q) {
    if (!q) return;
    free(q->data);
    free(q);
}

/* retorna 1 se vazia */
static int fila_Vazia(const fila *q) {
    return q->cabeca == q->cauda;
}

/* quantidade de elementos */
static int tamanho_Fila(const fila *q) {
    int s = q->cauda - q->cabeca;
    if (s < 0) s += q->cap;
    return s;
}

/* enfileira valor (assume espaço suficiente) */
static void enqueue(fila *q, int v) {
    q->data[q->cauda] = v;
    q->cauda++;
    if (q->cauda == q->cap) q->cauda = 0;
}

/* desenfileira e retorna valor; chama somente se !empty */
static int dequeue(fila *q) {
    int v = q->data[q->cabeca];
    q->cabeca++;
    if (q->cabeca == q->cap) q->cabeca = 0;
    return v;
}

int main(void) {
    int n;
    while ( (scanf("%d", &n) == 1) ) {
        if (n == 0) break; /* fim dos casos */
        if (n == 1) {
            /* caso trivial: nenhuma carta descartada */
            printf("Discarded cards:\n");
            printf("Remaining card: 1\n");
            continue;
        }

        /* capacidade: n + 5 para folga (evita colisão cabeca==cauda) */
        fila *q = criar_Fila(n + 5);
        if (!q) return 1;

        /* inicializa fila com 1..n (1 no topo) */
        for (int i = 1; i <= n; ++i) enqueue(q, i);

        /* armazenamos os descartes em um vetor para formatar depois */
        int *discarded = (int*) malloc(sizeof(int) * n); /* no máximo n-1 descartes */
        int dcount = 0;

        /* processo: repetir enquanto tiver 2 ou mais cartas */
        while (tamanho_Fila(q) > 1) {
            /* descarte a carta do topo */
            int top = dequeue(q);
            discarded[dcount++] = top;

            /* mova a próxima carta para a base (se existir) */
            if (!fila_Vazia(q)) {
                int next = dequeue(q);
                enqueue(q, next);
            }
        }

        /* imprime descartadas formatadas: "Discarded cards: " + lista separada por ", " */
        if (dcount == 0) {
            printf("Discarded cards:\n");
        } else {
            printf("Discarded cards: ");
            for (int i = 0; i < dcount; ++i) {
                if (i) printf(", ");
                printf("%d", discarded[i]);
            }
            printf("\n");
        }

        /* imprime a carta que restou */
        int remaining = fila_Vazia(q) ? -1 : dequeue(q);
        printf("Remaining card: %d\n", remaining);

        free(discarded);
        free_Fila(q);
    }
    return 0;
}