#include <stdio.h>

#define MAX 105 

int main() {
    int largura, altura; // X e Y
    char mapa[MAX][MAX];
    int visitado[MAX][MAX]; // Matriz para detectar loops

    scanf("%d", &largura);
    scanf("%d", &altura); 

    //Inicializa a matriz de visitados com 0
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            scanf(" %c", &mapa[i][j]);
            visitado[i][j] = 0;
        }
    }

    int r = 0, c = 0; // Linha e Coluna atuais
    int dr = 0, dc = 0; // Direção atual

    while (1) {
        // VERIFICAÇÃO DE LIMITES
        if (r < 0 || r >= altura || c < 0 || c >= largura) {
            printf("!\n");
            break;
        }

        if (visitado[r][c] == 1) {
            printf("!\n");
            break;
        }

        // Marca como visitado
        visitado[r][c] = 1;

        char celula = mapa[r][c];

        //  SUCESSO
        if (celula == '*') {
            printf("*\n");
            break;
        }

        // Se for '.', mantém a direção anterior (dr e dc não mudam)
        if (celula == '>') {
            dr = 0; dc = 1;
        } else if (celula == '<') {
            dr = 0; dc = -1;
        } else if (celula == 'v') {
            dr = 1; dc = 0;
        } else if (celula == '^') {
            dr = -1; dc = 0;
        }
        // MOVIMENTO
        r += dr;
        c += dc;
    }

    return 0;
}