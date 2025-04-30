#include <stdio.h>
#define TMAX 100000

int main()
{
    int t, ij[2][TMAX];
    scanf("%d", &t);

    for(int i = 0; i < t; i++)
    {
        scanf("%d %d", &ij[0][i], &ij[1][i]);
        int cont = 0; 
        for(int k = ij[0][i]; k <= ij[1][i]; k++){
            int cont2 = 0;
            for(int j = 2; j < k; j++){
              if(k%2 == 0) cont2++;
            }
            if(cont2 == 0) cont++;
        }
        printf("%d\n", cont);
    }
}