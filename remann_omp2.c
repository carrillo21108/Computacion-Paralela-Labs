// Brian Anthony Carrillo Monzon
// Computacion paralela - 21108

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Definición de la función f(x) a integrar
// En este caso, la función es x^2
double f(double x) {
    return pow(x, 2);
}

// Función que calcula la suma de Riemann usando la regla trapezoidal
// a: límite inferior del intervalo
// b: límite superior del intervalo
// n: número de subdivisiones (trapezoides)
double trapezoides(double a, double b, int n) {
    // Calcula la anchura de cada subdivisión
    double h = (b - a) / n;
    
    // Inicializa la suma considerando los extremos del intervalo
    double sum = 0.5 * (f(a) + f(b));
    
    // Ciclo para sumar las áreas de los trapezoides interiores
    for (int i = 1; i < n; i++) {
        double x = a + i * h; // Calcula la posición de x en la i-ésima subdivisión
        sum += f(x); // Añade la función f(x) a la suma total
    }
    
    // Multiplica la suma por h (la anchura de cada subdivisión) para obtener la integral aproximada
    return sum * h;
}

int main(int argc, char *argv[]) {
    // Verifica si los argumentos son suficientes
    // Se necesitan 4 argumentos: a, b, n y threads
    if (argc != 5) {
        printf("Uso: %s <a> <b> <n> <threads>\n", argv[0]);
        return 1;
    }

    // Convierte los argumentos de string a sus respectivos tipos numéricos
    double a = atof(argv[1]); // Convierte el primer argumento a double (límite inferior)
    double b = atof(argv[2]); // Convierte el segundo argumento a double (límite superior)
    int n = atoi(argv[3]); // Convierte el tercer argumento a entero (número de subdivisiones)
    int num_threads = atoi(argv[4]); // Convierte el cuarto argumento a entero (número de threads)

    // Verifica que n y num_threads sean enteros positivos
    if (n <= 0 || num_threads <= 0) {
        printf("El valor de n y el número de threads deben ser enteros positivos.\n");
        return 1;
    }

    // Verifica que n sea múltiplo de num_threads
    if (n % num_threads != 0) {
        printf("El número de trapezoides debe ser múltiplo del número de threads.\n");
        return 1;
    }

    // Calcula la anchura de cada subdivisión
    double h = (b - a) / n;
    // Calcula el número de subdivisiones que cada thread va a procesar
    int n_local = n / num_threads;
    double resultado = 0.0;

    // Inicialización del número de threads
    omp_set_num_threads(num_threads);

    // Región paralela donde cada thread ejecuta el código dentro del bloque
    #pragma omp parallel
    {
        // Obtiene el ID del thread actual
        int thread_id = omp_get_thread_num();
        
        // Calcula el límite inferior y superior del intervalo que procesará cada thread
        double a_local = a + thread_id * n_local * h;
        double b_local = a_local + n_local * h;
        
        // Calcula la suma de Riemann para el intervalo local
        double resultado_local = trapezoides(a_local, b_local, n_local);

        // Sección crítica donde se acumulan los resultados parciales de cada thread
        #pragma omp critical
        {
            resultado += resultado_local;
        }
    }

    // Imprime el resultado final de la integral aproximada
    printf("El resultado de la suma de Riemann usando la regla trapezoidal es: %f\n", resultado);

    // Finaliza el programa
    return 0;
}
