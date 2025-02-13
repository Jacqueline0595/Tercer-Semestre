import numpy as np
def leer_matriz(nombre_archivo):
    with open(nombre_archivo, 'r') as f:
        lineas = f.readlines()
    
    n = int(lineas[0].strip())
    matriz = [list(map(float, linea.split())) for linea in lineas[1:n+1]]
    
    return np.array(matriz)

def gauss_jordan(matriz):
    n, m = matriz.shape 
    
    with open(matriz, 'w') as f:
        f.write("Matriz original:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")
        f.write("\n")
        
        for i in range(n):  # Recorremos cada fila
            pivote = matriz[i, i]  # Obtenemos el elemento de la diagonal
            f.write(f"Multiplicamos la fila {i + 1} por {1 / pivote} para hacer el pivote 1\n")
            matriz[i] /= pivote  # Normalizamos la fila dividiendo todos sus elementos por el pivote
            
            for j in range(n):  # Recorremos nuevamente todas las filas
                if i != j:  # Evitamos la fila actual
                    factor = matriz[j, i]  # Obtenemos el factor a eliminar
                    f.write(f"Restamos {factor} veces la fila {i + 1} de la fila {j + 1}\n")
                    matriz[j] -= factor * matriz[i]  # Restamos la fila actual multiplicada por el factor
            
            f.write("Matriz después de este paso:\n")
            for fila in matriz:
                f.write(" ".join(map(str, fila)) + "\n")
            f.write("\n")
    
    return matriz  # Retornamos la matriz transformada

def escribir_matriz_en_archivo(nombre_archivo, matriz):
    # Abrimos el archivo en modo escritura
    with open(nombre_archivo, 'w') as f:
        f.write(f"{matriz.shape[0]}\n")  # Escribimos el tamaño de la matriz
        
        # Escribimos cada fila de la matriz en el archivo
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")

def main():
    # Nombre del archivo de entrada y archivo de registro
    archivo = r"C:\Users\jacqu\3\Tercer-Semestre\Analisis\matriz.txt"
    
    # Leer la matriz desde el archivo
    datos = leer_matriz(archivo)
    
    # Aplicar el método de Gauss-Jordan con registro de operaciones
    matriz_reducida = gauss_jordan(datos)
    
    # Escribir la matriz transformada de vuelta al archivo
    escribir_matriz_en_archivo(archivo, matriz_reducida)
    
    print("Proceso completado. Revisa los archivos.")  # Mensaje de confirmación

if __name__ == "__main__":
    main()
