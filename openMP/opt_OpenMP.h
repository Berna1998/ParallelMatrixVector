#ifndef OPT_OPENMP_H
#define OPT_OPENMP_H

void spmv_ottimizzato_open(int M, int N, int *row_ptr, int *col_idx, double *values, double *x);
void blocking_open(int M, int N, int *row_ptr, int *col_indices, double *values);

#endif
