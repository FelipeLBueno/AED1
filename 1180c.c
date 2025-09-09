#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    size_t n;
    scanf("%zu", &n);

    //alocação dinâmica de memória genérica
    void *V = malloc(n * sizeof(long));
    if (V == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return 1;
    }

    //Leitura dos valores 
    for (size_t i = 0; i < n; i++) {
        scanf("%ld", (long *)V + i);
    }

    //inicializa menor e posição
    long menor = *((long *)V);  
    size_t posicao = 0;

    // busca o menor valor
    for (size_t i = 1; i < n; i++) {
        long valor = *((long *)V + i);
        if (valor < menor) {
            menor = valor;
            posicao = i;
        }
    }

    printf("Menor valor: %ld\n", menor);
    printf("Posicao: %zu\n", posicao);

    free(V);
    return 0;
}