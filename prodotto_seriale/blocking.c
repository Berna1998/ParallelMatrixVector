#include <stdio.h>
#include <stdlib.h>
#include <blocking.h>

void spmv_ottimizzato(int M, int N, int *row_ptr, int *col_idx, double *values, double *x) {

    double *y = (double *)calloc(M, sizeof(double));
    int block_size = 128;

    // SpMV con blocking: calcola a blocchi di righe
    for (int i = 0; i < M; i += block_size) {
        int i_end = (i + block_size < M) ? i + block_size : M;
        for (int r = i; r < i_end; r++) {
            for (int j = row_ptr[r]; j < row_ptr[r + 1]; j++) {
                y[r] += values[j] * x[col_idx[j]];
            }
        }
    }
    
    printf("\nRisultato Seriale blocking y = A * x:\n");
    for (int i = 0; i < M; i++) {
        printf("%.4f ", y[i]);
    }
    printf("\n");

    free(y);
}

 
// Esempio di uso
void blocking(int M, int N, int *row_ptr, int *col_idx, double *values) {

    int NZ = sizeof(values);
    double *x = (double *)malloc(N * sizeof(double));


    // Inizializza x con tutti 1.0
    for (int i = 0; i < N; i++) x[i] = 1.0;

    // Ordina col_idx (e values) per riga per migliorare prefetching
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
    

    spmv_ottimizzato(M, N, row_ptr, col_idx, values,x);
    
    free(x);

}
    
