#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <cmath>

// Función auxiliar encargada de combinar dos subarreglos ordenados
void merge(std::vector<int>& A, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Vectores temporales para almacenar las dos mitades
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i) L[i] = A[l + i];
    for (int j = 0; j < n2; ++j) R[j] = A[m + 1 + j];

    int i = 0; // Índice inicial del primer subarreglo
    int j = 0; // Índice inicial del segundo subarreglo
    int k = l; // Índice inicial del subarreglo combinado

    // Combinación de elementos en orden ascendente
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar elementos remanentes de L[] si los hay
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    // Copiar elementos remanentes de R[] si los hay
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

// Algoritmo principal de merge sort
void mergesort_rec(std::vector<int>& A, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2; // Evita desbordamiento aritmético a diferencia de (l+r)/2

        // Divide y vence recursivamente sobre ambas mitades
        mergesort_rec(A, l, m);
        mergesort_rec(A, m + 1, r);

        // Combina las soluciones de forma lineal
        merge(A, l, m, r);
    }
}

void mergesort(std::vector<int>& A) {
    if (!A.empty()) {
        mergesort_rec(A, 0, A.size()-1);
    }
}

#endif // MERGESORT_H
