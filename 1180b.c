#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int V[n];  // vetor normal para armazenar os valores
    int *p = V; //ponteiro que aponta para o início do vetor

    // leitura dos elementos usando ponteiro
    for (int i = 0; i < n; i++) {
        scanf("%d", (p + i));
    }

    int menor = *p;   // valor do primeiro elemento
    int posicao = 0;

    // percorre usando ponteiro
    for (int i = 1; i < n; i++) {
        if (*(p + i) < menor) {   // acessa o valor com *(p+i)
            menor = *(p + i);
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);

    return 0;

}
