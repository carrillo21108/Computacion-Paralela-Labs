/*
*----------------------------------------
* quicksort_file.cpp
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3069 - Computacion Paralela y Distribuida
*
* Brian Anthony Carrillo Monzon
* Carlos Edgardo Lopez Barrera
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

void quicksort(int *data, int lo, int hi) {
    if (lo >= hi) return;
    int l = lo, h = hi;
    int p = data[(lo + hi) / 2];
    while (l <= h) {
        while (data[l] < p) l++;
        while (data[h] > p) h--;
        if (l <= h) {
            std::swap(data[l], data[h]);
            l++;
            h--;
        }
    }
    quicksort(data, lo, h);
    quicksort(data, l, hi);
}

int main() {
    int N;
    std::cout << "Cantidad de números aleatorios a generar: ";
    std::cin >> N;

    clock_t start_total = clock();

    // Generar números aleatorios y escribirlos en el archivo numeros.csv
    std::ofstream outFile("numeros.csv");
    if (!outFile) {
        std::cerr << "Error al crear el archivo numeros.csv\n";
        return 1;
    }

    srand(time(0));
    for (int i = 0; i < N; ++i) {
        int num = rand() % 1000000;
        outFile << num;
        if (i < N - 1) outFile << ",";
    }
    outFile.close();

    // Leer los números del archivo y guardarlos en un arreglo
    int *arr = new int[N];
    std::ifstream inFile("numeros.csv");
    if (!inFile) {
        std::cerr << "Error al leer el archivo numeros.csv\n";
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        char comma;
        inFile >> arr[i];
        if (i < N - 1) inFile >> comma;
    }
    inFile.close();

    // Medir el tiempo para el ordenamiento
    clock_t start_sort = clock();
    
    // Ordenar los números usando QuickSort
    quicksort(arr, 0, N - 1);

    clock_t end_sort = clock();
    double time_sort = double(end_sort - start_sort) / CLOCKS_PER_SEC;
    std::cout << "Tiempo para el ordenamiento: " << time_sort << " segundos\n";

    // Escribir los números ordenados en el archivo numeros_ordenados
    std::ofstream sortedFile("numeros_ordenados.csv");
    if (!sortedFile) {
        std::cerr << "Error al crear el archivo numeros_ordenados.csv\n";
        delete[] arr;
        return 1;
    }

    for (int i = 0; i < N; ++i) {
        sortedFile << arr[i];
        if (i < N - 1) sortedFile << ",";
    }
    sortedFile.close();

    // Medir el tiempo total del proceso
    clock_t end_total = clock();
    double time_total = double(end_total - start_total) / CLOCKS_PER_SEC;
    std::cout << "Tiempo total de ejecución: " << time_total << " segundos\n";

    // Liberar la memoria dinámica
    delete[] arr;

    std::cout << "Proceso completado.\n";

    return 0;
}
