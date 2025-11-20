#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *proximo;
} No;

// Função para inserir no final da lista
void inserir(No **lista, int n) {
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = n;
    novo->proximo = NULL;

    if (*lista == NULL) {
        // Se a lista está vazia, o novo nó é o primeiro
        *lista = novo;
    } else {
        // Se não, percorre até o último nó
        No *aux = *lista;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        // Conecta o novo nó ao final
        aux->proximo = novo;
    }
}

int main() {
    int N; // Número  de teste
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int M, C;
        scanf("%d %d", &M, &C); // M = endereços (base), C = quantidade de chaves

        No **tabela = (No **)calloc(M, sizeof(No *));

        for (int j = 0; j < C; j++) {
            int chave;
            scanf("%d", &chave);
            
            int endereco = chave % M;
            
            inserir(&tabela[endereco], chave);
        }
        // Impressão do resultado
        if (i > 0) {
            printf("\n");
        }

        for (int k = 0; k < M; k++) {
            printf("%d -> ", k);

            No *aux = tabela[k];
            while (aux != NULL) {
                printf("%d -> ", aux->valor);
                aux = aux->proximo;
            }
            // Imprime a barra invertida e pula linha
            printf("\\\n");
        }

        for (int k = 0; k < M; k++) {
            No *atual = tabela[k];
            while (atual != NULL) {
                No *temp = atual;
                atual = atual->proximo;
                free(temp);
            }
        }
        free(tabela);
    }

    return 0;
}