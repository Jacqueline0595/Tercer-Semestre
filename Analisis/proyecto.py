import numpy as np  
from fractions import Fraction

def leerMatriz(nombre_archivo):
    with open(nombre_archivo, 'r') as f:
        lineas = f.readlines()
    
    n, m = map(int, lineas[0].strip().split()) 
    matriz = [list(map(lambda x: Fraction(x), linea.split())) for linea in lineas[1:n+1]]
    
    return np.array(matriz, dtype=object)  

def gaussJordan(matriz, archivo):
    n, m = matriz.shape 
    with open(archivo, 'w') as f:
        f.write("La matriz original es:\n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")
        f.write("\n")
        
        for i in range(n): 
            piv = matriz[i, i]  
            f.write(f"Dividimos la fila {i + 1} por {piv} para hacer el pivote\n")
            matriz[i] = [x / piv for x in matriz[i]]  
            
            for j in range(n):  
                if i != j and j < n:
                    factor = matriz[j, i]  
                    f.write(f"A la fila {j + 1} le restamos {factor} y multiplicamos por la fila {i + 1}\n")
                    matriz[j] = [matriz[j, k] - factor * matriz[i, k] for k in range(m)]  
            
            f.write("\nDespues de la operacion:\n")
            for fila in matriz:
                f.write(" ".join(map(str, fila)) + "\n")
            f.write("\n")
        
        f.write("Resultado: \n")
        for fila in matriz:
            f.write(" ".join(map(str, fila)) + "\n")
    
    return matriz  

def main():
    archivo = r"C:\\Users\\jacqu\\3\\Tercer-Semestre\\Analisis\\matriz.txt"
    
    datos = leerMatriz(archivo)
    gaussJordan(datos, archivo)
    
    print("Listooo :D")

if __name__ == "__main__":
    main()
