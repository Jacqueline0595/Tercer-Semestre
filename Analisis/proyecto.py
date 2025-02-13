import numpy as np 

def leer_matriz_desde_archivo(nombre_archivo):
    # Abrimos el archivo en modo lectura
    with open(nombre_archivo, 'r') as f:
        lineas = f.readlines()
    
    n = int(lineas[0].strip()) 
    matriz = [list(map(float, linea.split())) for linea in lineas[1:n+1]]
    
    return np.array(matriz)  

def gauss_jordan(matriz, archivo):
    n, m = matriz.shape 
    with open(archivo, 'w') as f:
        f.write("Matriz original:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")
        f.write("\n")
        
        for i in range(n): 
            pivote = matriz[i, i]  
            f.write(f"Multiplicamos la fila {i + 1} por {1 / pivote} para hacer el pivote 1\n")
            matriz[i] /= pivote  
            
            for j in range(n):  
                if i != j:  
                    factor = matriz[j, i]  
                    f.write(f"Restamos {factor} veces la fila {i + 1} de la fila {j + 1}\n")
                    matriz[j] -= factor * matriz[i]  
            f.write("Matriz despues de este paso:\n")
            for fila in matriz:
                f.write(" ".join(map(str, fila)) + "\n")
            f.write("\n")
        
        f.write("Matriz final:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")
    
    return matriz  

def main():
    archivo = r"C:\Users\jacqu\3\Tercer-Semestre\Analisis\matriz.txt"
    
    datos = leer_matriz_desde_archivo(archivo)
    matriz_reducida = gauss_jordan(datos, archivo)
    
    print("Listo :D")

if __name__ == "__main__":
    main()
