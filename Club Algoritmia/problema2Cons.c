#include <stdio.h>
#include <string.h>

int main()
{
    int f, n, pos;
    int don[500] = {0};
    char sen[4];
    scanf("%d", &f);
    if(f >= 1 && f <= 100)
    {
        scanf("%d", &n);
        getchar(); 

        if(n >= 1 && n <= 500)
        {
            pos = 0; 
            for(int c=0; c<n; c++)
            {
                fgets(sen, sizeof(sen), stdin); 
                for(int i = 0; i < 3; i++) 
                {
                    if(sen[i] == '#')
                    {
                        if(pos < 500)
                            don[pos++] = i + 1;
                    }
                }
            }

            for(int i=0; i<n; i++)
            {
                printf("%d", don[i]);
            }
        }
    }
    return 0;
}
