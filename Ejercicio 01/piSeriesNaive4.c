// Brian Anthony Carrillo Monzón - 21108

#include <stdio.h>    // Biblioteca estándar de entrada/salida
#include <stdlib.h>   // Biblioteca estándar para funciones generales, como la conversión de cadenas a enteros
#include <string.h>   // Biblioteca estándar para funciones de manejo de cadenas
#include <omp.h>      // Biblioteca de OpenMP para programación paralela

int main(int argc, char *argv[]) {
    // Verifica que el número de argumentos sea exactamente 5 (el nombre del programa y cuatro argumentos adicionales)
    if (argc != 5) {
        printf("Usage: %s <number_of_iterations> <number_of_threads> <schedule_type> <chunk_size>\n", argv[0]);
        printf("schedule_type: static, dynamic, guided, auto\n");
        printf("chunk_size: integer value (ignored for auto schedule)\n");
        return 1;  // Si no se proporcionan los argumentos correctos, el programa termina con un código de error
    }

    // Convierte el primer argumento (número de iteraciones) de cadena a entero
    int n = atoi(argv[1]);

    // Convierte el segundo argumento (número de hilos) de cadena a entero
    int thread_count = atoi(argv[2]);

    // Almacena el tipo de planificación (schedule) como una cadena
    char *schedule_type = argv[3];

    // Convierte el cuarto argumento (tamaño del chunk) de cadena a entero
    int chunk_size = atoi(argv[4]);

    double sum = 0.0;   // Inicializa la suma en 0.0
    double factor = 1.0;  // Inicializa el factor con 1.0

    // Variable para almacenar el tipo de planificación de OpenMP
    omp_sched_t schedule;
    
    // Determina el tipo de planificación basado en el argumento 'schedule_type'
    if (strcmp(schedule_type, "static") == 0) {
        schedule = omp_sched_static;
    } else if (strcmp(schedule_type, "dynamic") == 0) {
        schedule = omp_sched_dynamic;
    } else if (strcmp(schedule_type, "guided") == 0) {
        schedule = omp_sched_guided;
    } else if (strcmp(schedule_type, "auto") == 0) {
        schedule = omp_sched_auto;
    } else {
        printf("Invalid schedule type. Use static, dynamic, guided, or auto.\n");
        return 1;  // Si el tipo de planificación no es válido, el programa termina con un código de error
    }

    // Configura el tipo de planificación y el tamaño del chunk (si corresponde)
    if (schedule == omp_sched_auto) {
        omp_set_schedule(schedule, 0);  // Auto no utiliza chunk size
    } else {
        omp_set_schedule(schedule, chunk_size);
    }

    // Inicia la medición del tiempo
    double start_time = omp_get_wtime();

    // Paraleliza el bucle usando OpenMP, con un número de hilos igual a 'thread_count'
    // La cláusula 'reduction(+:sum)' asegura que las sumas parciales calculadas por cada hilo se acumulen correctamente
    // La cláusula 'private(factor)' asegura que cada hilo tenga su propia copia del factor
    #pragma omp parallel for num_threads(thread_count) reduction(+:sum) private(factor)
    for (int k = 0; k < n; k++) {
        // Determina el valor del factor basado en si 'k' es par o impar
        if (k % 2 == 0) {
            factor = 1.0;  // Si 'k' es par, el factor es 1.0
        } else {
            factor = -1.0;  // Si 'k' es impar, el factor es -1.0
        }
        sum += factor / (2 * k + 1);  // Calcula el término de la serie y lo añade a la suma
    }

    // Calcula la aproximación de Pi multiplicando la suma por 4
    double pi_approx = 4.0 * sum;

    // Termina la medición del tiempo
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;  // Calcula el tiempo de ejecución

    // Muestra la aproximación de Pi y el tiempo de ejecución en la consola
    printf("Approximation of Pi: %f\n", pi_approx);
    printf("Execution Time: %f seconds\n", execution_time);

    return 0;  // Termina el programa exitosamente
}
