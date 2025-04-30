#ifndef CONVERT_H
#define CONVERT_H

void convert_to_CSR(int M, int N, int nz, int *I, int *J, double *val,
                    int **row_ptr, int **col_indices, double **values);

#endif
