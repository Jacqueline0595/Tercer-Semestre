#include <stdio.h>
#include <stdlib.h>
// Autora: Janelle Jacqueline Gomez Benitez
// Descripcion: Escriba un programa para manejar un arreglo unidimensional dinámico de datos de tipo long int.
// Nota: Usar %ld como especificador de tipo

int asignaMem(long int **ptrArr, int n);
void asignaDato(long int *ptrArr, int n, int dato);
void redimencionaArr(long int **ptrArr, int *nNew);
void muestraArr(long int *ptrArr, int n);
void liberaMem(long int **ptrArr);

int main()
{
    long int *punteroArreglo;
    int res, n = 9;
    res = asignaMem(&punteroArreglo, n);
    if(res)
    {
        printf("\t --- Arreglo con datos asignados previamente --- \n");
        asignaDato(punteroArreglo, n, 5);
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

int asignaMem(long int **ptrArr, int n)
{
    int res = 0;
    *ptrArr = (long int *)malloc(n * sizeof(long int));
    if(*ptrArr)
        res = 1;
    return res;
}

void asignaDato(long int *ptrArr, int n, int dato)
{
    long int cont;
    for(cont = 0; cont < n; cont++)
        *(ptrArr + cont) = dato;
}

void redimencionaArr(long int **ptrArr, int *nNew)
{
    long int num, cont;
    printf("Cual es el nuevo tamanio del arreglo? \n");
    scanf("%d", nNew);
    *ptrArr = (long int *)malloc(*nNew * sizeof(long int));
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

void muestraArr(long int *ptrArr, int n)
{
    long int cont;
    for(cont = 0; cont < n; cont++)
        printf("[%ld] ", *(ptrArr + cont));
    printf("\n");
}

void liberaMem(long int **ptrArr)
{
    free(*ptrArr);
    *ptrArr = NULL;
}