#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoFracc
{
    int num;
    int den;
    struct nodoFracc *sigFracc; 
} *FRACC;

void iniLista(LISTA *cab); 
int creaNodo(LISTA *nuevo, int dato);
int insIni(LISTA *cab, int dato);
int llenaLista(LISTA *cab);
int elimFinalRec(LISTA* cab);
void muestraLista(LISTA cab); 

int main()
{
    LISTA lis;
    int res;
    iniLista(&lis);
    res = llenaLista(&lis);
    muestraLista(lis);
    elimFinalRec(&lis);
    return 0;
}

void iniLista(LISTA *cab)
{
    *cab=NULL;
}


int insIni(LISTA *cab, int dato)
{
    int res;
    LISTA nuevo;
    res = creaNodo(&nuevo, dato);
    if(res)
    {
        nuevo->liga=*cab;
        *cab=nuevo;
    }
    return res;
}

int creaNodo(FRACC *nuevo, int num, int den)
{
    int res=0;
    *nuevo = (FRACC)malloc(sizeof(struct nodoFracc));
    if(*nuevo)
    {
        (*nuevo)->num = num;
        (*nuevo)->den = den;
        (*nuevo)->sigFracc = NULL;
        res = 1;
    }
    return res;
}


typedef struct nodoFracc
{
    int num;
    int den;
    struct nodoFracc *sigFracc; 
} *FRACC;

int sumaFracciones(FRACC cab, int *nTot, int *dTot)
{
    int num, den, res = 0;

    if(cab)
    {
        *nTot = cab->num;
        *dTot = cab->den;
        cab = cab->sigFracc;
        while(cab)
        {
            num = cab->num;
            den = cab->den;
            *nTot = (*nTot)*den + num*(*dTot);
            *dTot *= den;
            cab = cab->sigFracc;
        }
        res = 1;
    }
    return res;
}

int llenaLista(LISTA *cab)
{
    int dat, res;
    char sig = 's';
    do
    {
        printf("Dato: \n");
        scanf("%d", &dat);
        res = insIni(cab, 5);
        if(res)
        {
            printf("Otro \n");
            scanf(" %c", &sig);
            sig = 'n';
        } 
    } while(sig != 'n' && res);
    return res;
}

void muestraLista(LISTA cab)
{
    while(cab)
    {
        printf("%d \n", cab->dato);
        cab=cab->liga;
    }
}

int elimFinalRec(LISTA* cab)
{
    int res;
    if(!*cab)
        res = 0;
    else if(!(*cab)->liga)
    {
        free(*cab);
        *cab = NULL;
        res = 1;
    }
    else
        res = elimFinalRec(&(*cab)->liga);
    return (res);
}