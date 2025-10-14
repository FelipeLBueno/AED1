#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getchar_unlocked(void);
int putchar_unlocked(int c);

/* leitura rápida (getchar_unlocked quando disponível) */
static inline int fast_getchar(void) {
#if defined(_MSC_VER)
    return getchar();
#else
    return getchar_unlocked();
#endif
}

/* lê próximo inteiro não-negativo; retorna -1 em EOF */
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

/* escrita rápida de caractere */
static inline void fast_putchar(int c) {
#if defined(_MSC_VER)
    putchar(c);
#else
    putchar_unlocked(c);
#endif
}

/* escreve inteiro positivo seguido do separador 'sep' */
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

/* ------------------ QuickSort otimizado ------------------ */

/* limiar abaixo do qual usamos insertion sort (mais eficiente em blocos pequenos) */
enum { INSERTION_CUTOFF = 16 };

/* troca dois inteiros */
static inline void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

/* insertion sort em a[l..r-1] */
static void insertion_sort(int *a, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= l && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

/* escolhe pivot usando median-of-three entre posições l, m, r-1 e retorna o valor do pivô
   além de colocar elementos de forma que a[l] <= a[m] <= a[r-1] (apenas por comparação) */
static int median_of_three(int *a, int l, int r) {
    int m = l + ((r - l) >> 1);
    /* ordena trid de forma parcial */
    if (a[l] > a[m]) swap_int(&a[l], &a[m]);
    if (a[m] > a[r - 1]) swap_int(&a[m], &a[r - 1]);
    if (a[l] > a[m]) swap_int(&a[l], &a[m]);
    /* agora a[l] <= a[m] <= a[r-1], escolhemos a[m] como pivô */
    return a[m];
}

/* partição Hoare em [l, r) com pivô dado; retorna índice j tal que
   todos elementos em [l..j] <= pivot e em [j+1..r-1] >= pivot (j pode ser < l ou >= r-1 em casos extremos).
   Implementação baseada no esquema de Hoare, usando índices i e j. */
static int hoare_partition(int *a, int l, int r, int pivot) {
    int i = l - 1;
    int j = r;
    while (1) {
        /* avança i até achar a[i] >= pivot */
        do { ++i; } while (a[i] < pivot);
        /* decrementa j até achar a[j] <= pivot */
        do { --j; } while (a[j] > pivot);
        if (i >= j) return j;
        swap_int(&a[i], &a[j]);
    }
}

/* QuickSort recursivo otimizado (usa tail recursion elimination).
   Ordena a[l..r-1]. */
static void quick_sort_rec(int *a, int l, int r) {
    while (r - l > INSERTION_CUTOFF) {
        /* escolhe pivô com median-of-three para reduzir chances de pior caso */
        int pivot = median_of_three(a, l, r);
        /* partição Hoare */
        int p = hoare_partition(a, l, r, pivot);
        /* agora p é o índice final da partição (todos <= pivot em [l..p], >= pivot em [p+1..r-1]) */

        /* recursa na partição menor e itera na maior (elimina recursion depth) */
        if (p - l < r - (p + 1)) {
            quick_sort_rec(a, l, p + 1);  /* esquerda menor: [l..p] */
            l = p + 1;                    /* itera sobre direita maior */
        } else {
            quick_sort_rec(a, p + 1, r);  /* direita menor: [p+1..r-1] */
            r = p + 1;                    /* itera sobre esquerda maior */
        }
    }
    /* para partições pequenas, usa insertion sort (mais rápido) */
    if (r - l > 1) insertion_sort(a, l, r);
}

/* wrapper */
static void quick_sort(int *a, int N) {
    if (N <= 1) return;
    quick_sort_rec(a, 0, N);
}

/* ------------------------------------------------------- */

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
        if (!a) { fprintf(stderr, "malloc failed\n"); return 1; }

        for (int i = 0; i < N; ++i) {
            int v = read_int();
            if (v < 0) v = 0;
            a[i] = v;
        }

        /* ordena com quicksort otimizado */
        quick_sort(a, N);

        /* imprime resultado */
        for (int i = 0; i < N; ++i) {
            char sep = (i + 1 == N) ? '\n' : ' ';
            write_int_sep(a[i], sep);
        }

        free(a);
    }

    return 0;
}