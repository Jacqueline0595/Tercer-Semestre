#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo 
{
    int dato;
    struct Nodo *sig;
} *LISTA;

int crearNodo(LISTA *nuevo, int dato);
int insertar(LISTA *cab, int dato);
void mostrar(LISTA cab);

int main() 
{
    LISTA lista = NULL;
    insertar(&lista, 10);
    insertar(&lista, 20);
    insertar(&lista, 30);
    mostrar(lista);
    return 0;
}

int crearNodo(LISTA *nuevo, int dato) 
{
    int res = 0;
    *nuevo = (LISTA)malloc(sizeof(struct Nodo));
    if (*nuevo) 
    {
        (*nuevo)->dato = dato;
        (*nuevo)->sig = *nuevo;
        res = 1; 
    }
    return res;
}

int insertar(LISTA *cab, int dato) 
{
    int res;
    LISTA nuevo, aux;
    res = crearNodo(&nuevo, dato)
    if (res)    
    {
        if (!*cab) 
            *cab = nuevo; 
        else 
        {
            aux = *cab;
            while (aux->sig != *cab) 
                aux = aux->sig;
            
            aux->sig = nuevo;
            nuevo->sig = *cab;
        }
    }
    return res;
}

int insertar(LISTA *cab, int dato) 
{
    LISTA nuevo, ultimo;
    int res = crearNodo(&nuevo, dato);
    if (res) 
    {
        if (!*cab) 
            *cab = nuevo;
        else 
        {
            ultimo = (*cab)->sig;
            ultimo->sig = nuevo;
            nuevo->sig = *cab;
        }
    }
    return res;
}

void mostrar(LISTA cab) 
{
    if (!cab) return;
    
    LISTA aux = cab;
    do 
    {
        printf("%d ", aux->dato);
        aux = aux->sig;
    } while (aux != cab);
    printf("\n");
}
