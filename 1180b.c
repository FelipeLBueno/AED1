#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    int X[N];  // vetor normal para armazenar os valores
    int *p = X; //ponteiro que aponta para o início do vetor

    // leitura dos elementos usando ponteiro
    for (int i = 0; i < N; i++) {
        scanf("%d", (p + i));
    }

    int menor = *p;   // valor do primeiro elemento
    int pos = 0;

    // percorre usando ponteiro
    for (int i = 1; i < N; i++) {
        if (*(p + i) < menor) {   // acessa o valor com *(p+i)
            menor = *(p + i);
            pos = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", pos);

    return 0;
}