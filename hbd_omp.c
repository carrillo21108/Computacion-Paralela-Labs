// Brian Anthony Carrillo Monzon
// Computacion paralela - 21108

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Función principal del programa
int main(int argc, char *argv[]) {
    int num_threads = 10; // Número de threads por defecto es 10

    // Verificación de argumento de número de threads
    // Si se proporciona un argumento, se utiliza para establecer el número de threads
    if (argc > 1) {
        num_threads = atoi(argv[1]); // Convierte el argumento de string a entero
    }

    // Inicialización del número de threads con el valor especificado
    omp_set_num_threads(num_threads);

    // Comienza la región paralela donde cada thread ejecuta el código dentro del bloque
    #pragma omp.parallel
    {
        // Obtiene el número de thread actual (0 a num_threads-1)
        int thread_num = omp_get_thread_num();
        // Obtiene el número total de threads en ejecución en esta región paralela
        int total_threads = omp_get_num_threads();
        
        // Imprime el ID del thread y el número total de threads
        printf("Thread ID: %d, Total Threads: %d\n", thread_num, total_threads);

        // Verifica si el ID del thread es par o impar
        if (thread_num % 2 == 0) {
            // Si el thread ID es par, imprime un saludo
            printf("Saludos del hilo %d\n", thread_num);
        } else {
            // Si el thread ID es impar, imprime un mensaje de feliz cumpleaños usando el número total de threads
            printf("Feliz cumpleaños número %d!\n", total_threads);
        }
    }

    // Retorno de la función main, finaliza el programa
    return 0;
}
