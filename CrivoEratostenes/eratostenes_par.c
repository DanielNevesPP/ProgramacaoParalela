#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

int main(int argc, char *argv[]){
    long int n = 1000, i, j;
    bool a[n+1];
    double inicio, fim;

    omp_set_num_threads(1);
    inicio = omp_get_wtime();

    #pragma omp parallel for
    for(i = 0; i <= n; i++){
        a[i] =  true;
    }

    a[0] = false;
    a[1] = false;

    #pragma omp parallel for schedule(dynamic, 1)
    for(i = 2; i <= (int)floor(sqrt(n)); i++){
        if(a[i] == true){
            for(j = i+i; j <= n; j += i){
                a[j] = false;
            }
        }
    }

    fim = omp_get_wtime();
    printf("Tempo gasto: %fs\n", fim - inicio);

    /*for(i = 2; i <= n; i++)
        if(a[i] == true)
            printf("%d\n", i);*/

    return 0;
}
