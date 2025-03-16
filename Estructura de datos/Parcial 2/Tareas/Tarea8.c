/* El programa debe incluir
Declaración de la(s) estructura(s)
Funciones enQueue, deQueue y capturaQueue
Función para mostrar los datos del queue */

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int info;
    struct nodo *liga;
} *COLA;

typedef struct
{
    COLA frente;
    COLA final;
} COLA_CA;

void iniQueue(COLA_CA *queue);
int creaNodo(COLA *nuevo, int dato);
int insFinal(COLA_CA *queue, int dato);
int elimFinal(COLA_CA *queue, int *dato);
void captura(COLA_CA *queue);
void imprimir(COLA_CA *queue);

int main() 
{
    int dato, res;
    COLA_CA queue;
    iniQueue(&queue);
    captura(&queue);
    imprimir(&queue);
    res = elimFinal(&queue, &dato);
    if(res)
    {
        printf("Dato eliminado: %d \n", dato);
        imprimir(&queue);
    }
    return 0;
}

void iniQueue(COLA_CA *queue)
{
    queue->frente = NULL;
    queue->final = NULL;
}

int creaNodo(COLA *nuevo, int dato)
{
    int res=0;
    *nuevo = (COLA)malloc(sizeof(struct nodo));
    if(*nuevo)
    {
        (*nuevo)->info = dato;
        (*nuevo)->liga = NULL;
        res = 1;
    }
    return res;
}

int insFinal(COLA_CA *queue, int dato)
{
    int res;
    COLA nuevo;
    res = creaNodo(&nuevo, dato);
    if(res)
    {
        if(!queue->frente)
            queue->frente = nuevo;
        else    
            queue->final->liga = nuevo;
        queue->final = nuevo;
    }
    return res;
}

int elimFinal(COLA_CA *queue, int *dato)
{
    int res = 0;
    COLA aux;
    if(queue->frente)
    {
        aux = queue->frente;
        *dato = aux->info;
        queue->frente = queue->frente->liga;
        free(aux);
        if(!queue->frente)
            queue->final = NULL;
        res = 1;
    }
    return res;
}

void captura(COLA_CA *queue)
{
    int dato, res;
    char resp;
    do
    {
        printf("Ingresa un dato: \n");
        scanf("%d", &dato);
        res = insFinal(queue, dato);
        if(res)
        {
            printf("Ingresar otro dato? (s - n): \n");
            scanf(" %c", &resp);
        } 
        else    
        {
            printf("No hay memoria \n");
            resp = 'n';
        }
    } while (res && resp == 's');
}

void imprimir(COLA_CA *queue)
{
    COLA aux;
    if(queue->frente)
    {
        aux = queue->frente;
        while(aux)
        {
            printf("%d ", aux->info);
            aux = aux->liga;
        }
        printf("\n");
    }
}