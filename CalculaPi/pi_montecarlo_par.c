#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define SEED time(NULL)
#define N 1000000000

int main(int argc, char *argv[]) {

    srand( SEED );
    int i, total_count,local_count = 0;
    int meu_ranque, num_procs;
    double x, y, z, pi, tempo_inicial, tempo_final;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    tempo_inicial = MPI_Wtime();

    for (i = meu_ranque; i < N; i += num_procs) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;

        if (z <= 1) local_count++;
    }

    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    tempo_final = MPI_Wtime();

    if (meu_ranque == 0) {
        pi = (double)total_count / N * 4;
        printf("Aproximação de PI é = %g\n", pi);
        printf("Foram gastos %3.6f segundos\n", tempo_final - tempo_inicial);
    }

    MPI_Finalize();

    return 0;
}
