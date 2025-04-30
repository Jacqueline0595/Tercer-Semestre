#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct nodoEst
{
    int id;
    char nombre[50];
    float promedio;
    struct nodoEst *sig;
} *Estudiante;

typedef struct nodoCarre
{
    int clave;
    char nombre[50];
    Estudiante cabEstu;
    struct nodoCarre *sigCarre;
} *Carrera;

void iniCarre(Carrera *cabCarre);
int creaNodoEstu(Estudiante *nuEst, int idE, char *nomE, float promE);
int creaNodoCarre(Carrera *nuCar, int clv, char *nom);
int insCarreOrdIte(Carrera *cabCarre, int clv, char *nom);
int insCarreOrdRec(Carrera *cabCar, int clv, char *nom);
int insEstuOrdIt(Carrera cabCar, int id, char *nom, float prom, char *carrera);
int insEstOrdRec(Carrera cabCar, int id, char *nom, float prom, char *carrera);
int insEstCarrRec(Estudiante *cabEst, int id, char *nom, float prom);

void capturaCarrera(Carrera *cabCar);
void capturaEstudiante(Carrera cabCar);

void muestraLisLis(Carrera cabCar);
int eliminaEstudiante(Carrera cabCar, char *carrera, char *estudiante);
void eliminaEstudiantes(Estudiante *cabEstu);
int eliminaCarrera(Carrera *cabCar, char *carrera);
void eliminaCarreras(Carrera *cabCar);

int main()
{
    Carrera carre;
    char carrera[25], estudiante[25];
    int res;

    iniCarre(&carre);
    capturaCarrera(&carre);
    capturaEstudiante(carre);

    muestraLisLis(carre);
    fflush(stdin);
    printf("Ingresa la carrera de la que deseas elimnar un estudiante \n");
    fgets(carrera, 25, stdin);
    carrera[strcspn(carrera, "\n")] = '\0';
    fflush(stdin);
    printf("Ingresa el estudiante \n");
    fgets(estudiante, 25, stdin);
    estudiante[strcspn(estudiante, "\n")] = '\0';
    res = eliminaEstudiante(carre, carrera, estudiante);
    if(res)
        printf("Se pudo eliminar \n");
    else
        printf("No se pudo eliminar \n");
    muestraLisLis(carre);

    fflush(stdin);
    printf("Ingresa la carrera de la que deseas elimnar\n");
    fgets(carrera, 25, stdin);
    carrera[strcspn(carrera, "\n")] = '\0';
    res = eliminaCarrera(&carre, carrera);
    if(res)
        printf("Se pudo eliminar \n");
    else
        printf("No se pudo eliminar \n");
    muestraLisLis(carre);

    printf("Eliminar todo");
    eliminaCarreras(&carre);
    muestraLisLis(carre);
    return 0;
}

void iniCarre(Carrera *cabCarre)
{
    *cabCarre = NULL;
}

int creaNodoEstu(Estudiante *nuEst, int idE, char *nomE, float promE)
{
    int res=0;
    *nuEst = (Estudiante)malloc(sizeof(struct nodoEst));
    if(*nuEst)
    {
        (*nuEst)->id = idE;
        strcpy((*nuEst)->nombre, nomE);
        (*nuEst)->promedio = promE;
        (*nuEst)->sig = NULL;
        res = 1;
    }
    return(res);
}

int creaNodoCarre(Carrera *nuCar, int clv, char *nom)
{
    int res = 0;
    *nuCar = (Carrera)malloc(sizeof(struct nodoCarre));
    if(*nuCar)
    {
        (*nuCar)->clave = clv;
        strcpy((*nuCar)->nombre, nom);
        (*nuCar)->cabEstu = NULL;
        (*nuCar)->sigCarre = NULL;
        res = 1;
    }
    return(res);
}

int insCarreOrdIte(Carrera *cabCarre, int clv, char *nom)
{
    int res = 0;
    Carrera nuevo, ant, aux;
    aux = *cabCarre;
    while(aux && strcmp(nom, aux->nombre) > 0)
    {
        ant = aux;
        aux = aux->sigCarre;
    }
    if(!aux || strcmp(nom, aux->nombre) < 0)
    {
        res = creaNodoCarre(&nuevo, clv, nom);
        if(res)
        {
            nuevo->sigCarre = aux;
            if(aux == *cabCarre)
                *cabCarre = nuevo;
            else    
                ant->sigCarre = nuevo;
        }
    }
    return(res);
}

int insCarreOrdRec(Carrera *cabCar, int clv, char *nom)
{
    int res;
    Carrera nuevo;
    if(*cabCar && strcmp(nom, (*cabCar)->nombre)==0)
        res = 0;
    else if(!*cabCar || strcmp(nom, (*cabCar)->nombre) < 0)
    {
        res = creaNodoCarre(&nuevo, clv, nom);
        if(res)
        {
            nuevo->sigCarre = *cabCar;
            *cabCar = nuevo;
        }
    }
    else 
        res = insCarreOrdRec(&(*cabCar)->sigCarre, clv, nom);
    return(res);
}

int insEstuOrdIt(Carrera cabCar, int id, char *nom, float prom, char *carrera)
{
    int res = 0;
    Estudiante nuevo, ant, aux;
    while(cabCar && strcmp(carrera, cabCar->nombre) > 0)
        cabCar = cabCar->sigCarre;
    if(cabCar && strcmp(carrera, cabCar->nombre)==0)
    {
        aux = cabCar->cabEstu;
        while(aux && strcmp(nom, aux->nombre) > 0)
        {
            ant = aux;
            aux = aux->sig;
        }
        if(!aux || strcmp(nom, aux->nombre) < 0)
        {
            res = creaNodoEstu(&nuevo, id, nom, prom);
            if(res)
            {
                nuevo->sig = aux;
                if(aux == cabCar->cabEstu)
                    cabCar->cabEstu = nuevo;
                else   
                    ant->sig = nuevo;
            }
        }
    }
    return(res);
}

int insEstOrdRec(Carrera cabCar, int id, char *nom, float prom, char *carrera)
{
    int res;
    if(!cabCar && strcmp(nom, cabCar->nombre) < 0)
        res = 0;
    else if(cabCar && strcmp(nom, cabCar->nombre)==0)
        res = insEstCarrRec(&cabCar->cabEstu, id, nom, prom);
    else
        res = insEstOrdRec(cabCar->sigCarre, id, nom, prom, carrera);
    return(res);
}

int insEstCarrRec(Estudiante *cabEst, int id, char *nom, float prom)
{
    int res;
    Estudiante nuevo;
    if(*cabEst && strcmp(nom, (*cabEst)->nombre)==0)
        res = 0;
    else if(!*cabEst || strcmp(nom, (*cabEst)->nombre) < 0)
    {
        res = creaNodoEstu(&nuevo, id, nom, prom);
        if(res)
        {
            nuevo->sig = *cabEst;
            *cabEst = nuevo;
        }
    }
    else
        res = insEstCarrRec(&(*cabEst)->sig, id, nom, prom);
    return(res);

}

void capturaCarrera(Carrera *cabCar)
{
    int res;
    char resp;
    int clv;
    char nom[25];
    do
    {
        printf("Clave: \n");
        scanf("%d", &clv);
        fflush(stdin);
        printf("Ingrese un nombre: \n");
        fgets(nom, 25, stdin);
        nom[strcspn(nom, "\n")] = '\0';
        fflush(stdin);
        res = insCarreOrdIte(&(*cabCar), clv, nom);
        if(res)
        {
            printf("Dato añadido \n");
            printf("Otro? (s o n): \n");
            scanf("%c", &resp);
        }
        else
            printf("Dato no ingresado \n");
    } while (res && resp == 's');   
}

void capturaEstudiante(Carrera cabCar)
{
    int res, id;
    char resp, nom[25], carr[25];
    float prom;
    do
    {
        fflush(stdin);
        printf("Carrera deseada: \n");
        fgets(carr, 25, stdin);
        carr[strcspn(carr, "\n")] = '\0';
        printf("Id \n");
        scanf("%d", &id);
        fflush(stdin);;
        printf("Nombre \n");
        fgets(nom, 25, stdin);
        nom[strcspn(nom, "\n")] = '\0';
        printf("Promedio \n");
        scanf("%f", &prom);
        fflush(stdin);
        res = insEstuOrdIt(cabCar, id, nom, prom, carr);
        if(res)
        {
            printf("Dato añadido \n");
            printf("Otro? (s o n) \n");
            scanf("%c", &resp);
        }
        else 
            printf("Dato no ingresado \n");
    } while(res && resp == 's');
    
}

void muestraLisLis(Carrera cabCar)
{
    Estudiante aux;
    while(cabCar)
    {
        printf("Clave: %d, nombre: %s \n", cabCar->clave, cabCar->nombre);
        aux = cabCar->cabEstu;
        while(aux)
        {
            printf("\t Id: %d, nombre: %s, promedio: %.2f \n\n", aux->id, aux->nombre, aux->promedio);
            aux = aux->sig;
        }
        cabCar = cabCar->sigCarre;
    }
}

int eliminaEstudiante(Carrera cabCar, char *carrera, char *estudiante)
{
    int res = 0;
    Estudiante aux, elim;
    
    while(cabCar && strcmp(carrera, cabCar->nombre) > 0)
        cabCar = cabCar->sigCarre;
    if(cabCar && strcmp(carrera, cabCar->nombre)==0)
    {
        aux = cabCar->cabEstu;
        while(aux && strcmp(estudiante, aux->nombre) > 0)
            aux = aux->sig;
        if(aux && strcmp(estudiante, aux->nombre)==0)
        {
            elim = aux;
            aux = aux->sig;
            free(elim);
            res = 1;
        }
    }
    return(res);
}

void eliminaEstudiantes(Estudiante *cabEstu)
{
    Estudiante aux;
    if(!*cabEstu)
        printf("Lista de estudiantes vacia \n");
    while(*cabEstu)
    {
        aux = *cabEstu;
        *cabEstu = aux->sig;
        free(aux);
    }
}

int eliminaCarrera(Carrera *cabCar, char *carrera)
{
    int res = 0;
    Carrera ant, aux;
    aux = *cabCar;
    while(aux && strcmp(carrera, aux->nombre) > 0)
    {
        ant = aux;
        aux = aux->sigCarre;
    }
    if(aux && strcmp(carrera, aux->nombre)==0)
    {
        eliminaEstudiantes(&aux->cabEstu);
        if(aux == *cabCar)
            *cabCar = aux->sigCarre;
        else
            ant->sigCarre = aux->sigCarre;
        free(aux);
        res = 1;
    }
    return(res);
}

void eliminaCarreras(Carrera *cabCar)
{
    Carrera aux;
    if(!*cabCar)
        printf("Lista de carreras vacia \n");
    while(*cabCar)
    {
        eliminaEstudiantes(&(*cabCar)->cabEstu);
        aux = *cabCar;
        *cabCar = aux->sigCarre;
        free(aux);
    }
}
