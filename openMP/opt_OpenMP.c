#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "opt_OpenMP.h"

void spmv_ottimizzato_open(int M, int N, int *row_ptr, int *col_idx, double *values, double *x) {

    double *y = (double *)calloc(M, sizeof(double));
    int block_size = 128;

    // Parallelizzazione sui blocchi di righe
    #pragma omp parallel for default(none) shared(M, block_size, row_ptr, col_idx, values, x, y)
    for (int i = 0; i < M; i += block_size) {
        int i_end = (i + block_size < M) ? i + block_size : M;
        for (int r = i; r < i_end; r++) {
            for (int j = row_ptr[r]; j < row_ptr[r + 1]; j++) {
                y[r] += values[j] * x[col_idx[j]];
            }
        }
    }

    printf("\nRisultato Parallelo OpenMP blocking y = A * x:\n");
    for (int i = 0; i < M; i++) {
        printf("%.4f ", y[i]);
    }
    printf("\n");

    free(y);
}

void blocking_open(int M, int N, int *row_ptr, int *col_idx, double *values) {
    double *x = (double *)malloc(N * sizeof(double));

    // Inizializza x con 1.0
    for (int i = 0; i < N; i++) x[i] = 1.0;

    // Ordinamento per riga (seriale, migliora prefetching)
    for (int i = 0; i < M; i++) {
        int start = row_ptr[i];
        int end = row_ptr[i + 1];

        for (int j = start; j < end - 1; j++) {
            for (int k = j + 1; k < end; k++) {
                if (col_idx[j] > col_idx[k]) {
                    int tmp_idx = col_idx[j];
                    col_idx[j] = col_idx[k];
                    col_idx[k] = tmp_idx;

                    double tmp_val = values[j];
                    values[j] = values[k];
                    values[k] = tmp_val;
                }
            }
        }
    }

    // Chiamata alla versione parallela
    spmv_ottimizzato_open(M, N, row_ptr, col_idx, values, x);
    
    free(x);
}

