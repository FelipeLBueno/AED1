#include <stdio.h>

int main() {

    int n;

    scanf("%d", &n);    //Identifica o tamanho do vetor

    int V[n];   //cria o vetor com o tamanho solicitado

    for (int i = 0; i < n; i++) {
        scanf("%d", &V[i]);     //lê os valores e armazena no vetor
    }

    int menor = V[0];   //inicia o menor valor como o primeiro elemento do vetor
    int posicao = 0;    //inicia a primeira posição do vetor

    //percorre o vetor
    for (int i = 0; i < n; i++) {
        if (V[i] < menor) {
            menor = V[i];   //se achar valor menor, salva na memoria
            posicao = i;    //posicao do menor valor
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);

    return 0;
}