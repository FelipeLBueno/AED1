#include <stdio.h>
#include <stdlib.h>

// Estrutura da pilha (stack)
typedef struct {
    char *dados; // buffer dinâmico que armazena os caracteres '('
    int topo;    // índice do próximo slot livre (ou tamanho atual)
    int cap;     // capacidade do buffer 'dados'
} Stack;

// Cria e inicializa uma pilha com 'capacidade' bytes.
// Retorna ponteiro para Stack alocada ou NULL em caso de falha.
static Stack *criar_Stack(int capacidade) {
    Stack *s = (Stack*) malloc(sizeof(Stack)); // aloca a estrutura Stack
    if (!s) return NULL;                       // falha na alocação -> retorna NULL
    s->dados = (char*) malloc(capacidade);     // aloca o buffer de caracteres
    if (!s->dados) { free(s); return NULL; }   // se falhar, libera e retorna NULL
    s->topo = 0;                               // inicialmente vazia
    s->cap = capacidade;                       // armazena capacidade
    return s;                                  // retorna a pilha criada
}

// Libera memória ocupada pela pilha
static void libera_Stack(Stack *s) {
    if (!s) return;        // se ponteiro nulo, não faz nada
    free(s->dados);        // libera o buffer de caracteres
    free(s);               // libera a estrutura
}

// Empilha um caractere 'c'.
// Retorna 1 em sucesso, 0 se ocorrer overflow (capacidade esgotada).
static int stack_push(Stack *s, char c) {
    if (s->topo >= s->cap) return 0; // overflow: sem espaço
    s->dados[s->topo++] = c;         // armazena o caractere e incrementa topo
    return 1;                        // sucesso
}

// Desempilha um caractere. Se 'out' != NULL, escreve o valor desempilhado em *out.
// Retorna 1 em sucesso, 0 em underflow (pilha vazia).
static int stack_pop(Stack *s, char *out) {
    if (s->topo == 0) return 0;      // underflow: nada para desempilhar
    s->topo--;                       // decrementa topo
    if (out) *out = s->dados[s->topo]; // entrega o valor desempilhado se solicitado
    return 1;                        // sucesso
}

// Limpa a pilha logicamente (mantém buffer alocado, zera topo)
static void limpa_Stack(Stack *s) { s->topo = 0; }

int main(void) {
    // Buffer para leitura de cada linha (limite do enunciado: até 1000 caracteres)
    char linha[1005];
    int capacidade = 1005;                   // capacidade para a pilha/buffer (1000+folga)
    Stack *stk = criar_Stack(capacidade);    // cria pilha dinâmica
    if (!stk) return 1;                      // erro de alocação -> finaliza com código 1

    // Lê linhas até EOF; cada linha é uma expressão a ser verificada
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        // Calcula o comprimento útil da linha, removendo '\n' e '\r' finais
        int comprimento = 0;
        while (linha[comprimento] != '\0' &&
               linha[comprimento] != '\n' &&
               linha[comprimento] != '\r') {
            comprimento++;
        }

        limpa_Stack(stk);  // esvazia a pilha para processar a nova linha
        int correto = 1;   // flag que indica se a linha está correta (parênteses balanceados)

        // Percorre cada caractere da linha e processa apenas '(' e ')'
        for (int i = 0; i < comprimento; ++i) {
            char ch = linha[i];
            if (ch == '(') {
                // Ao encontrar '(', empilha
                if (!stack_push(stk, ch)) {
                    // Se push falhar por overflow (não esperado), marca incorreto e sai
                    correto = 0;
                    break;
                }
            } else if (ch == ')') {
                // Ao encontrar ')', tenta desempilhar; se a pilha estiver vazia, é erro
                char temp;
                if (!stack_pop(stk, &temp)) {
                    // Underflow: encontrou ')' sem '(' correspondente
                    correto = 0;
                    break;
                }
            }
            // Outros caracteres são ignorados
        }

        // Se, ao final, restarem itens na pilha, há '(' sem fechar -> incorreto
        if (stk->topo != 0) correto = 0;

        // Imprime resultado conforme especificado: "correct" ou "incorrect"
        if (correto) printf("correct\n");
        else printf("incorrect\n");
    }

    libera_Stack(stk); // libera recursos antes de terminar
    return 0; 
}