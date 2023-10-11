#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
#define SEED time(NULL)

int main() {

    srand( SEED );
    int i, mycount, n=1000000000;
    double x,y,z,pi, tempo_inicial, tempo_final;

    printf("n = %d \n", n);

    mycount = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque); 
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 

    tempo_inicial = MPI_Wtime();

    for(i = meu_ranque*N/num_procs; i < (meu_ranque+1)*N/num_procs; i++) {

        x = (double)rand() / RAND_MAX;

        y = (double)rand() / RAND_MAX;

        z = x * x + y * y;

        if( z <= 1 ) mycount++;
    }

    MPI_Reduce(&mycount, &count, 1, MPI_INTEGER, MPI_SUM, 0, MPI_COMM_WORLD);

    tempo_final = MPI_Wtime();

    MPI_Finalize();

    pi = (double) count / n * 4;
    
    printf("Aproximação de PI é = %g\n", pi);
    printf("Foram gastos %3.6f segundos\n", tempo_final-tempo_inicial);

    return(0);
}
