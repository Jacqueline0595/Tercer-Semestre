#include <stdio.h>

int main()
{
    int a[] = {1, 2, 3, 4, 5};
    int n = sizeof(a)/sizeof(a[0]);
    printf("El tamanio de un elemento del arreglo es %llu \n", sizeof(a)[0]);
    printf("El tamanio del arreglo es %llu \n", sizeof(a));
    printf("El arreglo tiene %llu elementos \n", sizeof(a)/sizeof(a[0]));

    int *pt = a; // el nombre del arreglo es una direccion de memoria
    printf("El tamño del apuntador es %llu \n", sizeof(pt)); // tamaño del apuntador
    printf("El tamño del contenido del apuntador es %llu \n", sizeof(*pt)); // tamaño de lo que contiene la direccion de memoria

    printf("Impresion del arreglo 'tracicional' \n");
    for(int i=0; i<n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("Impresion del arreglo con apuntadores \n");
    for(int i=0; i<n; i++)
    {
        printf("%d ", *(pt+i));
    }
    printf("\n");
    return 0;
}