#include <stdio.h>
#include <stdlib.h>
// Autora: Janelle Jacqueline Gomez Benitez
// Descripcion: Escriba un programa para manejar un arreglo bidimensional dinámico de datos de tipo signed long int.
// Nota: Usar %ld como especificador de tipo

int asignaMem(signed long int **ptrArr, int n);
void asignaDato(signed long int *ptrArr, int n, signed long int dato);
void redimencionaArr(signed long int **ptrArr, int *nNew);
void muestraArr(signed long int *ptrArr, int n);
void liberaMem(signed long int **ptrArr);

int main()
{
    signed long int *punteroArreglo;
    int res, n = 10;
    res = asignaMem(&punteroArreglo, n);
    if(res)
    {
        printf("\t --- Arreglo con datos asignados previamente --- \n");
        asignaDato(punteroArreglo, n, 9);
        muestraArr(punteroArreglo, n);
        printf("\n\n");
        printf("\t --- Nuevo arreglo --- \n");
        liberaMem(&punteroArreglo);
        redimencionaArr(&punteroArreglo, &n);
        muestraArr(punteroArreglo, n);
        liberaMem(&punteroArreglo);
    }
    return 0;
}

int asignaMem(signed long int **ptrArr, int n)
{
    int res = 0;
    *ptrArr = (signed long int *)malloc(n * sizeof(signed long int));
    if(*ptrArr)
        res = 1;
    return res;
}

void asignaDato(signed long int *ptrArr, int n, signed long int dato)
{
    signed long int cont;
    for(cont = 0; cont < n; cont++)
        *(ptrArr + cont) = dato;
}

void redimencionaArr(signed long int **ptrArr, int *nNew)
{
    signed long int num, cont;
    printf("Cual es el nuevo tamanio del arreglo? \n");
    scanf("%d", nNew);
    *ptrArr = (signed long int *)malloc(*nNew * sizeof(signed long int));
    if(*ptrArr)
    {
        for(cont = 0; cont < *nNew; cont++)
        {
            printf("Dame el numero %ld \n", (cont +1));
            scanf("%ld", &num);
            *(*ptrArr + cont) = num;
        }
    }
}

void muestraArr(signed long int *ptrArr, int n)
{
    signed long int cont;
    for(cont = 0; cont < n; cont++)
        printf("[%ld] ", *(ptrArr + cont));
    printf("\n");
}

void liberaMem(signed long int **ptrArr)
{
    free(*ptrArr);
    *ptrArr = NULL;
}