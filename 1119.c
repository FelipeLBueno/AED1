#include <stdio.h>

// Função principal
int main() {
    int N, k, m;

    while (scanf("%d %d %d", &N, &k, &m) && N != 0) {
        
        // 1 significa que a pessoa está no círculo, 0 que foi removida
        int pessoas[25]; 
        for (int i = 1; i <= N; i++) {
            pessoas[i] = 1;
        }

        int restantes = N;
        // p1 (horário) começa virtualmente no N para que o primeiro passo caia no 1 (se k=1)
        int p1 = N; 
        // p2 (anti-horário) começa virtualmente no 1 para que o primeiro passo caia no N (se m=1)
        int p2 = 1;

        while (restantes > 0) {
            
            int contador = 0;
            while (contador < k) {
                p1++; 
                if (p1 > N) p1 = 1;
                
                if (pessoas[p1] == 1) {
                    contador++; // Só conta se a pessoa ainda estiver lá
                }
            }

            contador = 0;
            while (contador < m) {
                p2--; 
                if (p2 < 1) p2 = N; 
                if (pessoas[p2] == 1) {
                    contador++; // Só conta se a pessoa ainda estiver lá
                }
            }

            if (p1 != p2) {
                printf("%3d%3d", p1, p2);
                pessoas[p1] = 0; // Remove p1
                pessoas[p2] = 0; // Remove p2
                restantes -= 2;
            } 
            else {
                printf("%3d", p1);
                pessoas[p1] = 0; // Remove a única pessoa
                restantes -= 1;
            }

            // Se ainda houver pessoas, imprime a vírgula separadora
            if (restantes > 0) {
                printf(",");
            }
        }
        
        printf("\n");
    }

    return 0;
}