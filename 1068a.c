#include <stdio.h>

int main(void) {
    /* buffer para leitura de linha e pilha estática.
       Supõe-se, conforme o enunciado, que cada linha tem no máximo 1000 caracteres. */
    enum { MAX = 1005 };
    char linha[MAX];
    char pilha[MAX];
    int topo; /* índice do topo da pilha (tamanho atual) */

    /* leitura até EOF */
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        /* calcula comprimento útil removendo '\n' e '\r' finais (tratamento CRLF compatível) */
        int len = 0;
        while (linha[len] != '\0' && linha[len] != '\n' && linha[len] != '\r') len++;

        topo = 0;       /* pilha vazia para cada nova linha */
        int correto = 1; /* flag de validade dos parênteses */

        for (int i = 0; i < len; ++i) {
            char ch = linha[i];
            if (ch == '(') {
                /* empilha: protege contra overflow (não esperado se MAX >= tamanho da linha) */
                if (topo >= MAX) { /* overflow de pilha -> marca incorreto e interrompe */
                    correto = 0;
                    break;
                }
                pilha[topo++] = ch;
            } else if (ch == ')') {
                /* desempilha: se pilha vazia -> underflow (fechamento sem abertura) */
                if (topo == 0) {
                    correto = 0;
                    break;
                }
                topo--; /* remove um '(' empilhado */
            }
            /* outros caracteres são ignorados */
        }

        /* se restaram '(' na pilha, há aberturas sem fechamento */
        if (topo != 0) correto = 0;

        if (correto) printf("correct\n");
        else printf("incorrect\n");
    }

    return 0;
}
