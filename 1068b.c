#include <stdio.h>
#include <stdlib.h>

/* Nó da lista encadeada usado como célula da pilha */
typedef struct Node {
    char val;           // valor armazenado (usamos apenas '(')
    struct Node *next;  // ponteiro para o próximo nó (topo -> head)
} Node;

/* Empilha um caractere: insere nó no início da lista.
   Retorna 1 em sucesso, 0 em falha de alocação. */
static int push(Node **head, char c) {
    Node *n = (Node*) malloc(sizeof(Node));
    if (!n) return 0;   // falha de alocação
    n->val = c;
    n->next = *head;
    *head = n;
    return 1;
}

/* Desempilha: remove nó do início da lista.
   Se out != NULL, escreve o valor desempilhado em *out.
   Retorna 1 em sucesso, 0 se a pilha estava vazia (underflow). */
static int pop(Node **head, char *out) {
    if (*head == NULL) return 0;  // underflow
    Node *n = *head;
    if (out) *out = n->val;
    *head = n->next;
    free(n);
    return 1;
}

/* Libera toda a lista (útil para limpar sobras ao final de uma linha) */
static void free_all(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    enum { MAX = 1005 };      // capacidade do buffer (1000 do enunciado + folga)
    char linha[MAX];

    /* Lê cada linha até EOF */
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        /* calcula comprimento útil removendo '\n' e '\r' finais */
        int len = 0;
        while (linha[len] != '\0' && linha[len] != '\n' && linha[len] != '\r') len++;

        Node *head = NULL;    // topo da pilha (lista vazia no início)
        int correto = 1;      // flag de validade

        for (int i = 0; i < len; ++i) {
            char ch = linha[i];
            if (ch == '(') {
                /* empilha '('; se malloc falhar, marca incorreto e sai */
                if (!push(&head, ch)) {
                    correto = 0;
                    break;
                }
            } else if (ch == ')') {
                /* tenta desempilhar; se estiver vazia => fechamento sem abertura */
                char tmp;
                if (!pop(&head, &tmp)) {
                    correto = 0;
                    break;
                }
            }
            /* outros caracteres são ignorados */
        }

        /* se ainda houver nós na lista => existem '(' sem fechar */
        if (head != NULL) correto = 0;

        /* libera qualquer nó restante (caso de erro) e evita vazamento */
        free_all(head);

        if (correto) printf("correct\n");
        else printf("incorrect\n");
    }

    return 0;
}
