#include <stdio.h>
#include <sdtlib.h>

int leerMatriz(int *matriz[][], int *n);

int main()
{
    return 0;
}

int leerMatriz(int *matriz[][], int *n)
{
    FILE *matriz;
    int n;
    matriz = fopen("matriz.txt", "r");
    fread(&n, sizeof(int), 1, matriz);
    while(fread)

}