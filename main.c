#include <stdio.h>
#include <stdlib.h>
#include "utils/matrix_io.h"
#include "utils/convert.h"

#ifdef USE_OPENMP
#include "openMP/naive_OpenMP.h"
#include "openMP/opt_OpenMP.h"
#else
#include "prodotto_seriale/matvec_serial.h"
#include "prodotto_seriale/blocking.h"
#endif

int main() {
    int M, N, nz;
    int *I, *J;
    double *val;

    if (load_matrix("matrices/cage4.mtx", &M, &N, &nz, &I, &J, &val) != 0) {
        return 1;
    }

    int *row_ptr, *col_indices;
    double *values;
    convert_to_CSR(M, N, nz, I, J, val, &row_ptr, &col_indices, &values);

#ifdef USE_OPENMP
    printf("Esecuzione con OpenMP\n");
    matvec_open(M, N, row_ptr, col_indices, values);  
    blocking_open(M, N, row_ptr, col_indices, values);      
#else
    printf("Esecuzione seriale\n");
    matvec_serial(M, N, row_ptr, col_indices, values);
    blocking(M, N, row_ptr, col_indices, values);
#endif

    free(I);
    free(J);
    free(val);
    free(row_ptr);
    free(col_indices);
    free(values);

    return 0;
}

