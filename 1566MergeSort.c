#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getchar_unlocked();
int putchar_unlocked(int c);

/* Leitura rápida: getchar_unlocked quando disponível (Linux/gcc). */
static inline int fast_getchar(void) {
#if defined(_MSC_VER)
    return getchar();          /* fallback no Windows/MSVC */
#else
    return getchar_unlocked();
#endif
}

/* Lê próximo inteiro não-negativo do stdin; retorna -1 em EOF. */
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

/* Escrita rápida: putchar_unlocked quando disponível. */
static inline void fast_putchar(int c) {
#if defined(_MSC_VER)
    putchar(c);
#else
    putchar_unlocked(c);
#endif
}

/* Escreve um inteiro positivo seguido do separador 'sep' (sem usar printf). */
static void write_int_sep(int x, char sep) {
    char buf[16];
    int i = 0;
    if (x == 0) buf[i++] = '0';
    else {
        int tmp = x, j = 0;
        char rev[16];
        while (tmp > 0) {
            rev[j++] = '0' + (tmp % 10);
            tmp /= 10;
        }
        while (j--) buf[i++] = rev[j];
    }
    for (int k = 0; k < i; ++k) fast_putchar(buf[k]);
    fast_putchar(sep);
}

/* Merge: combina dois segmentos ordenados a[l..m-1] e a[m..r-1] usando 'aux'.
   Observação: usa indices [l, r) (meio m). */
static void merge_range(int *a, int *aux, int l, int m, int r) {
    int i = l;    /* cursor do primeiro segmento */
    int j = m;    /* cursor do segundo segmento */
    int k = l;    /* posição de escrita em aux */

    /* intercala em aux */
    while (i < m && j < r) {
        if (a[i] <= a[j]) aux[k++] = a[i++];
        else aux[k++] = a[j++];
    }
    while (i < m) aux[k++] = a[i++];
    while (j < r) aux[k++] = a[j++];

    /* copia de volta para a[l..r-1] */
    for (k = l; k < r; ++k) a[k] = aux[k];
}

/* Merge sort recursivo em a[l..r-1], usando buffer auxiliar aux do mesmo tamanho de a */
static void merge_sort_rec(int *a, int *aux, int l, int r) {
    /* segmento vazio ou unitário já está ordenado */
    if (r - l <= 1) return;
    int m = l + ((r - l) >> 1);
    merge_sort_rec(a, aux, l, m);
    merge_sort_rec(a, aux, m, r);
    /* se já estiver ordenado, podemos evitar o merge (pequuna otimização) */
    if (a[m - 1] <= a[m]) return;
    merge_range(a, aux, l, m, r);
}

int main(void) {
    int NC = read_int();
    if (NC < 0) return 0;

    for (int case_i = 0; case_i < NC; ++case_i) {
        int N = read_int();
        if (N <= 0) {
            /* caso improvável segundo o enunciado; apenas imprime nova linha */
            fast_putchar('\n');
            continue;
        }

        /* aloca vetor de N inteiros e buffer auxiliar (mesmo tamanho) */
        int *a = (int*) malloc((size_t)N * sizeof(int));
        if (!a) { fprintf(stderr, "malloc falhou\n"); return 1; }
        int *aux = (int*) malloc((size_t)N * sizeof(int));
        if (!aux) { free(a); fprintf(stderr, "malloc falhou\n"); return 1; }

        for (int i = 0; i < N; ++i) {
            int v = read_int();
            if (v < 0) v = 0;
            a[i] = v;
        }

        /* ordena com merge sort (estável, O(N log N)) */
        merge_sort_rec(a, aux, 0, N);

        /* imprime a linha ordenada: separa por espaço, termina com '\n' */
        for (int i = 0; i < N; ++i) {
            char sep = (i + 1 == N) ? '\n' : ' ';
            write_int_sep(a[i], sep);
        }

        free(a);
        free(aux);
    }

    return 0;
}