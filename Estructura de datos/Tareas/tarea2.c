#include <stdio.h>
// Autora: Janelle Jacqueline Gomez Benitez
// Descripcion: Escriba un programa para manejar un apuntador a un dato de tipo char.
// Notas: Para ver el valor al que apunta 'ptr' debemos poner un '*'
//        Al igual que cuando queremos modificar el valor al que apunta

int main()
{
    char *ptr;
    char letra;
    letra = 'j';
    ptr = &letra;
    printf("La letra es: %c \n", letra);
    printf("La letra del apuntador es: %c \n", *ptr);
    // Cambio del valor

    *ptr = 'k';
    printf("La letra es: %c \n", letra);
    printf("La letra del apuntador es: %c \n", *ptr);
    return 0;
}