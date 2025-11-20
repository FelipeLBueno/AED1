#include <stdio.h>

#define MAX 105 // Margem de segurança para a matriz

int main() {
    int N, M;
    int tabuleiro[MAX][MAX];

    // Lê enquanto houver entrada (EOF)
    while (scanf("%d %d", &N, &M) != EOF) {
        
        // 1. Leitura da matriz
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf("%d", &tabuleiro[i][j]);
            }
        }

        // 2. Processamento e Saída
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                
                // Regra: Se tem pão de queijo (1), imprime 9
                if (tabuleiro[i][j] == 1) {
                    printf("9");
                } 
                else {
                    // Se não tem (0), conta os vizinhos adjacentes
                    int adjacentes = 0;

                    // Verifica CIMA (i-1) - Só se não for a primeira linha
                    if (i > 0 && tabuleiro[i-1][j] == 1) 
                        adjacentes++;

                    // Verifica BAIXO (i+1) - Só se não for a última linha
                    if (i < N - 1 && tabuleiro[i+1][j] == 1) 
                        adjacentes++;

                    // Verifica ESQUERDA (j-1) - Só se não for a primeira coluna
                    if (j > 0 && tabuleiro[i][j-1] == 1) 
                        adjacentes++;

                    // Verifica DIREITA (j+1) - Só se não for a última coluna
                    if (j < M - 1 && tabuleiro[i][j+1] == 1) 
                        adjacentes++;

                    printf("%d", adjacentes);
                }
            }
            // Quebra de linha ao final de cada linha da matriz
            printf("\n");
        }
    }

    return 0;
}