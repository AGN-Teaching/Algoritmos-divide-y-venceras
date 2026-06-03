#ifndef MATRICES_H
#define MATRICES_H

#include <vector>
#include <stdexcept>

// Alias de tipo para simplificar la lectura y escritura del código
using Matriz = std::vector<std::vector<double>>;

// Función auxiliar para crear e inicializar una matriz vacía de n x n
Matriz crearMatriz(int n) {
    return std::vector<std::vector<double>>(n, std::vector<double>(n, 0.0));
}

// Algoritmo de fuerza bruta de multiplicación de matrices
Matriz multiplicacionMatrices(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double suma = 0.0;
            for (int k = 0; k < n; ++k) {
                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
        }
    }
    return C;
}

// Función auxiliar: Suma de dos matrices cuadradas (Theta(n^2))
Matriz sumarMatrices(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función auxiliar: Resta de dos matrices cuadradas (Theta(n^2))
Matriz restarMatrices(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

#endif // MATRICES_H
