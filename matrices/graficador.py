import csv
import matplotlib.pyplot as plt

# 1. LEER LOS DATOS DESDE EL CSV DE MATRICES
valores_n = []
tiempos_tradicional = []
tiempos_strassen = []

try:
    with open('tiempos_matrices.csv', mode='r', encoding='utf-8') as f:
        lector = csv.reader(f)
        next(lector)  # Omitir cabecera (Tamaño,Tradicional,Strassen)
        for fila in lector:
            if fila:
                valores_n.append(int(fila[0]))
                tiempos_tradicional.append(float(fila[1]))
                tiempos_strassen.append(float(fila[2]))
except FileNotFoundError:
    print("ERROR: No se encontró 'tiempos_matrices.csv'.")
    exit()

# 2. CONFIGURAR EL ESTILO DE LA GRÁFICA
plt.figure(figsize=(9, 6), dpi=100)
plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')

# 3. GRAFICAR AMBAS CURVAS MATRICIALES
plt.plot(valores_n, tiempos_tradicional, label='Multiplicación Tradicional $\\Theta(n^3)$', color='#7f7f7f', marker='o', linewidth=2, markersize=6)
plt.plot(valores_n, tiempos_strassen, label='Algoritmo de Strassen $\\Theta(n^{2.807})$', color='#9467bd', marker='X', linewidth=2, markersize=6)

# 4. PERSONALIZAR EL PLANO CARTESIANO
plt.title('Multiplicación de Matrices: Impacto de las Constantes Ocultas', fontsize=14, fontweight='bold', pad=15)
plt.xlabel('Dimensión de la matriz cuadrada ($n \\times n$)', fontsize=12, labelpad=10)
plt.ylabel('Tiempo de ejecución (milisegundos)', fontsize=12, labelpad=10)

# Forzar a que el eje X muestre exactamente tus tamaños de control (potencias de 2)
plt.xticks(valores_n)

# Añadir la leyenda y activar la cuadrícula
plt.legend(fontsize=11, loc='upper left', frameon=True, shadow=True)
plt.grid(True, linestyle='--', alpha=0.6)

# Ajustar márgenes automáticamente
plt.tight_layout()

# 5. GUARDAR Y MOSTRAR
plt.savefig('grafica_matrices.png', bbox_inches='tight')
plt.show()
