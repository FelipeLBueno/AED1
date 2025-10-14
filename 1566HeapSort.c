#include <stdio.h>
#include <stdlib.h>

int getchar_unlocked(void);
int putchar_unlocked(int c);

/* Leitura rápida (usa getchar_unlocked quando disponível) */
static inline int fast_getchar(void) {
#if defined(_MSC_VER)
    return getchar();
#else
    return getchar_unlocked();
#endif
}

/* Lê próximo inteiro não-negativo do stdin; retorna -1 em EOF */
static int read_int(void) {
    int c = fast_getchar();
    while (c != EOF && (c < '0' || c > '9')) c = fast_getchar();
    if (c == EOF) return -1;
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = fast_getchar();
    }
    return x;
}

/* Escrita rápida (putchar_unlocked quando disponível) */
static inline void fast_putchar(int c) {
#if defined(_MSC_VER)
    putchar(c);
#else
    putchar_unlocked(c);
#endif
}

/* Escreve inteiro positivo seguido do separador 'sep' (sem usar printf). */
static void write_int_sep(int x, char sep) {
    char buf[16];
    int i = 0;
    if (x == 0) buf[i++] = '0';
    else {
        int tmp = x;
        char rev[16];
        int j = 0;
        while (tmp > 0) {
            rev[j++] = '0' + (tmp % 10);
            tmp /= 10;
        }
        while (j--) buf[i++] = rev[j];
    }
    for (int k = 0; k < i; ++k) fast_putchar(buf[k]);
    fast_putchar(sep);
}

/* ------------------ Heapsort (in-place) ------------------ */

/* Sift-down (heapify down) em a[start..end-1] assumindo que subárvores
   de start já são heaps; transforma a[start..end-1] em heap (max-heap raiz em start).
   end é exclusivo. */
static void sift_down(int *a, int start, int end) {
    int root = start;
    while (1) {
        int left = 2 * root + 1;   /* filho esquerdo */
        if (left >= end) break;    /* sem filhos */
        int right = left + 1;      /* filho direito */
        int swap_idx = root;

        /* escolhe o maior entre root, left, right */
        if (a[swap_idx] < a[left]) swap_idx = left;
        if (right < end && a[swap_idx] < a[right]) swap_idx = right;
        if (swap_idx == root) break; /* já heap */
        /* troca root <-> maior filho e continua descendo */
        int tmp = a[root];
        a[root] = a[swap_idx];
        a[swap_idx] = tmp;
        root = swap_idx;
    }
}

/* Constrói max-heap a[0..N-1] em O(N) */
static void build_max_heap(int *a, int N) {
    /* último pai = (N-2)/2; percorre de baixo para cima */
    for (int i = (N - 2) / 2; i >= 0; --i) {
        sift_down(a, i, N);
        if (i == 0) break; /* evita underflow do i ao decrementar (i é unsigned implícito) */
    }
}

/* Heapsort: ordena a[0..N-1] em ordem crescente (usa max-heap) */
static void heapsort(int *a, int N) {
    if (N <= 1) return;
    build_max_heap(a, N);        /* agora a[0] é o maior */
    /* extrai o máximo repetidamente */
    for (int end = N - 1; end > 0; --end) {
        /* move maior para a posição final */
        int tmp = a[0];
        a[0] = a[end];
        a[end] = tmp;
        /* restaura heap em a[0..end-1] */
        sift_down(a, 0, end);
    }
}

int main(void) {
    int NC = read_int();
    if (NC < 0) return 0;

    for (int case_i = 0; case_i < NC; ++case_i) {
        int N = read_int();
        if (N <= 0) {
            fast_putchar('\n');
            continue;
        }

        int *a = (int*) malloc((size_t)N * sizeof(int));
        if (!a) {
            fprintf(stderr, "malloc failed\n");
            return 1;
        }

        for (int i = 0; i < N; ++i) {
            int v = read_int();
            if (v < 0) v = 0;
            a[i] = v;
        }

        /* ordena com heapsort (in-place, O(N log N)) */
        heapsort(a, N);

        /* escreve resultado */
        for (int i = 0; i < N; ++i) {
            char sep = (i + 1 == N) ? '\n' : ' ';
            write_int_sep(a[i], sep);
        }

        free(a);
    }

    return 0;
}