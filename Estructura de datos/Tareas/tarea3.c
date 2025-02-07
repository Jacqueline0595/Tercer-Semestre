#include <stdio.h>
#include <stdlib.h>
// Autora: Janelle Jacqueline Gomez Benitez
// Descripcion: Escriba un programa que contenga las funciones básicas para manejar 
// un apuntador a un apuntador a un apuntador a un dato de tipo unsigned.
// Notas: Usar %u  como especificador de tipo.

int asignaMem(unsigned ****ptr);
void asignaDato(unsigned ***ptr, unsigned dato);
void pideDato(unsigned ***ptr);
void muestraDato(unsigned ***ptr);
void aumentaUno(unsigned ***ptr);
void liberaMem(unsigned ***ptr);

int main()
{  
    unsigned ***apuntador;
    int res;
    res = asignaMem(&apuntador);
    if(res)
    {
        // Implicitamente ya tiene los 3 '*'
        asignaDato(apuntador, 25);
        muestraDato(apuntador);
        pideDato(apuntador);
        muestraDato(apuntador);
        aumentaUno(apuntador);
        muestraDato(apuntador);
        liberaMem(apuntador);
    }

    return 0;
}

// el cuarto '*' es porque pasa por referencia el puntero
int asignaMem(unsigned ****ptr)
 
{
    int res=0;
    *ptr = (unsigned ***)malloc(sizeof(unsigned **));
    if(*ptr)
    {
        **ptr = (unsigned **)malloc(sizeof(unsigned *));
        if(**ptr)
        {
            ***ptr = (unsigned *)malloc(sizeof(unsigned));
            if(***ptr)
                res = 1;
            else
                free(**ptr);
        } else
            free(*ptr);
    }
    return res;
}

void asignaDato(unsigned ***ptr, unsigned dato)
{
    ***ptr = dato;
}

void pideDato(unsigned ***ptr)
{
    printf("Dame un dato: \n");
    scanf("%u", **ptr);
}

void muestraDato(unsigned ***ptr)
{
    printf("El dato del puntero es: %u \n", ***ptr);
}

void aumentaUno(unsigned ***ptr)
{
    (***ptr)++;
}

void liberaMem(unsigned ***ptr)
{
    free(ptr);
}
