#include <stdio.h>
#include <stdlib.h>

int asignaMem(int **ptr);
void asignaDat(int *ptr, int dato);
void pideDato(int *ptr);
void muestraDato(int *ptr);
void aumentaDato(int *ptr);
void liberaMem(int *ptr);

//prueba

int main()
{
    int *apuntador;
    int res;
    res = asignaMem(&apuntador);
    if(res)
    {
        asignaDat(apuntador, 100);
        muestraDato(apuntador);
        pideDato(apuntador);
        muestraDato(apuntador);
        aumentaDato(apuntador);
        muestraDato(apuntador);
        liberaMem(apuntador);
    } else
    printf("No hay memoria \n");
    return 0;
}

int asignaMem(int **ptr)
{
    int res;
    *ptr = (int *)malloc(sizeof(int));
    if(*ptr)
        res = 1;
    return res;
}

void asignaDat(int *ptr, int dato)
{
    *ptr = dato;
}

void pideDato(int *ptr)
{
    printf("Introduce un numero: \n");
    scanf("%d", ptr);
}

void muestraDato(int *ptr)
{
    printf("El dato es: %d \n", *ptr);
}

void aumentaDato(int *ptr)
{
    (*ptr)++;
}

void liberaMem(int *ptr)
{
    free(ptr);
}