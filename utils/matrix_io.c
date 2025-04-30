#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"
#include "matrix_io.h"

int load_matrix(const char *filename, int *M, int *N, int *nz, int **I, int **J, double **val) {
    FILE *f;
    MM_typecode matcode;

    if ((f = fopen(filename, "r")) == NULL) {
        printf("Errore nell'aprire il file.\n");
        return 1;
    }

    if (mm_read_banner(f, &matcode) != 0) {
        printf("Impossibile leggere l'intestazione del file.\n");
        return 1;
    }

    if (mm_read_mtx_crd_size(f, M, N, nz) != 0) {
        printf("Impossibile leggere le dimensioni della matrice.\n");
        return 1;
    }

    *I = (int *)malloc(*nz * sizeof(int));
    *J = (int *)malloc(*nz * sizeof(int));
    *val = (double *)malloc(*nz * sizeof(double));

    for (int i = 0; i < *nz; i++) {
        fscanf(f, "%d %d %lf\n", &(*I)[i], &(*J)[i], &(*val)[i]);
        (*I)[i]--;
        (*J)[i]--;
    }

    fclose(f);
    return 0;
}
