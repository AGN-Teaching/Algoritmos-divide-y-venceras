#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <utility>

// Esquema de partición de Lomuto
// Selecciona el último elemento como pivote y reorganiza el subarreglo
int particionar(std::vector<int>& A, int l, int r) {
    int pivote = A[r]; // Pivote fijo en la frontera derecha
    int i = l - 1;    // Índice del elemento más pequeño

    for (int j = l; j <= r - 1; ++j) {
        // Si el elemento actual es menor o igual al pivote
        if (A[j] <= pivote) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    // Coloca el pivote en su posición correcta intermedia
    std::swap(A[i + 1], A[r]);
    return (i + 1);
}

// Algoritmo principal de quicksort
void quicksort_rec(std::vector<int>& A, int l, int r) {
    if (l < r) {
        // s es el índice de división donde el pivote ya está en su posición final
        int q = particionar(A, l, r);

        // Ordena recursivamente los subarreglos izquierdo y derecho
        quicksort_rec(A, l, q - 1);
        quicksort_rec(A, q + 1, r);
    }
}

void quicksort(std::vector<int>& A) {
    if (!A.empty()) {
        quicksort_rec(A, 0, A.size()-1);
    }
}

#endif // QUICKSORT_H
