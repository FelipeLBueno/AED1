#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main() {
    int N;
    char entrada[MAX], saida[MAX];
    char pilha[MAX];

    // Lê N. Se N for 0, o programa encerra.
    while (scanf("%d", &N) && N != 0) {
        
        // Leitura da sequência de entrada (Lado A)
        for (int i = 0; i < N; i++) {
            scanf(" %c", &entrada[i]);
        }

        // Leitura da sequência desejada (Lado B)
        for (int i = 0; i < N; i++) {
            scanf(" %c", &saida[i]);
        }

        int topo = -1;      // Índice do topo da pilha
        int j = 0;          // Índice para percorrer a sequência de saída (B)
        
        // Percorre a sequência de entrada (A)
        for (int i = 0; i < N; i++) {
            // 1. INSERE (Push) o vagão na estação
            pilha[++topo] = entrada[i];
            printf("I"); 

            // 2. REMOVE (Pop) enquanto o topo for igual ao necessário na saída
            while (topo >= 0 && pilha[topo] == saida[j]) {
                topo--; // Remove da pilha
                j++;    // Avança para o próximo vagão esperado
                printf("R");
            }
        }

        // Se ao final a pilha não estiver vazia, significa que não foi possível
        // esvaziar a estação na ordem correta.
        if (topo != -1) {
            printf(" Impossible");
        }

        printf("\n");
    }

    return 0;
}