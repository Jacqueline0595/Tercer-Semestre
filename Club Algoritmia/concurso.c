#include <stdio.h>

int main()
{
    int a, b, c = 0, n;

    scanf("%d", &n);

    for(int i = 0; i<n; i++)
    {
        scanf("%d %d", &a, &b);

        if(a >= 1 && b <= 10)
        {
            c = (c-a) + (b-c);
        
            printf("%d \n", c);
        }
    }
    return 0;
}