#include <stdio.h>
#include <stdlib.h>

typedef struct nodoAB
{
    struct nodoAB *izq;
    int info;
    struct nodoAB *der;
} *AB;

int main()
{
    return 0;
}

int detIgual(AB a, AB b)
{
    int res;
    if(!a && !b)
        res = 1;
    else if(!a || !b || b->info != a->info)
        res = 0;
    else 
        res = detIgual(a->izq, b->izq) && detIgual(a->der, b->der);
    return(res);
}

int detPadreHijo(AB a, int padre, int hijo)
{
    int res;
    if(!a)
        res = 0;
    else if(padre == a->info)
        if((a->izq && hijo == a->izq->info) || (a->der && hijo == a->der->info))
            res = 1;
    else
        res = detPadreHijo(a->izq, padre, hijo) || detPadreHijo(a->der, padre, hijo);
    return(res);
}
