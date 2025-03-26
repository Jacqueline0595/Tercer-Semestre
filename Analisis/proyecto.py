import numpy as np
from fractions import Fraction

def leer_matriz(nombre_archivo):
    with open(nombre_archivo, 'r') as f:
        lineas = f.readlines()

    if not lineas:
        raise ValueError("Error: El archivo esta vacio.")

    try:
        n, m = map(int, lineas[0].strip().split())  # Tamaño de la matriz
        matriz = [list(map(Fraction, linea.split())) for linea in lineas[1:n+1]]
    except Exception as e:
        raise ValueError(f"Error al leer la matriz: {e}")

    if len(matriz) != n or any(len(fila) != m for fila in matriz):
        raise ValueError("Error: La matriz no coincide con las dimensiones especificadas.")

    return np.array(matriz, dtype=object)

def intercambiar_filas(matriz, fila1, fila2):
    matriz[[fila1, fila2]] = matriz[[fila2, fila1]]

def gauss_jordan(matriz, archivo):
    n, m = matriz.shape
    with open(archivo, 'a') as f:  # Modo 'a' para no sobrescribir cada vez
        f.write("La matriz original es:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")
        f.write("\n")

        for i in range(n):
            # Si el pivote es 0, buscar otra fila para intercambiar
            if matriz[i, i] == 0:
                for k in range(i+1, n):
                    if matriz[k, i] != 0:
                        intercambiar_filas(matriz, i, k)
                        break
                else:
                    raise ValueError(f"Error: La matriz tiene un pivote cero en la fila {i+1}, el sistema puede ser dependiente.")

            pivote = matriz[i, i]
            f.write(f"Dividimos la fila {i+1} por {pivote} para hacer el pivote 1\n")
            matriz[i] = matriz[i] / pivote  # Normaliza la fila del pivote

            for j in range(n):
                if i != j:
                    factor = matriz[j, i]
                    f.write(f"A la fila {j+1} le restamos {factor} veces la fila {i+1}\n")
                    matriz[j] = matriz[j] - factor * matriz[i]  # Eliminación de Gauss-Jordan

            f.write("\nDespues de la operacion:\n")
            for fila in matriz:
                f.write(" ".join(map(str, fila)) + "\n")
            f.write("\n")

        f.write("Resultado:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")

    return matriz

def main():
    archivo = r"C:\\Users\\jacqu\\3\\Tercer-Semestre\\Analisis\\matriz.txt"

    try:
        datos = leer_matriz(archivo)
        gauss_jordan(datos, archivo)
        print("Listooo :D")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
