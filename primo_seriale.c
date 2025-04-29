#include <stdio.h>

int main() {

    int A[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    int v[3] = {1, 2, 3};

    int result[3] = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i] = A[i][j] * v[j];
        }
    }

    printf("Risultato del prodotto matrice-vettore:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}

