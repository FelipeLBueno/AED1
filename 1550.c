#include <stdio.h>
#include <string.h>

int reverso(int x) {
    int r = 0;
    while (x > 0) {
        r = r * 10 + (x % 10);
        x /= 10;
    }
    return r;
}

int main(void) {
    int T;
    if (scanf("%d", &T) != 1) return 0;

    while (T--) {
        int A, B;
        if (scanf("%d %d", &A, &B) != 2) return 0;

        if (A == B) {
            printf("0\n");
            continue;
        }

        int distancia[10000];
        int q[10000];
        memset(distancia, -1, sizeof(distancia));

        int cabeca = 0, fim = 0;
        distancia[A] = 0;
        q[fim++] = A;

        while (cabeca < fim) {
            int atual = q[cabeca++];
            int d = distancia[atual];

            /* operação +1 */
            int proximo = atual + 1;
            if (proximo <= 9999 && distancia[proximo] == -1) {
                distancia[proximo] = d + 1;
                if (proximo == B) { printf("%d\n", distancia[proximo]); break; }
                q[fim++] = proximo;
            }

            /* operação inverter dígitos */
            proximo = reverso(atual);
            if (distancia[proximo] == -1) {
                distancia[proximo] = d + 1;
                if (proximo == B) { printf("%d\n", distancia[proximo]); break; }
                q[fim++] = proximo;
            }
        }
        
        if (distancia[B] != -1) continue;
        printf("%d\n", distancia[B]);
    }

    return 0;
}