// Brian Anthony Carrillo Monzon
// Computacion paralela - 21108

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definición de la función f(x) a integrar
// En este caso, la función es sin(x)
double f(double x) {
    return sin(x);
}

// Función que calcula la suma de Riemann usando la regla trapezoidal
// a: límite inferior del intervalo
// b: límite superior del intervalo
// n: número de subdivisiones (trapezoides)
double trapezoides(double a, double b, int n) {
    // Calcula la anchura de cada subdivisión
    double h = (b - a) / n;
    
    // Calcula la suma inicial sumando los valores en los extremos (f(a) y f(b))
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
    // Se necesitan 3 argumentos: a, b y n
    if (argc != 4) {
        printf("Uso: %s <a> <b> <n>\n", argv[0]);
        return 1;
    }

    // Convierte los argumentos de string a sus respectivos tipos numéricos
    double a = atof(argv[1]); // Convierte el primer argumento a double (límite inferior)
    double b = atof(argv[2]); // Convierte el segundo argumento a double (límite superior)
    int n = atoi(argv[3]); // Convierte el tercer argumento a entero (número de subdivisiones)

    // Verifica que n sea un entero positivo
    if (n <= 0) {
        printf("El valor de n debe ser un entero positivo.\n");
        return 1;
    }

    // Calcula la integral aproximada usando la regla trapezoidal
    double resultado = trapezoides(a, b, n);
    
    // Imprime el resultado de la integral
    printf("El resultado de la suma de Riemann usando la regla trapezoidal es: %f\n", resultado);

    // Finaliza el programa
    return 0;
}
