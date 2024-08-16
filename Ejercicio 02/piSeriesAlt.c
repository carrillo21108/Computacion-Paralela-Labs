// Brian Anthony Carrillo Monzón - 21108

#include <stdio.h>    // Biblioteca estándar de entrada/salida
#include <stdlib.h>   // Biblioteca estándar para funciones generales, como la conversión de cadenas a enteros
#include <omp.h>      // Biblioteca de OpenMP para programación paralela

int main(int argc, char *argv[]) {
    // Verifica que el número de argumentos sea exactamente 3 (el nombre del programa y dos argumentos adicionales)
    if (argc != 3) {
        printf("Usage: %s <number_of_iterations> <number_of_threads>\n", argv[0]);
        return 1;  // Si no se proporcionan los argumentos correctos, el programa termina con un código de error
    }

    // Convierte el primer argumento (número de iteraciones) de cadena a entero
    int n = atoi(argv[1]);

    // Convierte el segundo argumento (número de hilos) de cadena a entero
    int thread_count = atoi(argv[2]);
    
    double even_sum = 0.0;  // Inicializa la suma para los índices pares en 0.0
    double odd_sum = 0.0;   // Inicializa la suma para los índices impares en 0.0

    // Inicia la medición del tiempo
    double start_time = omp_get_wtime();

    // Paraleliza el bucle usando OpenMP, con un número de hilos igual a 'thread_count'
    // La cláusula 'reduction(+:even_sum, odd_sum)' asegura que las sumas parciales calculadas por cada hilo para 'even_sum' y 'odd_sum' se acumulen correctamente
    #pragma omp parallel for num_threads(thread_count) reduction(+:even_sum, odd_sum)
    for (int k = 0; k < n; k++) {
        if (k % 2 == 0) {
            even_sum += 1.0 / (2 * k + 1);  // Calcula la suma para los índices pares
        } else {
            odd_sum += 1.0 / (2 * k + 1);   // Calcula la suma para los índices impares
        }
    }

    // Calcula la aproximación de Pi restando la suma de los índices impares de la suma de los índices pares y multiplicando por 4
    double pi_approx = 4.0 * (even_sum - odd_sum);

    // Termina la medición del tiempo
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;  // Calcula el tiempo de ejecución

    // Muestra la aproximación de Pi y el tiempo de ejecución en la consola
    printf("Approximation of Pi: %f\n", pi_approx);
    printf("Execution Time: %f seconds\n", execution_time);

    return 0;  // Termina el programa exitosamente
}
