#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 2000
#define BLOCK_SIZE 32

void iniciar();
void limpeza();
void multiplica_matriz();
void multiplica_matriz2();
void alocar();
void transpor_matriz();

double get_wall_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * 1e-6;
}

int main(){
    int i, j, k;
    double **matriz_A, **matriz_B, **matriz_C;
    clock_t t;
    double start_time, end_time;

    matriz_A = malloc(sizeof(double*) * N);
    matriz_B = malloc(sizeof(double*) * N);
    matriz_C = malloc(sizeof(double*) * N);
    alocar(matriz_A, matriz_B, matriz_C);
    srand(time(NULL));
    iniciar(matriz_A, matriz_B, matriz_C);
    
    start_time = get_wall_time();

    //multiplica_matriz(matriz_A, matriz_B, matriz_C);
    transpor_matriz(matriz_B);
    multiplica_matriz2(matriz_A, matriz_B, matriz_C);
 
    end_time = get_wall_time();
   
    printf("Tempo decorrido: %f segundos\n", end_time - start_time);
     
    limpeza(matriz_A, matriz_B, matriz_C);

    return 0;
}    

void iniciar(double **matriz_A, double **matriz_B, double **matriz_C ) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz_A[i][j] = (rand() % 20) - 10;
            matriz_B[i][j] = (rand() % 20) - 10;
            matriz_C[i][j] = 0;
        }
    }

}

void limpeza(double **matriz_A, double **matriz_B, double **matriz_C){
    
    for(int i = 0; i < N; i++){
        free(matriz_A[i]);
        free(matriz_B[i]);
        free(matriz_C[i]);
    }
    free(matriz_A);
    free(matriz_B);
    free(matriz_C);
}

void alocar(double **matriz_A, double **matriz_B, double **matriz_C){
    *matriz_A = malloc(sizeof(double *) * N);
    *matriz_B = malloc(sizeof(double *) * N);
    *matriz_C = malloc(sizeof(double *) * N);
    for(int i = 0; i < N; i++){
        matriz_A[i] = malloc(sizeof(double) * N);
        matriz_B[i] = malloc(sizeof(double) * N);
        matriz_C[i] = malloc(sizeof(double) * N);
    }
}

void multiplica_matriz(double **matriz_A, double **matriz_B, double **matriz_C){
    
    for (int i = 0; i < N; i++){
        for (int k = 0; k < N; k++){
            double r = matriz_A[i][k];
            for(int j = 0; j < N; j++){
                matriz_C[i][j] += r * matriz_B[k][j];
            }
        }
    }
        
}


void multiplica_matriz2(double **matriz_A, double **matriz_B, double **matriz_C){
    int num = N/BLOCK_SIZE;
    for (int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            for (int k = 0; k < BLOCK_SIZE; k++){
                for (int m = 0; m < BLOCK_SIZE; m++){
                    double sum = 0.0;
                    for(int r = 0; r < num; r++){
                        for(int p = 0; p < BLOCK_SIZE; p++){
                            sum += *matriz_A[i*BLOCK_SIZE*N + r*BLOCK_SIZE + k*N + p] * *matriz_B[j*BLOCK_SIZE*N + r*BLOCK_SIZE + m*N + p];
                        }

                    }  
                    *matriz_C[i*BLOCK_SIZE*N + j*BLOCK_SIZE + k*N + m] = sum;
                }
            }
        }
    }     
}

/*
void multiplica_matriz3(double **matriz_A, double **matriz_B, double **matriz_C){
    for (int bi = 0; bi < N; bi += BLOCK_SIZE) {
        for (int bj = 0; bj < N; bj += BLOCK_SIZE) {
            for (int i = bi; i < bi + BLOCK_SIZE && i < N; i++) {
                for (int k = 0; k < N; k++) {
                    double *pA = matriz_A + i * N + k;
                    double *sum = 0.0;
                    for (int j = bj; j < bj + BLOCK_SIZE && j < N; j++) {
                        double *pB = matriz_B + k * N + j;
                        *sum = matriz_C + i * N + j;
                        *sum += (*pA) * (*pB);
                    }
                    *pC = *sum;
                }
            }
        }
    }
}
*/


void transpor_matriz(double **matriz){
    int temp;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            temp = matriz[i][j];
            matriz[i][j] = matriz[j][i];
            matriz[j][i] = temp;
        }
    }
}
