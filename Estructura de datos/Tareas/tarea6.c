#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Autora: Janelle Jacqueline Gomez Benitez
// Descripcion: Escriba un programa para manejar un arreglo unidimensional dinámico de estructuras cliente.
// Nota: Solo una vez hice personas aleatoriamente, espero no este mal. Solo debe decirle al programa cuantos clientes desea y el hara el resto :)

typedef struct{
    char clave[6];
    char nombre[26];
    char tipoCli[4];
    float totalCom;
    char compraFre[3];
    float totalPag;
} CLI;

int asignaMem(CLI **ptrArrCli, int n);
int asignaN();
void generaPersonas(char *clave, char *nombre, char *tipoC, float *totalCompra, char *compraF);
void asignaDatos(CLI *ptrArrCli, int n);
void calculaTotal(CLI *ptrArrCli, int n);
void muestraArreglo(CLI *ptrArrCli, int n);
void tipoCliente(CLI *ptrArrCli, int n);
float totalPagado(CLI *ptrArrCli, int n);
void liberaMem(CLI **ptrArrCli);

int main()
{
    CLI *puntero = NULL; 
    int res, n = 5;
    float total;
    res = asignaMem(&puntero, n);
    if(res)
    {
        srand(time(NULL));
        n = asignaN();
        printf("\t\t Datos generados aleatoriamente\n");
        asignaDatos(puntero, n);
        calculaTotal(puntero, n);
        muestraArreglo(puntero, n);
        tipoCliente(puntero, n);
        total = totalPagado(puntero, n);
        printf("\t\t El total pagado por todos los clientes es de %.2f \n", total);
        liberaMem(&puntero);
    }
    else
        printf("No se pudo almacenar memoria \n");
    return 0;
}

int asignaMem(CLI **ptrArrCli, int n)
{
    int res = 0;
    *ptrArrCli = (CLI *)malloc(n * sizeof(CLI));
    if(*ptrArrCli)
        res = 1;
    return res;
}

int asignaN()
{
    int num;
    printf("Cuantas personas deseas generar? \n");
    scanf("%d", &num);
    return num;
}

void generaPersonas(char *clave, char *nombre, char *tipoC, float *totalCompra, char *compraF)
{
    int numC, numN, numAP, numTCli, numCF;
    float numTC;

    char nombres[5][8] = {"Juan ", "Liz ", "Oliv ", "Danna ", "Diego "};
    char apellidoP[5][3] = {"G.", "H.", "L.", "G.", "M."};
    char claves[10][6] = {"A1234", "B5678", "C9101", "D2345", "E6789", "A3456", "B9876", "C1267", "D2367", "E4532"};
    char tipo[3][4] = {"B", "P", "VIP"};
    char compraFre[2][3] = {"S", "N"};

    numC = rand() % 10;
    strcpy(clave, claves[numC]);

    numN = rand() % 5;
    numAP = rand() % 5;
    strcpy(nombre, nombres[numN]);
    strncat(nombre, apellidoP[numAP], sizeof(nombre) - strlen(nombre) - 1);

    numTCli = rand() % 3;
    strcpy(tipoC, tipo[numTCli]);

    numTC = ((float)rand() / RAND_MAX) * 5000.0;
    *totalCompra = numTC;

    numCF = rand() % 2;
    strcpy(compraF, compraFre[numCF]);
}

void asignaDatos(CLI *ptrArrCli, int n)
{
    int cont;
    char clave[6], nombre[26], tipoCl[4], compra[2];
    float totalC;
    for(cont = 0; cont < n; cont++)
    {
        generaPersonas(clave, nombre, tipoCl, &totalC, compra);
        strcpy((ptrArrCli + cont)->clave, clave);
        strcpy((ptrArrCli + cont)->nombre, nombre);
        strcpy((ptrArrCli + cont)->tipoCli, tipoCl);
        (ptrArrCli + cont)->totalCom = totalC;
        strcpy((ptrArrCli + cont)->compraFre, compra);
        (ptrArrCli + cont)->totalPag = 0;
    }
}

void calculaTotal(CLI *ptrArrCli, int n)
{
    int cont;
    float descuento, descuentoAd;
    for(cont = 0; cont < n; cont++)
    {
        if(strcmp((ptrArrCli + cont)->tipoCli, "B") == 0)
            descuento = (ptrArrCli + cont)->totalCom * 0.08;
        else if(strcmp((ptrArrCli + cont)->tipoCli, "P") == 0)
            descuento = (ptrArrCli + cont)->totalCom * 0.13;
        else if(strcmp((ptrArrCli + cont)->tipoCli, "VIP") == 0)
            descuento = (ptrArrCli + cont)->totalCom * 0.18;
        else 
            descuento = 0;

        if(strcmp((ptrArrCli + cont)->compraFre, "S") == 0)
            descuentoAd = (ptrArrCli + cont)->totalCom * 0.05;
        else 
            descuentoAd = 0;

        (ptrArrCli + cont)->totalPag = (ptrArrCli + cont)->totalCom - descuento - descuentoAd;

    }
}

void muestraArreglo(CLI *ptrArrCli, int n)
{
    int cont;
    for(cont = 0; cont < n; cont++)
    {
        printf("\t --- Datos de la venta %d ---\n\n", cont + 1);
        printf("Clave: %s \n", (ptrArrCli + cont)->clave);
        printf("Nombre: %s \n", (ptrArrCli + cont)->nombre);
        printf("Tipo de cliente: %s \n", (ptrArrCli + cont)->tipoCli);
        printf("Total de la compra: %.2f\n", (ptrArrCli + cont)->totalCom);
        printf("Compra frecuente: %s \n", (ptrArrCli + cont)->compraFre);
        printf("Total a pagar: %.2f \n\n", (ptrArrCli + cont)->totalPag);
    }
}

void tipoCliente(CLI *ptrArrCli, int n)
{
    int cont, basico = 0, premium = 0, vip = 0;
    for(cont = 0; cont < n; cont++)
    {
        if(strcmp((ptrArrCli + cont)->tipoCli, "B") == 0)
            basico++;
        else if(strcmp((ptrArrCli + cont)->tipoCli, "P") == 0)
            premium++;
        else if(strcmp((ptrArrCli + cont)->tipoCli, "VIP") == 0)
            vip++;
    }
    printf("La cantidad de clientes de tipo basico es de %d \n", basico);
    printf("La cantidad de clientes de tipo premium es de %d \n", premium);
    printf("La cantidad de clientes de tipo VIP es de %d \n", vip);
}

float totalPagado(CLI *ptrArrCli, int n)
{
    int cont;
    float totalClientes = 0;
    for(cont = 0; cont < n; cont++)
    {
        totalClientes += (ptrArrCli + cont)->totalPag;
    }
    return totalClientes;
}

void liberaMem(CLI **ptrArrCli)
{
    free(*ptrArrCli);
    *ptrArrCli = NULL;
}
