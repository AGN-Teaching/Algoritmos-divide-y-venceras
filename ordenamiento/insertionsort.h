#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H


void insertionsort(std::vector<int>& A) {
    int n = A.size();
    for (int i = 1; i < n; i++) {
        int k = A[i];
        int j = i-1;
 
        // Se mueven los elementos de A[0..i-1], que son
        // mayores que k, a una posición hacia la derecha
        // de su posicion actual
        while (j >= 0 && A[j] > k) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = k;
    }
}

#endif // INSERTIONSORT_H
