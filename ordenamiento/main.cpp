
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <random>

#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include "tiempoejecucion.h"

using namespace std;


/**
 Crea un arreglo aleatorio.
 */
void crear_arreglo_aleatorio(std::vector<int>& A, int rango) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribucion(0, rango);

    for (int& elemento : A) {
        elemento = distribucion(gen);
    }
}

/**
 Crea un arreglo en orden creciente.
 */
void crear_arreglo_creciente(std::vector<int>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

/**
 Crea un arreglo en orden decreciente.
 */
void crear_arreglo_decreciente(std::vector<int>& A) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        A[i] = n-i;
    }
}

/**
 Ejecuta los experimentos.
 */
void experimentos(int tam_inicial, int tam_final, int intervalo, int reps) {
    std::vector<double> t_is;
    std::vector<double> t_ms;
    std::vector<double> t_qs;

    ofstream archivo("tiempos.csv", std::ios::trunc);
    archivo << "n,insertion sort, merge sort, quicksort\n";
    
    for (int t = tam_inicial; t <= tam_final; t += intervalo) {
        cout << "**********\n***** TAMAÑO ARREGLO " << t << "\n**********" << endl;
        int rango = 10 * t;
        double t_prom_is = 0.0;
        double t_prom_ms = 0.0;
        double t_prom_qs = 0.0;
        for (int i = 0; i < reps; i++) {
            cout << "*** REPETICION " << i+1 << " ***" << endl;
            std::vector<int> A(t);
            double tiempo;
            
            // Arreglo aleatorio
//            cout << "Creando arreglo aleatorio de tamaño " << t << "... ";
//            tiempo = medir_tiempo_ejecucion(crear_arreglo_aleatorio, A, rango);
            
            // Arreglo ordenado creciente
            cout << "Creando arreglo ordenado creciente de tamaño " << t << "... ";
            tiempo = medir_tiempo_ejecucion(crear_arreglo_creciente, A);

            // Arreglo ordenado decreciente
//            cout << "Creando arreglo ordenado decreciente de tamaño " << t << "... ";
//            tiempo = medir_tiempo_ejecucion(crear_arreglo_decreciente, A);
            cout << "\tCreado. ";
            cout << "\tTiempo: " << tiempo << "s" << endl;
            
            std::vector<int> aux = A;
            cout << "Iniciando ordenamiento con INSERTION SORT... " << flush;;
            tiempo = medir_tiempo_ejecucion(insertionsort, aux);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo << "s" << endl;
            t_prom_is = t_prom_is + tiempo;
            
            aux = A;
            cout << "Iniciando ordenamiento con MERGE SORT... " << flush;;
            tiempo = medir_tiempo_ejecucion([](std::vector<int>& v) {
                mergesort(v);
            }, aux);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo << "s" << endl;
            t_prom_ms = t_prom_ms + tiempo;
            
            aux = A;
            cout << "Iniciando ordenamiento con QUICKSORT... " << flush;;
            tiempo = medir_tiempo_ejecucion([](std::vector<int>& v) {
                quicksort(v);
            }, aux);
            cout << "\tOrdenado. ";
            cout << "\tTiempo: " << tiempo << "s" << endl;
            t_prom_qs = t_prom_qs + tiempo;

            cout << endl;
        }
        t_prom_is = t_prom_is / reps;
        t_prom_ms = t_prom_ms / reps;
        t_prom_qs = t_prom_qs / reps;
        cout << "*** TIEMPO PROMEDIO ***" << endl;
        cout << "Insertion sort:\t" << t_prom_is << endl;
        cout << "Merge sort:\t" << t_prom_ms << endl << endl;
        cout << "Quicksort:\t" << t_prom_qs << endl << endl;
        t_is.push_back(t_prom_is);
        t_ms.push_back(t_prom_ms);
        t_qs.push_back(t_prom_qs);
    }
    cout << "**********\n***** RESUMEN\n**********" << endl;
    cout << "n\tInsertion sort\tMerge sort\tQuicksort" << endl;
    for(int i = 0; i < t_is.size(); i++) {
        cout << (tam_inicial + (i*intervalo)) << "\t" << t_is[i] << "\t" << t_ms[i] << "\t" << t_qs[i] << endl;
        archivo << (tam_inicial + (i*intervalo)) << "," << t_is[i] << "," << t_ms[i] << "," << t_qs[i] << "\n";
    }
    archivo.close();
}


int main(int argc, char * argv[]) {
    if (argc != 5) {
        cout << "Sintaxis: main <tamaño_inicial_arreglo> <tamaño_final_arreglo> <intervalo> <repeticiones>" << endl;
    } else {
        experimentos(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    }
    return EXIT_SUCCESS;
}
