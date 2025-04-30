#include <stdio.h>
#include <stdlib.h>
#include "utils/matrix_io.h"
#include "utils/convert.h"
#include "prodotto_seriale/matvec_serial.h"

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

    matvec_serial(M, N, row_ptr, col_indices, values);

    free(I);
    free(J);
    free(val);
    free(row_ptr);
    free(col_indices);
    free(values);

    return 0;
}
