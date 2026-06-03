#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include "matrices.h"
#include "strassen.h"
#include "tiempoejecucion.h"

using namespace std;


// Genera una matriz de n x n con valores flotantes aleatorios entre 0.0 y 10.0
Matriz generarMatrizAleatoria(int n) {
    Matriz M = crearMatriz(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 10.0);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            M[i][j] = dis(gen);
        }
    }
    return M;
}


int main() {
    std::cout << "=====================================================" << std::endl;
    std::cout << "Iniciando Experimento de Matrices (Fuerza Bruta vs Strassen)" << std::endl;
    std::cout << "=====================================================" << std::endl;

//    std::ofstream archivoCSV("tiempos_matrices.csv");
    ofstream archivo("tiempos_matrices.csv", std::ios::trunc);
    archivo << "Tamaño,Fuerza bruta,Strassen\n";

    // Dimensiones obligatorias potencias de 2 para Strassen
    std::vector<int> tamanosMatrices = {64, 128, 256, 512};
    const int REPETICIONES = 3;

    for (int n : tamanosMatrices) {
        std::cout << "Procesando dimension n = " << n << "... " << std::flush;

        double t_acumulado_tradicional = 0.0;
        double t_acumulado_strassen = 0.0;

        for (int r = 0; r < REPETICIONES; ++r) {
            Matriz A = generarMatrizAleatoria(n);
            Matriz B = generarMatrizAleatoria(n);

            // 1. Medir Multiplicación Tradicional empleando tu función genérica
            // Como tu cabecera devuelve segundos en double, multiplicamos por 1000.0 para pasarlo a milisegundos
            double t_tradicional = medir_tiempo_ejecucion(multiplicacionMatrices, A, B);
            t_acumulado_tradicional += t_tradicional * 1000.0;

            // 2. Medir Algoritmo de Strassen empleando tu función genérica
            double t_strassen = medir_tiempo_ejecucion(strassen, A, B);
            t_acumulado_strassen += t_strassen * 1000.0;
        }

        // Calcular los promedios numéricos netos
        double promedio_tradicional = t_acumulado_tradicional / REPETICIONES;
        double promedio_strassen = t_acumulado_strassen / REPETICIONES;

        // Volcar datos al archivo CSV
        archivo << n << "," << promedio_tradicional << "," << promedio_strassen << "\n";
        
        std::cout << "¡Completado! (Tradicional: " << promedio_tradicional
                  << " ms | Strassen: " << promedio_strassen << " ms)" << std::endl;
    }

    archivo.close();
    std::cout << "\nExperimento finalizado con exito. Archivo 'tiempos_matrices.csv' generado.\n";

    return 0;
}
