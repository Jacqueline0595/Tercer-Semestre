#include <stdio.h>
#include <stdlib.h>

typedef struct nodoAB
{
    struct nodoAB *izq;
    char *info;
    struct nodoAB *der;
} *AB;

int main()
{
    return 0;
}


// Escribir una función para determinar si 2 árboles binarios son isomorfos. Nota: Misma forma, aunque no los mismos datos.

// Nota:  Solo enviar el código de la función.

int detIgual(AB a, AB b)
{
    int res;
    if(!a && !b)
        res = 1;
    else if(!a || !b)
        res = 0;
    else 
        res = detIgual(a->izq, b->izq) && detIgual(a->der, b->der);
    return(res);
}

// Escribir una función para calcular el número de veces que se repite un dato en un árbol binario.  

int numDato(AB a, int dato)
{
    int res;
    if (!a)
        res = 0;
    else if (a->info == dato)
        res = 1 + numDato(a->izq, dato) + numDato(a->der, dato);
    else
        res = numDato(a->izq, dato) + numDato(a->der, dato);
    return res;
}

// El contenido de un árbol binario corresponde a un árbol genealógico(Ver imagen en la parte inferior), 
// de tal manera que para cada nodo el sucesor izquierdo es femenino y el sucesor derecho es masculino. 
// Escriba una función para mostrar todos los elementos femeninos que contiene un árbol de este tipo. 

void mostrarFemenino(AB a)
{
    if (!a)
        return;

    if (a->izq)
        printf("%s ", a->izq->info);

    mostrarFemenino(a->izq);
    mostrarFemenino(a->der);
}

// Un árbol binario se usa para representar una expresión aritmética como se muestra en la figura:
// Escribir una función que reciba un árbol de este tipo y calcule el resultado de la expresión 
// aritmética que representa. Nota: Las operaciones permitidas son +, -, * y /, además las cantidades pueden llevar decimales.

float evaluarExpresion(AB a) 
{
    float res = 0;

    if (!a)
        return 0;
    if (!a->izq && !a->der)
        res = atof(a->info);
    else 
    {
        float izq;
        float der;
        izq = evaluarExpresion(a->izq);
        der = evaluarExpresion(a->der);

        if (strcmp(a->info, "+") == 0)
            res = izq + der;
        else if (strcmp(a->info, "-") == 0)
            res = izq - der;
        else if (strcmp(a->info, "*") == 0)
            res = izq * der;
        else if (strcmp(a->info, "/") == 0)
            res = izq / der;
        else 
            res = 0;
    }
    return res;
}