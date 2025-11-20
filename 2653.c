#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tamanhos máximos baseados nas restrições do problema
#define MAX_BUFFER 1000005 // 10^6 + margem de segurança
#define MAX_JOIAS 100005   // Estimativa de quantidade máxima de strings distintas

// Função de comparação usada pelo qsort
int comparar(const void *a, const void *b) {
    const char **str_a = (const char **)a;
    const char **str_b = (const char **)b;
    return strcmp(*str_a, *str_b);
}

// Declaração global para não estourar a memória
char buffer[MAX_BUFFER]; 
char *lista_joias[MAX_JOIAS]; 

int main() {
    int total_joias = 0;

    // Lê strings até o fim do arquivo (EOF)
    while (scanf("%s", buffer) != EOF) {
        // Aloca memória do tamanho da string 
        lista_joias[total_joias] = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        
        // Copia do buffer temporário para a memória alocada
        strcpy(lista_joias[total_joias], buffer);
        total_joias++;
    }

    // Se não houver joias, a resposta é 0
    if (total_joias == 0) {
        printf("0\n");
        return 0;
    }

    // Ordena o array de strings alfabeticamente
    qsort(lista_joias, total_joias, sizeof(char *), comparar);

    // CONTAGEM DE ÚNICOS
    int distintos = 1; // Começamos com 1 porque a primeira joia é sempre única
    
    for (int i = 1; i < total_joias; i++) {
        // Se a joia atual for diferente da anterior, incrementamos o contador
        if (strcmp(lista_joias[i], lista_joias[i-1]) != 0) {
            distintos++;
        }
    }

    printf("%d\n", distintos);
    
    for(int i=0; i<total_joias; i++) {
        free(lista_joias[i]);
    }

    return 0;
}