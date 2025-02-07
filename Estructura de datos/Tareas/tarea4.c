#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NChar 26
#define NClave 5

typedef struct
{
    char clave[NClave+1];
    char nombre[NChar+1];
    float totVen;
    float suelBas;
    float comision;
    float suelNet;
} VENDE;

int asignaMem(VENDE **ptrVen);
void asignaDatos(VENDE *ptrVen, char clav[], char nom[], float total, float sueldo);
void captura(VENDE *ptrVen);
void muestraDatos(VENDE *ptrVen);
void calculoComi(VENDE *ptrVen);
void claculoSueldo(VENDE *ptrVen);
void liberaMem(VENDE *ptrVen);

int main()
{
    VENDE *punteroV;
    int res;
    res = asignaMem(&punteroV);
    if(res)
    {
        printf("--- Datos asignados previamente --- \n\n");
        asignaDatos(punteroV, "A7843", "Jacqueline", 1000, 250);
        calculoComi(punteroV);
        claculoSueldo(punteroV);
        muestraDatos(punteroV);
        printf("\n\n--- Ingrese datos de un vendedor --- \n\n");
        captura(punteroV);
        calculoComi(punteroV);
        claculoSueldo(punteroV);
        muestraDatos(punteroV);
        liberaMem(punteroV);
    }
    return 0;
}

int asignaMem(VENDE **ptrVen) // Porque modifica la direccion de memoria del puntero
{
    int res = 0;
    *ptrVen = (VENDE *)malloc(sizeof(VENDE));
    if(*ptrVen)
        res = 1;
    return res;
}

void asignaDatos(VENDE *ptrVen, char clav[], char nom[], float total, float sueldo) // Un asterisco porque se quiere modificar la estructura
{
    strcpy(ptrVen->clave, clav);
    strcpy(ptrVen->nombre, nom);
    ptrVen->totVen = total;
    ptrVen->suelBas = sueldo;
    ptrVen->comision = 0;
    ptrVen->suelNet = 0;
}

void captura(VENDE *ptrVen) 
{
    do{
        printf("Introduce tu clave: \n");
        // gets(ptrVen->clave); // Marca un warning de seguridad
        fflush(stdin);
        fgets(ptrVen->clave, 6, stdin);
        ptrVen->clave[strcspn(ptrVen->clave, "\n")] = '\0';

        if(strlen(ptrVen->clave) > 5 || strlen(ptrVen->clave) == 0)
            printf("Clave invalida, introducela de nuevo \n");
    } while(strlen(ptrVen->clave) > 5 || strlen(ptrVen->clave) == 0);
    fflush(stdin);
    printf("Introduce tu nombre: \n");
    fflush(stdin);
    // gets(ptrVen->nombre);
    fgets(ptrVen->nombre, 25, stdin);
    *(strchr(ptrVen->nombre, '\n')) = '\0';
    printf("Introduce el total de ventas: \n");
    scanf("%f", &ptrVen->totVen);
    printf("Introduce tu sueldo base: \n");
    scanf("%f", &ptrVen->suelBas);
    ptrVen->comision = 0;
    ptrVen->suelNet = 0;
}

void muestraDatos(VENDE *ptrVen)
{
    printf("\t --- Datos del vendedor --- \n\n");
    printf("La clave del vendedor %s es: %s \n", ptrVen->nombre, ptrVen->clave);
    printf("Su total de ventas es: %.2f \n", ptrVen->totVen);
    printf("Su sueldo base es: $%.2f \n", ptrVen->suelBas);
    printf("La comision es: %.0f%% \n", ptrVen->comision * 100);
    printf("El sueldo neto es de: $%.2f \n", ptrVen->suelNet);
}

void calculoComi(VENDE *ptrVen)
{
    if(ptrVen->totVen > 0 && ptrVen->totVen <= 1000)
        ptrVen->comision = 0.10;
    else if(ptrVen->totVen >= 1001 && ptrVen->totVen <= 3000)
        ptrVen->comision = 0.13;
    else if(ptrVen->totVen >= 3001 && ptrVen->totVen <= 7000)
        ptrVen->comision = 0.18;
    else if(ptrVen->comision > 7000)
        ptrVen->comision = 0.21;
    else 
        ptrVen->comision = 0;
}

void claculoSueldo(VENDE *ptrVen)
{
    ptrVen->suelNet = (ptrVen->totVen * ptrVen->comision) + ptrVen->suelBas;
}

void liberaMem(VENDE *ptrVen)
{
    free(ptrVen);
}