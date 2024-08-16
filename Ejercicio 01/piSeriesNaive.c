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
    
    double factor = 1.0;  // Inicializa el factor con 1.0
    double sum = 0.0;     // Inicializa la suma en 0.0

    // Paraleliza el bucle usando OpenMP, con un número de hilos igual a 'thread_count'
    // La cláusula 'reduction(+:sum)' asegura que las sumas parciales calculadas por cada hilo se acumulen correctamente
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum)
    for (int k = 0; k < n; k++) {
        sum += factor / (2 * k + 1);  // Calcula el siguiente término de la serie y lo añade a la suma
        factor = -factor;  // Cambia el signo del factor para la siguiente iteración
    }

    // Calcula la aproximación de Pi multiplicando la suma por 4
    double pi_approx = 4.0 * sum;

    // Muestra la aproximación de Pi en la consola
    printf("Approximation of Pi: %f\n", pi_approx);

    return 0;  // Termina el programa exitosamente
}
