#ifndef STRASSEN_H
#define STRASSEN_H

#include "matrices.h"


const int UMBRAL = 64;

Matriz strassen_rec(const Matriz& A, const Matriz& B) {
    int n = A.size();
    Matriz C = crearMatriz(n);

    // Caso base: Matrices de 1 x 1
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Caso base optimizado: Matrices de UMBRAL x UMBRAL
//    if (n <= UMBRAL) {
//        return multiplicacionMatrices(A, B);
//    }
    
    int k = n / 2;

    // Crear las 4 submatrices para A y B
    Matriz A11 = crearMatriz(k), A12 = crearMatriz(k), A21 = crearMatriz(k), A22 = crearMatriz(k);
    Matriz B11 = crearMatriz(k), B12 = crearMatriz(k), B21 = crearMatriz(k), B22 = crearMatriz(k);

    // Dividir las matrices originales en los 4 cuadrantes
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Calcular las 7 multiplicaciones intermedias de Strassen (P1 a P7)
    // Se reutilizan las funciones auxiliares de suma y resta de matrices.h
    Matriz P1 = strassen_rec(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    Matriz P2 = strassen_rec(sumarMatrices(A21, A22), B11);
    Matriz P3 = strassen_rec(A11, restarMatrices(B12, B22));
    Matriz P4 = strassen_rec(A22, restarMatrices(B21, B11));
    Matriz P5 = strassen_rec(sumarMatrices(A11, A12), B22);
    Matriz P6 = strassen_rec(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    Matriz P7 = strassen_rec(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Combinar los resultados intermedios para obtener los 4 cuadrantes de la matriz C
    Matriz C11 = restarMatrices(sumarMatrices(P1, P4), sumarMatrices(P5, P7)); // P1 + P4 - P5 + P7
    Matriz C12 = sumarMatrices(P3, P5);                                        // P3 + P5
    Matriz C21 = sumarMatrices(P2, P4);                                        // P2 + P4
    Matriz C22 = restarMatrices(sumarMatrices(P1, P3), restarMatrices(P2, P6)); // P1 + P3 - P2 + P6

    // Reconstruir la matriz C global a partir de sus cuadrantes
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}


Matriz strassen(const Matriz& A, const Matriz& B) {
    if (A.empty() || B.empty() || A.size() != B.size() || A.size() != A[0].size()) {
        throw std::invalid_argument("Las matrices deben ser cuadradas, no vacias y de iguales dimensiones.");
    }
    return strassen_rec(A, B);
}

#endif // STRASSEN_H
