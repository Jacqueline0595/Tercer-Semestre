#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int hh;
    int mm;
} Tiempo;

void imprime_arreglo(Tiempo b[], int n);

int main()
{
    Tiempo t[] = {
        {8, 0},
        {10, 15},
        {12, 30}
    };
    int m = sizeof(t)/sizeof(t[0]);
    imprime_arreglo(t, m);

    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a)/sizeof(a[0]);
    printf("El tamanio de un elemento del arreglo es %llu \n", sizeof(a)[0]);
    printf("El tamanio del arreglo es %llu \n", sizeof(a));
    printf("El arreglo tiene %llu elementos \n", sizeof(a)/sizeof(a[0]));

    int *pt = a; // el nombre del arreglo es una direccion de memoria
    printf("El tamnio del apuntador es %llu \n", sizeof(pt)); // tamaño del apuntador
    printf("El tamnio del contenido del apuntador es %llu \n", sizeof(*pt)); // tamaño de lo que contiene la direccion de memoria

    printf("Impresion del arreglo 'tracicional' \n");
    printf("La direccion del arreglo es: %p \n", a);
    printf("\n");
    for(int i=0; i<n; i++)
    {
        printf("El elemento %d esta en la direccion %p y tiene valor %d \n", i, &a[i], a[i]);
        // Las dos son equivalentes
        // a[i] <---> *(a+i)
        // &a[i] <---> a+i 
        // printf("El elemento %d esta en la direccion %p y tiene valor %d \n", i, a+i, *(a+i));
    }
    printf("\n");
    printf("Impresion del arreglo con apuntadores \n");
    printf("La direccion del arreglo es: %p \n", pt);
    printf("\n");
    for(int i=0; i<n; i++)
    {
        printf("El elemento %d esta en la direccion %p y tiene valor %d \n", i, pt+i, *(pt+i)); // "*algo" es el contenido de la direccion
        // *(pt+i) <---> pt[i]
        // pt+i <---> *(pt[i])
        // printf("El elemento %d esta en la direccion %p y tiene valor %d \n", i, &pt[i], pt[i]); 
    }
    printf("\n");
    return 0;
}

void imprime_arreglo(Tiempo b[], int n)
{
    printf("El contenido del arreglo es: \n");
    for (int i =0; i<n; i++)
    {
        printf("Horas: %d, minutos: %d \n", (*(b+i)).hh, (*(b+i)).mm); 
        // (*(b+i)).hh equivale a (b+i)->hh
        printf("Horas: %d, minutos: %d \n", (b+i)->hh, (b+i)->mm); // esta es la notacion que se estara usando
    }
}