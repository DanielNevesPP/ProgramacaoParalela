#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int main(){
    int i, j, k;
    double *matriz_A, *matriz_B, *matriz_C;
    clock_t t;

    matriz_A = malloc(sizeof(double) * N * N);
    matriz_B = malloc(sizeof(double) * N * N);
    matriz_C = malloc(sizeof(double) * N * N);

    srand(time(NULL));
    for (i = 0; i < N; i ++)
        for (j = 0; j < N; j ++){
            matriz_A[i*N + j] = (rand() % 20) - 10;
            matriz_B[i*N + j] = (rand() % 20) - 10;
            matriz_C[i*N + j] = 0;
        }

    t = clock();
    for (i = 0; i < N; i ++)
        for (j = 0; j < N; j ++)
            for (k = 0; k < N; k ++)
                matriz_C[i*N + j] += matriz_A[i*N + j] * matriz_B[i*N + j];
    t = clock() - t;
    printf("Tempo de execucao: %lf\n", ((double)t)/CLOCKS_PER_SEC);
    /*for (i = 0; i < N; i ++)
        for (j = 0; j < N; j ++){
            printf("%f ", matriz_C[i*N + j]);
        }*/

    free(matriz_A);
    free(matriz_B);
    free(matriz_C);

    return 0;
}
