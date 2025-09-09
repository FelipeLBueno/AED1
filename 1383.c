#include <stdio.h>

int valido(int matriz[9][9]) {
    int i, j, k, l;

    // Verifica linhas
    for (i = 0; i < 9; i++) {
        int freq[10] = {0};
        for (j = 0; j < 9; j++) {
            int num = matriz[i][j];
            if (num < 1 || num > 9 || freq[num]) return 0;
            freq[num] = 1;
        }
    }

    // Verifica colunas
    for (j = 0; j < 9; j++) {
        int freq[10] = {0};
        for (i = 0; i < 9; i++) {
            int num = matriz[i][j];
            if (num < 1 || num > 9 || freq[num]) return 0;
            freq[num] = 1;
        }
    }

    // Verifica submatrizes 3x3
    for (i = 0; i < 9; i += 3) {
        for (j = 0; j < 9; j += 3) {
            int freq[10] = {0};
            for (k = 0; k < 3; k++) {
                for (l = 0; l < 3; l++) {
                    int num = matriz[i + k][j + l];
                    if (num < 1 || num > 9 || freq[num]) return 0;
                    freq[num] = 1;
                }
            }
        }
    }

    return 1; // passou em todas as verificações
}

int main() {
    int n, inst = 1;
    scanf("%d", &n);

    while (n--) {
        int matriz[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                scanf("%d", &matriz[i][j]);
            }
        }

        printf("Instancia %d\n", inst++);
        if (valido(matriz)) {
            printf("SIM\n\n");
        } else {
            printf("NAO\n\n");
        }
    }

    return 0;
}
