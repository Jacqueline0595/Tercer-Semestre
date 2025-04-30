#include <stdio.h>
#include <math.h>
#define BMAX 5
#define NMAX 100000

int main(){
    int b, n, wp[2][BMAX], abc[3][NMAX];
    float area = 0;

    scanf("%d %d", &b, &n);

    for(int i = 0; i < b; i++){
        scanf("%d %d", wp[0][i], wp[1][i]);
    }
    
    for(int i = 0; i < b; i++){
        scanf("%d %d %d", abc[0][i], abc[1][i], abc[2][i]);
    }

    for(int i = 0; i < n; i++){
        float s = (abc[0][i] + abc[1][i] + abc[2][i]) / 2;
        area += sqrt(s*(s-abc[0][i])*(s-abc[1][i])*(s- abc[2][i]));
    }

    
}