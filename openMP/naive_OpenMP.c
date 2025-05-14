#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "naive_OpenMP.h"

void matvec_open(int M, int N, int *row_ptr, int *col_indices, double *values) {
    double *x = (double *)malloc(N * sizeof(double));
    double *y = (double *)calloc(M, sizeof(double));

    // Inizializzazione vettore x (seriale)
    for (int i = 0; i < N; i++) x[i] = 1.0;

    // Prodotto matrice-vettore parallelo
    #pragma omp parallel for shared(M, row_ptr, col_indices, values, x, y) default(none)
    for (int i = 0; i < M; i++) {
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; j++) {
            y[i] += values[j] * x[col_indices[j]];
        }
    }

    // Stampa del risultato
    printf("\nRisultato Naive OpenMP y = A * x:\n");
    for (int i = 0; i < M; i++) {
        printf("%.4f ", y[i]);
    }
    printf("\n");

    free(x);
    free(y);
}

