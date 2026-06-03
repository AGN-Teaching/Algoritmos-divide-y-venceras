# Análisis empírico de algoritmos divide y vencerás

Este repositorio contiene la infraestructura de código base para un ejercicio de laboratorio de **Análisis y Diseño de Algoritmos**. El objetivo principal es evaluar de manera empírica el impacto del paradigma *Divide y Vencerás* frente a los enfoques tradicionales de *Fuerza Bruta*, analizando el rendimiento real en hardware mediante la recolección de métricas temporales.

---

## Estructura del Proyecto

El repositorio está organizado de forma modular en dos grandes bloques independientes:

```text
.
├── README.md                # Guía general del ejercicio
├── ordenamiento/            # BLOQUE I: Eficiencia en algoritmos de ordenamiento
│   ├── tiempoejecucion.h    # Cabecera genérica para medición de tiempos empleando C++17
│   ├── insertionsort.h      # Implementación de insertion sort
│   ├── mergesort.h          # Implementación de merge sort 
│   ├── quicksort.h          # Implementación de quicksort (Pivote fijo)
│   ├── main.cpp             # Generador de vectores, ejecutor de pruebas y exportador CSV
│   └── graficador.py        # Script en Python para dibujar curvas de rendimiento
└── matrices/                # BLOQUE II: Multiplicación de matrices
    ├── tiempoejecucion.h    # Copia local de la cabecera genérica de cronometraje
    ├── matrices.h           # Utilidades para la creación y gestión de matrices dinámicas
    ├── strassen.h           # Implementación del algoritmo de Strassen
    ├── main.cpp             # Generador de matrices aleatorias y ejecutor de pruebas algebráicas
    └── graficador.py        # Script en Python para dibujar curvas de rendimiento
```
---

## Requisitos del Sistema

Para compilar y ejecutar los experimentos correctamente, asegúrate de contar con las siguientes herramientas en tu entorno local:

1. **Compilador de C++**: Compatible con el estándar **C++17** o superior (p. ej., `g++` v9.0+, `clang` o MSVC actualizado).
2. **Python 3**: Con las siguientes dependencias instaladas para la generación de gráficos:
   ```bash
   pip install matplotlib

## Instrucciones de Uso
Cada bloque es autocontenido. Debes situar tu terminal en la carpeta correspondiente antes de compilar o ejecutar los scripts.

## Bloque I: Algoritmos de ordenamiento
Este bloque somete a los algoritmos a muestras incrementales desde `n = 5,000` hasta `n = 30,000` elementos bajo dos condiciones críticas: arreglos aleatorios y arreglos ya ordenados en forma creciente.

1. Navegar al directorio:
```
cd ordenamiento
```

2. Compilar el código fuente:
```
g++ -std=c++17 main.cpp -o main
```

3. Ejecutar el experimento:
```
./main
```
(Esto procesará las pruebas y generará de forma automática el archivo tiempos_ordenamiento.csv).

4. Graficar los resultados:
```
python graficador.py
```
(El script generará las imágenes con las curvas de crecimiento listas para tu análisis).

## Bloque II: Multiplicación de matrices
Este bloque contrasta la multiplicación tradicional por fuerza bruta ($\Theta$($n^3$)) contra el método de Strassen ($\Theta$($n^{2.807}$) utilizando matrices cuadradas de tamaño de potencias de 2 (n = 64, 128, 256, 512).

1. Navegar al directorio:
```
cd ../matrices
```

2. Compilar el código fuente:
```
g++ -std=c++17 main.cpp -o main
```

3. Ejecutar el experimento:
```
./main
```
(Al finalizar, se exportará el archivo con las métricas netas denominado tiempos_matrices.csv).

4. Graficar los resultados:
```
python graficador.py
```
(Esto generará el archivo visual grafica_matrices.png).
