#include <stdio.h>
#include <assert.h>

int sumar(int a, int b)
{
    return a+b;
}

int factorial(int a)
{
    if(a > 0)
    {
        return factorial(a) * factorial(a-1);
    }
    else return 1;
}

void test_sumar()
{
    assert(sumar(2, 3)==5);
    assert(sumar(5, 0)==5);
    assert(sumar(-1, -1)==-2);
    assert(sumar(10, -4)==6);
    printf("Todas las pruebas pasaron");
}

void test_factorial()
{
    assert(factorial(0) == 1);
    assert(factorial(1) == 1);
    assert(factorial(5) == 120);
    assert(factorial(10) == 3628800);
    assert(factorial(-5) == 0);
    printf("Todas las pruebas pasaron");
}

int main()
{
    test_sumar();
    test_factorial();
}