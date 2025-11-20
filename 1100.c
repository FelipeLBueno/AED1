#include <stdio.h>
#include <string.h>

// Estrutura para representar uma posição no tabuleiro
typedef struct {
    int l; // Linha (0 a 7)
    int c; // Coluna (0 a 7)
    int dist; // Distância a partir da origem
} Ponto;

// Arrays de deslocamento para os 8 movimentos possíveis do cavalo
int dr[] = {-2, -2, -1, -1,  1,  1,  2,  2};
int dc[] = {-1,  1, -2,  2, -2,  2, -1,  1};

int main() {
    char s1[5], s2[5];

    while (scanf("%s %s", s1, s2) != EOF) {
        
        // Converte a notação do xadrez para coordenadas da matriz (0-7)
        int comecaColuna = s1[0] - 'a';
        int comecaLinha = s1[1] - '1';
        int fimColuna = s2[0] - 'a';
        int fimLinha = s2[1] - '1';

        int visitado[8][8];
        // Zera a matriz de visitados
        memset(visitado, 0, sizeof(visitado));

        Ponto fila[200];
        int inicio = 0, fim = 0;

        // Insere o ponto inicial na fila
        Ponto inicial;
        inicial.l = comecaLinha;
        inicial.c = comecaColuna;
        inicial.dist = 0;
        
        fila[fim++] = inicial;
        visitado[comecaLinha][comecaColuna] = 1;

        int movimentos = 0;

        // Loop da BFS
        while (inicio < fim) {
            Ponto atual = fila[inicio++]; // Remove da fila

            // Se chegamos ao destino
            if (atual.l == fimLinha && atual.c == fimColuna) {
                movimentos = atual.dist;
                break;
            }

            // Tenta todos os 8 movimentos possíveis
            for (int i = 0; i < 8; i++) {
                int nr = atual.l + dr[i];
                int nc = atual.c + dc[i];

                // Verifica se a nova posição está DENTRO do tabuleiro e NÃO foi visitada
                if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && !visitado[nr][nc]) {
                    visitado[nr][nc] = 1;
                    
                    Ponto proximo;
                    proximo.l = nr;
                    proximo.c = nc;
                    proximo.dist = atual.dist + 1;
                    
                    fila[fim++] = proximo; // Insere na fila
                }
            }
        }

        printf("To get from %s to %s takes %d knight moves.\n", s1, s2, movimentos);
    }

    return 0;
}