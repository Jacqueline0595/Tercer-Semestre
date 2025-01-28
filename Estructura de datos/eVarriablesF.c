#include <stdio.h>

int modifica(int *rt);

int main()
{
    int a, b;
    int *pt, *qt;
    a = 10;
    pt = &a;
    printf("El valor de 'a' es: %d \n", a);
    printf("La direccion de 'a' es: %p \n", &a); // %p se utiliza para imprimir direcciones en hezxadecimal
    printf("El contenido del apuntador es: %d \n", *pt);
    printf("La direccion del apuntador es %p \n", pt);
    pt = &a; // deja de apuntar a 'a' y empieza a puntar a 'b'
    *pt = 20; // modifica el contenido de 'b'
    qt = pt; // Al hacer esto, 'qt' copia la direccion de 'pt' asi entonces apunta a 'b'
    *qt = 30;
    modifica(pt);
    printf("El contenido de 'b'  es: %d \n", b);
    printf("El valor de 'a' es: %d \n", a);
    return 0;
}

int modifica(int *rt)
{
    *rt = 100;
}