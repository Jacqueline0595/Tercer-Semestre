#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodoMun
{
    float egMun;
    int pobMun;
    float dpMun;
    char *numMun;
    struct nodoMun *sigMun;
} *MUN;

typedef struct nodoEdo
{
    float egEdo;
    int pobEdo;
    float promPob;
    char *capEdo;
    char *numEdo;
    float promDp;
    MUN cabMun;
    struct nodoEdo *sigEdo;
} *EDO;

int main()
{
    return 0;
}

void iniList(EDO *cab)
{
    *cab = NULL;
}

int creaNodoMun(MUN *nuevo, float extG, int pob, char *nom)
{
    int res=0;
    *nuevo = (MUN)malloc(sizeof(struct nodoMun));
    if(*nuevo)
    {
        (*nuevo)->egMun = extG;
        (*nuevo)->pobMun = pob;
        strcpy((*nuevo)->numMun, nom);
        (*nuevo)->dpMun = 0;
        (*nuevo)->sigMun = NULL;
        res = 1;
    }
    return res;
}

int creaNodoEst(EDO *nuevoE, char *capital, char *nombre)
{
    int res=0;
    *nuevo = (EDO)malloc(sizeof(struct nodoEdo));
    if(*nuevo)
    {
        strcpy((*nuevoE)->capEdo, capital);
        strcpy((*nuevoE)->numEdo, nombre);
        (*nuevoE)->egEdo = 0;
        (*nuevoE)->pobMun = 0;
        (*nuevoE)->dpEdo = 0;
        (*nuevoE)->cabMun = NULL;
        (*nuevoE)->sigEdo = NULL;
        res = 1;
    }
    return res;
}

/* Con base en las estructuras de los  estados-municipios, 
suponga que la estructura de estado tiene un campo llamado promDp 
que representa el promedio de densidad de población del estado. 
Escriba una función iterativa para calcular y asignar el 
promedio de densidad de población de cada estado. */

void calculaDen(EDO cab)
{
    int cont;
    float prom;
    MUN aux;
    while(cab)
    {
        cont=0;
        prom=0;
        aux=cab->cabMun;
        while(aux)
        {
            prom+=aux->dpMun;
            cont++;
            aux=aux->sigMun;
        }
        prom/=cont;
        cab->promDp = prom;
        cab=cab->sigEdo;
    }
}

/* Con base en las estructuras de los  estados-municipios, 
suponga que la estructura de estado tiene un campo llamado promEg 
que representa el promedio de extensión geográfica del estado. 
Escriba una(s) función(es) recursiva(s)  para calcular y asignar 
el promedio de extensión geográfica de cada estado. */

void calculaPromGe(EDO cab)
{
    float prom;
    int num;
    if(cab)
    {
        num = 0;
        prom = calculaProm(cab->cabMun, &num);
        prom /= num;
        calculaPromGe(cab->sigEdo);
    }
}

int calculaProm(MUN cabM, int *cont)
{
    int sum;
    if(!cab)
    {
        sum=0;
        *cont=0;
    }
    else if(cab)
    {
        sum += cabM->egMun;
        (*cont)++;
        calculaProm(cabM->sigMun);
    }
    return sum;
}

/* Con base en las estructuras de los  estados-municipios, suponga que la 
estructura de estado tiene un campo llamado promPob que representa el 
promedio de población del estado. Escriba dos funciones iterativas  
para calcular y asignar el promedio de población de cada estado. */

void calculaPromPobEst(EDO cabE)
{
    float prom;
    int num;
    while(cabE)
    {
        num=0;
        prom = calculaPromPobMun(cabE->cabMun, &num);
        prom /= num;
        cabE->promPob = prom;
        cabE=cabE->sigEdo;
    }
}

int calculaPromPobMun(MUN cabM, int *num)
{
    int sum = 0;
    *num = 0;
    while(cabM)
    {
        sum += cabM->pobMun;
        (*num)++;
        cabM=cabM->sigMun;
    }
    return sum;
}