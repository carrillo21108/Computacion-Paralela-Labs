// Brian Anthony Carrillo Monzón - 21108

#include <stdio.h>    // Biblioteca estándar de entrada/salida
#include <stdlib.h>   // Biblioteca estándar para funciones generales, como la conversión de cadenas a enteros

int main(int argc, char *argv[]) {
    // Verifica que el número de argumentos sea exactamente 2 (el nombre del programa y un argumento adicional)
    if (argc != 2) {
        printf("Usage: %s <number_of_iterations>\n", argv[0]);
        return 1;  // Si no se proporciona el argumento correcto, el programa termina con un código de error
    }

    // Convierte el argumento (número de iteraciones) de cadena a entero
    int n = atoi(argv[1]);

    double factor = 1.0;  // Inicializa el factor con 1.0
    double sum = 0.0;     // Inicializa la suma en 0.0

    // Bucle para calcular la suma de la serie
    for (int k = 0; k < n; k++) {
        sum += factor / (2 * k + 1);  // Añade el término correspondiente a la suma
        factor = -factor;  // Alterna el signo del factor para la siguiente iteración
    }

    // Calcula la aproximación de Pi multiplicando la suma por 4
    double pi_approx = 4.0 * sum;

    // Muestra la aproximación de Pi en la consola
    printf("Approximation of Pi: %f\n", pi_approx);

    return 0;  // Termina el programa exitosamente
}
