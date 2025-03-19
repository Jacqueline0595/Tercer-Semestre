#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
  int dato;
  struct nodo *sig;
} *LISTA;

void iniLista(LISTA *cab); 
int creaNodo(LISTA *nuevo, int dato);
int insIni(LISTA *cab, int dato);
int llenaLista(LISTA *cab);
int elimFinalRec(LISTA* cab);
void muestraLista(LISTA cab); 
int juntaListas(LISTA cab1, LISTA cab2, LISTA *uni);

int main()
{
    LISTA lis1 = NULL, lis2 = NULL, unidas = NULL;
    int res;
    iniLista(&lis1);
    iniLista(&lis2);
    printf("Llenado de la lista 1:\n");
    res = llenaLista(&lis1);
    printf("Llenado de la lista 2:\n");
    res = llenaLista(&lis2);

    printf("Lista 1:\n");
    muestraLista(lis1);
    printf("Lista 2:\n");
    muestraLista(lis2);
    
    res = juntaListas(lis1, lis2, &unidas);
    printf("Se hizo: %d\n", res);
    muestraLista(unidas);

    elimFinalRec(&lis1);
    elimFinalRec(&lis2);
    elimFinalRec(&unidas);

    return 0;
}

void iniLista(LISTA *cab)
{
    *cab = NULL;
}

int creaNodo(LISTA *nuevo, int dato)
{
    int res = 0;
    *nuevo = (LISTA)malloc(sizeof(struct nodo));
    if (*nuevo)
    {
        (*nuevo)->dato = dato;
        (*nuevo)->sig = NULL;
        res = 1;
    }
    else
    {
        printf("Error al asignar memoria.\n");
    }
    return res;
}

int insIni(LISTA *cab, int dato)
{
    int res;
    LISTA nuevo;
    res = creaNodo(&nuevo, dato);
    if (res)
    {
        nuevo->sig = *cab;
        *cab = nuevo;
    }
    return res;
}

int llenaLista(LISTA *cab)
{
    int dat, res;
    char sig = 's';
    do
    {
        printf("Dato: ");
        scanf("%d", &dat);
        res = insIni(cab, dat); 
        if (res)
        {
            printf("Otro (s/n)? ");
            scanf(" %c", &sig);
        } 
    } while (sig != 'n' && res);
    return res;
}

int elimFinalRec(LISTA *cab)
{
    int res;
    if (!*cab)
        res = 0;
    else if (!(*cab)->sig)
    {
        free(*cab);
        *cab = NULL;
        res = 1;
    }
    else
        res = elimFinalRec(&(*cab)->sig);
    return res;
}

void muestraLista(LISTA cab)
{
    while (cab)
    {
        printf("%d ", cab->dato);
        cab = cab->sig;
    }
    printf("\n");
}

int juntaListas(LISTA cab1, LISTA cab2, LISTA *uni)
{
    int res = 0, cont = -1;
    *uni = NULL;
    LISTA aux1 = cab1, aux2;

    if(cab1 && cab2)
    {
        while(aux1 != NULL)
        {
            aux2 = cab2;
            while(aux2 != NULL)
            {
                if(aux1->dato == aux2->dato && aux1->dato != cont)
                {
                    res = insIni(uni, aux1->dato);
                    cont = aux1->dato;
                }
                aux2 = aux2->sig;
            }
            aux1 = aux1->sig;
        }
    }
    return res;
}