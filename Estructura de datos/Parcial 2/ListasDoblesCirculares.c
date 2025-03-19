#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo 
{
    int dato;
    struct Nodo *sig;
    struct Nodo *ant;
} *LISTA;

typedef struct
{
    LISTA pri;
    LISTA ult;
} LISTA_DBL;

int crearNodo(LISTA *nuevo, int dato);
int insertar(LISTA_DBL *lista, int dato);
void mostrar(LISTA_DBL lista);

int main() 
{
    LISTA_DBL lista = {NULL, NULL};
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
        (*nuevo)->sig = (*nuevo)->ant = *nuevo;
        res = 1; 
    }
    return res;
}

int insertar(LISTA_DBL *lista, int dato) 
{
    LISTA nuevo;
    int res;
    res = crearNodo(&nuevo, dato);
    if (res) 
    {
        if (!lista->pri) 
        {
            lista->pri = lista->ult = nuevo;
        } 
        else 
        {
            nuevo->ant = lista->ult;
            nuevo->sig = lista->pri;
            lista->ult->sig = nuevo;
            lista->pri->ant = nuevo;
            lista->ult = nuevo;
        }
    }
    return res;
}

void mostrar(LISTA_DBL lista) 
{
    LISTA aux;
    if (lista.pri) 
    {
        aux = lista.pri;
        do 
        {
            printf("%d ", aux->dato);
            aux = aux->sig;
        } while (aux != lista.pri);
        printf("\n");
    }
}
