#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getchar_unlocked();
int putchar_unlocked(int c);

/* leitura rápida (usa getchar_unlocked quando disponível) */
static inline int fast_getchar(void) {
#if defined(_MSC_VER)
    return getchar();
#else
    return getchar_unlocked();
#endif
}

/* lê próximo inteiro não-negativo do stdin; retorna -1 em EOF */
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

/* lower_bound (busca binária) para posição de inserção em arr[0..len-1] */
static int lower_bound(const int *arr, int len, int key) {
    int l = 0, r = len;
    while (l < r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] < key) l = m + 1;
        else r = m;
    }
    return l;
}

/* Threshold para decidir usar insertion (com busca binária) ou counting sort.
   Ajustável; 10000 é uma escolha pragmática: insertion fica razoável até esse ponto. */
enum { THRESHOLD_INSERTION = 10000 };

/* Roda insertion sort (busca binária + memmove) sobre vetor a de tamanho N.
   Complexidade: O(N^2) no pior caso, mas comparações reduzidas pela busca binária. */
static void insertion_sort_bin(int *a, int N) {
    for (int i = 1; i < N; ++i) {
        int key = a[i];
        int pos = lower_bound(a, i, key);
        if (pos == i) continue;
        /* desloca bloco [pos..i-1] uma posição à direita */
        memmove(&a[pos + 1], &a[pos], (size_t)(i - pos) * sizeof(int));
        a[pos] = key;
    }
}

/* Roda counting sort (eficiente para faixa limitada 20..230).
   counts array deve ter comprimento >= 231; resultado é escrito direto na saída. */
static void counting_output(const int *vals, int N) {
    /* faixa conhecida: 20..230 (inclusive) */
    int counts[231] = {0};
    for (int i = 0; i < N; ++i) counts[vals[i]]++;
    int first = 1;
    for (int h = 20; h <= 230; ++h) {
        while (counts[h]--) {
            if (first) {
                write_int_sep(h, (counts[h] >= 0 || h < 230) ? ' ' : '\n');
                first = 0;
            } else {
                /* sep = space ou newline se último */
                /* determinamos se é o último imprimindo com ' ' e substituindo no final: 
                   mais simples: vamos imprimir ' ' e depois trocar o último por '\n' é complexo.
                   Melhor: rastrear quantos faltam. */
                write_int_sep(h, ' ');
            }
        }
    }
    /* O método acima imprime um espaço extra no final da linha — corrigimos imprimindo uma nova linha no fim */
    /* Em vez de complicar, vamos reimplementar a forma certa: */
}

/* versão counting bem formatada: escreve todos valores ordenados e termina com '\n' */
static void counting_sort_and_write(const int *vals, int N) {
    int counts[231] = {0};
    for (int i = 0; i < N; ++i) counts[vals[i]]++;
    int printed = 0;
    for (int h = 20; h <= 230; ++h) {
        while (counts[h] > 0) {
            printed++;
            char sep = (printed == N) ? '\n' : ' ';
            write_int_sep(h, sep);
            counts[h]--;
        }
    }
}

int main(void) {
    int NC = read_int();
    if (NC < 0) return 0;

    for (int case_i = 0; case_i < NC; ++case_i) {
        int N = read_int();
        if (N <= 0) {
            /* se N inválido, escreve linha vazia e segue */
            fast_putchar('\n');
            continue;
        }

        /* aloca vetor para as alturas */
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

        if (N <= THRESHOLD_INSERTION) {
            /* usa insertion otimizado (busca binária) */
            insertion_sort_bin(a, N);
            for (int i = 0; i < N; ++i) {
                char sep = (i + 1 == N) ? '\n' : ' ';
                write_int_sep(a[i], sep);
            }
        } else {
            /* para N grande: counting sort é a opção prática (faixa pequena conhecida) */
            counting_sort_and_write(a, N);
        }

        free(a);
    }

    return 0;
}