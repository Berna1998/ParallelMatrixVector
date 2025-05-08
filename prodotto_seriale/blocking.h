#ifndef BLOCKING_H
#define BLOCKING_H

void spmv_ottimizzato(int M, int N, int *row_ptr, int *col_idx, double *values, double *x);
void blocking(int M, int N, int *row_ptr, int *col_indices, double *values);

#endif
