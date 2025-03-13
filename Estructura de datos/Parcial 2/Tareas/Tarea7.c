/* El programa debe incluir
Declaración de las estructuras
Funciones push, pop y capturaPila
Función para mostrar los datos de la pila. */

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int info;
    struct nodo *sig;
} *LISTA;

typedef struct 
{
    LISTA frente;
}PILA;

int creaNodo(LISTA *nuevo, int dato);
int pop(PILA *tope);
int push(PILA *tope, int dato);
void capLista(PILA *tope);
int sumaLis(PILA *tope);
void mostrarPila(PILA *tope);

int main() {
    PILA pila
    int suma;

    capLista(&pila);
    mostrarPila(&pila);
    suma = sumaLis(&pila);
    printf("Suma de los elementos es: %d \n", suma);
    return 0;
}

int creaNodo(LISTA *nuevo, int dato)
{
    int res=0;
    *nuevo = (LISTA)malloc(sizeof(struct nodo));
    if(*nuevo)
    {
        (*nuevo)->dato = dato;
        (*nuevo)->liga = NULL;
        res = 1;
    }
    return res;
}

int pop(PILA *tope)
{
    int res = 0;
    LISTA aux;
    if(*tope)
    {
        aux = tope->frente;
        tope->frente = aux->sig;
        free(aux);
        res = 1;
    }
    return res;
}

int push(PILA *tope, int dato)
{
    int res;
    LISTA nuevo;
    res = creaNodo(&nuevo, dato);
    if (res) {
        nuevo->sig = tope->frente;
        tope->frente = nuevo;
    }
    return res;
}

void capLista(PILA *tope)
{
    int dato, res;
    char resp;
    do
    {
        printf("El dato es: \n");
        scanf("%d", &dato);
        res = push(tope, dato);
        if(res)
        {
            printf("Ingresar otro dato? (s - n): \n");
            scanf("%c", res);
        } 
        else    
            printf("No hay memoria \n");
    } while (res && resp == 's');
    
}

int sumaLis(PILA *tope)
{
    int suma=0;
    LISTA aux;
    aux = *tope;
    if(aux)
    {
        while(aux)
        {
            suma += aux->info;
            aux = aux->sig;
        }
    }
    return suma;
}

void mostrarPila(PILA *tope) {
    LISTA aux;
    aux = tope->frente;
    if(aux) 
    {
        while(aux) 
        {
            printf("%d ", aux->info);
            aux = aux->sig;
        }
        printf("\n");
    }
}
