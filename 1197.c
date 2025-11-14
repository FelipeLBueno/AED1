#include <stdio.h>

int main(void) {
    int v, t;
    //para cada linha com dois inteiros v e t, imprime 2*v*t
    while (scanf("%d %d", &v, &t) == 2) {
        printf("%d\n", 2 * v * t);
    }
    return 0;
}