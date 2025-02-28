#include <stdio.h>
#include <stdlib.h>
// Autora: Janelle Jacqueline Gomez Benitez
// Descripcion: Programa para manejar un arreglo bidimensional dinámico de estructuras alumno.

typedef struct
{
    char clave[6];
    char nombre[26];
    float calif1;
    float calif2;
    float calif3;
    float prom;
} ALU;

int asignaRen();
int asignaCol();
int asignaMem(ALU ***ptrArrBiAlu, int ren, int col);
void captura(ALU **ptrArrBiAlu, int ren, int col);
void calculoProm(ALU **ptrArrBiAlu, int ren, int col);
void muestraArr(ALU **ptrArrBiAlu, int ren, int col);
void liberaMem(ALU ***ptrArrBiAlu, int ren);

int main()
{
    ALU **puntero;
    int nr, nc, res;
    nr = asignaRen();
    nc = asignaCol();

    res = asignaMem(&puntero, nr, nc);
    if(res)
    {
        printf("Ingrese los datos\n");
        captura(puntero, nr, nc);
        calculoProm(puntero, nr, nc);
        muestraArr(puntero, nr, nc);
        liberaMem(&puntero, nr);
    }
    return 0;
}

int asignaRen()
{
    int ren;
    printf("Cuantos renglones deseas? \n");
    scanf("%d", &ren);
    return ren;
}

int asignaCol()
{
    int col;
    printf("Cuantas columnas deseas? \n");
    scanf("%d", &col);
    return col;
}

int asignaMem(ALU ***ptrArrBiAlu, int ren, int col)
{
    int cont, res = 0;

    *ptrArrBiAlu = (ALU **)malloc(ren * sizeof(ALU *));
    if (*ptrArrBiAlu)
    {
        res = 1;
        for (cont = 0; cont < ren; cont++)
        {
            *(*ptrArrBiAlu + cont) = (ALU *)malloc(col * sizeof(ALU));
            if (!(*ptrArrBiAlu)[cont])
            {
                while (--cont >= 0)
                    free((*ptrArrBiAlu)[cont]);
                free(*ptrArrBiAlu);
                res = 0;
                break;
            }
        }
    }
    return res;
}

void captura(ALU **ptrArrBiAlu, int ren, int col)
{
    int contR, contC;
    for(contR = 0; contR < ren; contR++)
        for(contC = 0; contC < col; contC++)
        {
            printf("Clave del alumno: \n");
            fflush(stdin);
            // gets((*(ptrArrBiAlu + contR) + contC)->clave);
            fgets((*(ptrArrBiAlu + contR) + contC)->clave, 5, stdin);
            printf("Nombre del alumno: \n");
            fflush(stdin);
            // gets((*(ptrArrBiAlu + contR) + contC)->nombre);
            fgets((*(ptrArrBiAlu + contR) + contC)->nombre, 25, stdin);
            printf("Calificacion 1: \n");
            scanf("%f", &(*(ptrArrBiAlu + contR) + contC)->calif1);
            printf("Calificacion 2: \n");
            scanf("%f", &(*(ptrArrBiAlu + contR) + contC)->calif2);
            printf("Calificacion 3: \n");
            scanf("%f", &(*(ptrArrBiAlu + contR) + contC)->calif3);
            (*(ptrArrBiAlu + contR) + contC)->prom = 0;
        }
}

void calculoProm(ALU **ptrArrBiAlu, int ren, int col)
{
    int contR, contC;
    for(contR = 0; contR < ren; contR++)
    {
        for(contC = 0; contC < col; contC++)
        {
            (*(ptrArrBiAlu + contR) + contC)->prom = (*(ptrArrBiAlu + contR) + contC)->calif1 + (*(ptrArrBiAlu + contR) + contC)->calif2 + (*(ptrArrBiAlu + contR) + contC)->calif3;
            (*(ptrArrBiAlu + contR) + contC)->prom /= 3;
        }
    }
}

void muestraArr(ALU **ptrArrBiAlu, int ren, int col)
{
    int contR, contC;
    for(contR = 0; contR < ren; contR++)
    {
        for(contC = 0; contC < col; contC++)
        {
            printf("Clave del alumno: %s \n", (*(ptrArrBiAlu + contR) + contC)->clave);
            printf("Nombre del alumno: %s \n", (*(ptrArrBiAlu + contR) + contC)->nombre);
            printf("Calificacion 1: %.2f \n", (*(ptrArrBiAlu + contR) + contC)->calif1);
            printf("Calificacion 2: %.2f \n", (*(ptrArrBiAlu + contR) + contC)->calif2);
            printf("Calificacion 3: %.2f \n", (*(ptrArrBiAlu + contR) + contC)->calif3);
            printf("Promedio: %.2f \n", (*(ptrArrBiAlu + contR) + contC)->prom);
        }
    }
}

void liberaMem(ALU ***ptrArrBiAlu, int ren)
{
    while (--ren >= 0)
        free(*(*ptrArrBiAlu + ren));
    free(*ptrArrBiAlu);
}