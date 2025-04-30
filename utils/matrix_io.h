#ifndef MATRIX_IO_H
#define MATRIX_IO_H

int load_matrix(const char *filename, int *M, int *N, int *nz, int **I, int **J, double **val);

#endif
