#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 **************
 * Enunciado: *
 **************
 
 Escriba un programa que, dado un valor de n menor que $10000,
 calcule el numero total de maneras en que se pueden combinar
 las monedas de $1, $5, $10, $50, $100 y $500 pesos para sumar
 n.
*/

const int V1 = 1;
const int V2 = 5;
const int V3 = 10;
const int V4 = 50;
const int V5 = 100;
const int V6 = 500;

long long int brute_force(int n);
long long int dynamic_programming(int n);

int main(int argc, char* argv[])
{
    if(argc != 2) {
        printf("Error, uso: monedas n\n");
        return -1;
    }

    char* p;
    int n = strtol(argv[1], &p, 10);

    if (*p != '\0') {
        printf("Error, no ha ingresado un numero valido.\n");
        return -1;
    }

    if(n >= 10000 || n <= 0) {
        printf("Error, n debe estar entre 0 y 10000.\n");
        return -1;
    }

    clock_t start, stop;
    double elapsed_time;

    /* Recomiendo comentar estas lineas si se quiere probar para n grandes.
     * Tener en cuenta que para n = 700, fuerza bruta demora cerca de 19 seg.
    */
	
	// Calcular el tiempo requerido por fuerza bruta.
    start = clock();
    printf("Solucion fuerza bruta: %d\n", brute_force(n));
    stop = clock();
    elapsed_time = (double)(stop - start) / (double)CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);
	
	// Calcular el tiempo requerido por programacion dinamica.
    start = clock();
    printf("Solucion DP: %lld\n", dynamic_programming(n));
    stop = clock();
    elapsed_time = (double)(stop - start) / (double)CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}

long long int brute_force(int N)
{
    int i, j, k, l, m, n;
    long long int comb = 0;

	// Se prueban todas las combinaciones posibles.
    for(i = 0; i <= N / V1; i++) {
        for(j = 0; j <= N / V2; j++) {
            for(k = 0; k <= N / V3; k++) {
                for(l = 0; l <= N / V4; l++) {
                    for(m = 0; m <= N / V5; m++) {
                        for(n = 0; n <= N / V6; n++) {
                            int total = i*V1 + j*V2 + k*V3 + l*V4 + m*V5 + n*V6;
                            if (total == N) {
                                comb++;
                            }
                        }
                    }
                }
            }
        }
    }
    return comb;
}

long long int dynamic_programming(int n)
{
    // table[i] guardara el numero de soluciones para el
    // valor i. Se necesitan n+1 filas pues la tabla se construye
    // de manera "bottom up" usando el caso base (n = 0)
    long long int* table, j;

    table = (long long int*)malloc((n + 1)*sizeof(long long int));

    // Inicializar tabla
    for(j = 0; j <= n; j++) table[j] = 0;

    // Caso base.
    table[0] = 1;

    for(j=V1; j<=n; j++)
        table[j] += table[j-V1];
    for(j=V2; j<=n; j++)
        table[j] += table[j-V2];
    for(j=V3; j<=n; j++)
        table[j] += table[j-V3];
    for(j=V4; j<=n; j++)
        table[j] += table[j-V4];
    for(j=V5; j<=n; j++)
        table[j] += table[j-V5];
    for(j=V6; j<=n; j++)
        table[j] += table[j-V6];

    return table[n];
}
