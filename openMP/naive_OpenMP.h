#ifndef NAIVE_OPENMP_H
#define NAIVE_OPENMP_H

void matvec_open(int M, int N, int *row_ptr, int *col_indices, double *values);

#endif
