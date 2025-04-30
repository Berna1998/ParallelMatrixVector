#include <stdio.h>
#include <stdlib.h>
#include "convert.h"

void convert_to_CSR(int M, int N, int nz, int *I, int *J, double *val,
                    int **row_ptr, int **col_indices, double **values) {
    *row_ptr = (int *)calloc(M + 1, sizeof(int));
    *col_indices = (int *)malloc(nz * sizeof(int));
    *values = (double *)malloc(nz * sizeof(double));

    for (int i = 0; i < nz; i++) {
        (*row_ptr)[I[i] + 1]++;
    }

    for (int i = 0; i < M; i++) {
        (*row_ptr)[i + 1] += (*row_ptr)[i];
    }

    int *temp = (int *)malloc(M * sizeof(int));
    for (int i = 0; i < M; i++) temp[i] = (*row_ptr)[i];

    for (int i = 0; i < nz; i++) {
        int row = I[i];
        int dest = temp[row]++;
        (*col_indices)[dest] = J[i];
        (*values)[dest] = val[i];
    }
    free(temp);

    // Debug output
    printf("\nFormato CSR:\n");
    printf("Row pointers (IRP): ");
    for (int i = 0; i <= M; i++) printf("%d ", (*row_ptr)[i]);
    printf("\nCol indices (JA): ");
    for (int i = 0; i < nz; i++) printf("%d ", (*col_indices)[i]);
    printf("\nValues (AS): ");
    for (int i = 0; i < nz; i++) printf("%.2f ", (*values)[i]);
    printf("\n");
}
