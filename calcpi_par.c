#include <stdio.h>
#include "mpi.h"

#define N 1000000000

int main(int argc, char *argv[]) { /* calcpi_par.c  */
    double tempo_inicial, tempo_final, pi, mypi = 0.0f; 
    long i;
    int meu_ranque, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque); 
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 

    tempo_inicial = MPI_Wtime();

    for (i = meu_ranque*N/num_procs; i < (meu_ranque+1)*N/num_procs; i++) {
         double t = (double) ((i+0.5)/N);
         mypi += 4.0/(1.0+t*t);
    }
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(meu_ranque == 0){
        printf("pi = %f\n", pi/N);
    }

    tempo_final = MPI_Wtime();

    MPI_Finalize();

    printf("Foram gastos %3.6f segundos\n", tempo_final-tempo_inicial);

    return(0);
}
