#include <stdio.h>
#include <stdlib.h>
#include "matvec_serial.h"

void matvec_serial(int M, int N, int *row_ptr, int *col_indices, double *values) {
    double *x = (double *)malloc(N * sizeof(double));
    double *y = (double *)calloc(M, sizeof(double));

    for (int i = 0; i < N; i++) x[i] = 1.0;

    for (int i = 0; i < M; i++) {
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; j++) {
            y[i] += values[j] * x[col_indices[j]];
        }
    }

    printf("\nRisultato Seriale basic y = A * x:\n");
    for (int i = 0; i < M; i++) {
        printf("%.4f ", y[i]);
    }
    printf("\n");

    free(x);
    free(y);
}
