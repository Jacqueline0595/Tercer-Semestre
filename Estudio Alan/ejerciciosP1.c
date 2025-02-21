#include <stdio.h>

void acomoda(int arre[], int arre2[], int n);
void imprime(int arr[], int n);
int sumaArr(int arr[], int n);

int main()
{
    int arreglo1[] = {2, 3, 9, 7, 1, 6, 2, 3, 9};
    int arreglo2[9];
    int arreglo[] = {4, 6, 4, 2, 6, 4, 2, 9, 8};
    int n = 9;
    imprime(arreglo1, n);
    acomoda(arreglo1, arreglo2, n);
    imprime(arreglo2, n);

    imprime(arreglo, n);
    sumaArr(arreglo, n);
    imprime(arreglo, n);
    return 0;
}

void acomoda(int arre[], int arre2[], int n)
{
    // Variables
    int i, j=0;

    for(i=0; i<n; i++)
    {
        // Verifica que sea par
        if(arre[i] % 2 == 0)
        {
            arre2[j] = arre[i];
            j++;
        }
    }

    // Acomoda los impares 
    for(i=0; i<n; i++)
    {
        // Verifica que sea par
        if(arre[i] % 2 != 0)
        {
            arre2[j] = arre[i];
            j++;
        }
    }
}

int sumaArr(int arr[], int n) {
    int num, res;
    if (n <= 1)
        return arr[n - 1];

    num = arr[n - 2] + arr[n - 1];
    arr[n - 2] = num;

    res = sumaArr(arr, n - 1);
    return res;
}



void imprime(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}