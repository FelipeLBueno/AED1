#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void heap_push(int *heap, int *hsize, int val) {
    int i = (*hsize)++;
    heap[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] >= heap[i]) break;
        int tmp = heap[p]; heap[p] = heap[i]; heap[i] = tmp;
        i = p;
    }
}

static int heap_pop(int *heap, int *hsize, bool *empty) {
    if (*hsize == 0) { *empty = true; return -1; }
    int ret = heap[0];
    (*hsize)--;
    heap[0] = heap[*hsize];
    int i = 0;
    while (1) {
        int l = 2*i + 1;
        int r = 2*i + 2;
        int largest = i;
        if (l < *hsize && heap[l] > heap[largest]) largest = l;
        if (r < *hsize && heap[r] > heap[largest]) largest = r;
        if (largest == i) break;
        int tmp = heap[i]; heap[i] = heap[largest]; heap[largest] = tmp;
        i = largest;
    }
    *empty = false;
    return ret;
}

int main(void) {
    int n;
    while (scanf("%d", &n) == 1) {
        /* aloca dinamicamente com capacidade n (cada caso tem no máximo n pushes) */
        int *st = (int*) malloc(n * sizeof(int));
        int *qu = (int*) malloc(n * sizeof(int));
        int *heap = (int*) malloc(n * sizeof(int));
        if (!st || !qu || !heap) {
            /* falha em alocar — aborta */
            fprintf(stderr, "Allocation error\n");
            return 1;
        }

        int st_top = 0;
        int q_head = 0, q_tail = 0;
        int hsize = 0;

        bool isStack = true, isQueue = true, isPq = true;

        for (int i = 0; i < n; ++i) {
            int cmd, x;
            if (scanf("%d %d", &cmd, &x) != 2) {
                /* entrada inesperada; marca tudo impossível e segue */
                isStack = isQueue = isPq = false;
                continue;
            }

            if (cmd == 1) {
                /* push / enqueue / heap push */
                if (st_top < n) st[st_top++] = x;
                if (q_tail < n) qu[q_tail++] = x;
                if (hsize < n) heap_push(heap, &hsize, x);
            } else if (cmd == 2) {
                /* pop stack */
                if (st_top == 0) {
                    isStack = false;
                } else {
                    int v = st[--st_top];
                    if (v != x) isStack = false;
                }

                /* dequeue queue */
                if (q_head == q_tail) {
                    isQueue = false;
                } else {
                    int v = qu[q_head++];
                    if (v != x) isQueue = false;
                }

                /* pop heap (max-heap) */
                bool empty;
                int v = heap_pop(heap, &hsize, &empty);
                if (empty) {
                    isPq = false;
                } else {
                    if (v != x) isPq = false;
                }
            } else {
                /* comando inválido — ignora (marca impossível por segurança) */
                isStack = isQueue = isPq = false;
            }
        }

        int possible = (isStack ? 1 : 0) + (isQueue ? 1 : 0) + (isPq ? 1 : 0);
        if (possible == 0) puts("impossible");
        else if (possible > 1) puts("not sure");
        else {
            if (isStack) puts("stack");
            else if (isQueue) puts("queue");
            else puts("priority queue");
        }

        free(st);
        free(qu);
        free(heap);
    }
    return 0;
}