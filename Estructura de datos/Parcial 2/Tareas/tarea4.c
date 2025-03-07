#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct nodoMono
{
  float coef;
  int expo;
  struct nodoMono *sigMono;
} *MONO;

int evaluaRec(MONO cab, int equis)
{
    int res;
    if(!cab)
        res = 0;
    else {
        res = cab->coef * pow(equis, cab->expo) + evaluaRec(cab->sigMono, equis);
    }
    return res;
}


typedef struct nodoGen
{
  // caracter, entero, flotante
  char nomTipo[10];
  int tipo; // 1-char, 2-int, 3-float
  void *info;
  struct nodoGen *sigGen;
} *GEN;

void suma(GEN cab, float *suma)
{
  if(!cab)
    *suma = 0;
  else {
    suma(cab->sigGen);
    if(cab->tipo == 2)
      *suma += *(int *)(cab->info);
    else if(cab->tipo == 3)
      *suma += *(float *)(cab->info);
  }
}

float sumaRec(GEN cab) {
  if (!cab) return 0; 

  float suma = 0;

  
  if (cab->tipo == 2) 
      suma = *(int *)(cab->info);
  else if (cab->tipo == 3) 
      suma = *(float *)(cab->info);

  return suma + sumaRec(cab->sigGen);
}