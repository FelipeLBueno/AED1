#include <stdio.h>

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    // consumir até o final da linha após o número 
    int c = getchar();
    while (c != '\n' && c != EOF) c = getchar();

    for (int i = 0; i < N; i++) {
        int abrir = 0;
        int diamantes = 0;

        /* ler a linha caractere a caractere */
        while (1) {
            c = getchar();
            if (c == EOF || c == '\n') {
                /* fim da linha (ou do arquivo) -> imprimimos e vamos para próxima */
                printf("%d\n", diamantes);
                break;
            }
            if (c == '\r') continue; // ignora CR em entradas

            if (c == '<') {
                abrir++;
            } else if (c == '>') {
                if (abrir > 0) {
                    diamantes++;
                    abrir--;
                }
            }
        }

        if (c == EOF && i < N-1) {
            // se EOF inesperado, saímos cedo
            break;
        }
    }

    return 0;
}
