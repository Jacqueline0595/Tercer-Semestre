/* Escribir una función iterativa para determinar si los datos en una lista están ordenados en forma ascendente. */

typedef struct nodo
{
    int dato;
    struct nodo *sig;
} *LISTA;

int determina(LISTA *cab)
{
    int res = 0, num;
    LISTA aux;
    if(*cab)
    {
        aux = *cab;
        num = aux->dato;
        aux = aux->sig;
        while(aux && num < aux->dato)
        {
            num = aux->num;
            aux = aux->sig;
        }
        if(!aux)
            res = 1;
    }
    return(res);
}

/* Escribir una función recursiva para determinar si dos listas son iguales.  */

int detIg(LISTA cab1, LISTA cab2)
{
    int res;
    if(!cab2 && !cab2)
        res = 1;
    else if(!cab2 || !cab2 || cab1->dato != cab2->dato)
        res = 0;
    else if(cab1->dato == cab2->dato)
        res = detIg(cab1->sig, cab2->sig);
    else
        res = 0;
    return res;
}

/* Escribir una función iterativa para determinar si dos listas son iguales.  */

int deterIg(LISTA cab1, LISTA cab2)
{
    int res = 1;
    while(cab1 && cab2 && res)
    {
        if(cab1->dato == cab1->dato)
        {
            cab1 = cab1->sig;
            cab2 = cab2->sig;
            res = 1;
        }
        else  
            res = 0;
    }
    return res;
}

/* Escribir una función recursiva para determinar si los datos en una lista están ordenados en forma ascendente. */

int detOrd(LISTA cab1)
{
    int res;
    if(!cab1 || !cab1->sig)
        res = 1;
    else if(cab1->dato > cab1->sig->dato)
        res = 0;
    res = detOrd(cab1->sig);
    return res;
}

/* Escriba una función recursiva para eliminar un dato de una lista simple, considerando que puede haber repetidos. */

int eliminaDato(LISTA *cab, int dato)
{
    int res;
    LISTA aux;
    if(!*cab)
        res = 0;
    else
    {
        res = eliminaDato(&(*cab)->sig, dato);
        
        if(dato == (*cab)->dato)
        {
            aux = *cab;
            *cab = aux->sig;
            free(aux);
            res = 1;
            res = eliminaDato(cab, dato);
        }
    }
    return(res);
}