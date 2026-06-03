import csv
import matplotlib.pyplot as plt

# 1. LEER LOS DATOS DESDE EL CSV
valores_n = []
tiempos_insertion = []
tiempos_merge = []
tiempos_quick = []

try:
    with open('tiempos.csv', mode='r', encoding='utf-8') as f:
        lector = csv.reader(f)
        next(lector)  # Omitir cabecera (n, t_insertion, t_merge, t_quick)
        for fila in lector:
            if fila:
                valores_n.append(int(fila[0]))
                tiempos_insertion.append(float(fila[1]))
                tiempos_merge.append(float(fila[2]))
                tiempos_quick.append(float(fila[3]))
except FileNotFoundError:
    print("ERROR: No se encontró 'tiempos.csv'.")
    exit()

# 2. CONFIGURAR EL ESTILO DE LA GRÁFICA
plt.figure(figsize=(9, 6), dpi=100)
plt.style.use('seaborn-v0_8-whitegrid' if 'seaborn-v0_8-whitegrid' in plt.style.available else 'default')

# 3. GRAFICAR LAS CURVAS
#plt.plot(valores_n, tiempos_insertion, label='Insertion sort', color='#1f77b4', marker='o', linewidth=2, markersize=6)
plt.plot(valores_n, tiempos_merge, label='Merge sort', color='#ff7f0e', marker='s', linewidth=2, markersize=6)
plt.plot(valores_n, tiempos_quick, label='Quicksort', color='#3d3d3d', marker='d', linewidth=2, markersize=6)

# 4. PERSONALIZAR EL PLANO CARTESIANO
plt.title(r'Análisis empírico de complejidad temporal', fontsize=14, fontweight='bold', pad=15)
plt.xlabel('Tamaño de la entrada ($n$)', fontsize=12, labelpad=10)
plt.ylabel('Tiempo de ejecución (segundos)', fontsize=12, labelpad=10)

# Formatear el eje X para que los números grandes lleven comas (ej: 10,000 en vez de 10000)
plt.gca().xaxis.set_major_formatter(plt.FuncFormatter(lambda x, p: format(int(x), ',')))

# Añadir la leyenda y activar la cuadrícula
plt.legend(fontsize=11, loc='upper left', frameon=True, shadow=True)
plt.grid(True, linestyle='--', alpha=0.6)

# Ajustar márgenes automáticamente para que no se corte nada
plt.tight_layout()

# 5. GUARDAR Y MOSTRAR
plt.savefig('grafica_complejidad.png', bbox_inches='tight')
plt.show()
