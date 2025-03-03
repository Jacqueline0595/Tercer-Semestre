#include <stdio.h>
#include <stdlib.h>

// 5 minutos
typedef struct 
{
  int coef;
  char exp;
} POLI;


typedef struct nodo
{
  POLI dato;
  struct nodo *liga;
} *LISTA;


void iniLista(LISTA *cab); 
int creaNodo(LISTA *nuevo, int dato);
int insIni(LISTA *cab, int dato);
int llenaLista(LISTA *cab);
int elimFinalRec(LISTA* cab);
void muestraLista(LISTA cab); 

int main()
{
  LISTA lis;
  int res;
  iniLista(&lis);
  res = llenaLista(&lis);
  muestraLista(lis);
  elimFinalRec(&lis);
  return 0;
}

void iniLista(LISTA *cab)
{
  *cab=NULL;
}

int creaNodo(LISTA *nuevo, int dato)
{
  int res=0;
  *nuevo = (LISTA)malloc(sizeof(struct nodo));
  if(*nuevo)
  {
    (*nuevo)->dato = dato;
    (*nuevo)->liga = NULL;
    res = 1;
  }
  return res;
}

int insIni(LISTA *cab, int dato)
{
  int res;
  LISTA nuevo;
  res = creaNodo(&nuevo, dato);
  if(res)
  {
    nuevo->liga=*cab;
    *cab=nuevo;
  }
  return res;
}

int llenaLista(LISTA *cab)
{
  int dat, res;
  char sig = 's';
  do
  {
    printf("Dato: \n");
    scanf("%d", &dat);
    res = insIni(cab, 5);
    if(res)
    {
      printf("Otro \n");
      scanf(" %c", &sig);
      sig = 'n';
    } 
  } while(sig != 'n' && res);
  return res;
}

void muestraLista(LISTA cab)
{
  while(cab)
  {
    printf("%d \n", cab->dato);
    cab=cab->liga;
  }
}

int elimFinalRec(LISTA* cab)
{
  int res;
  if(!*cab)
    res = 0;
  else if(!(*cab)->liga)
  {
    free(*cab);
    *cab = NULL;
    res = 1;
  }
  else
    res = elimFinalRec(&(*cab)->liga);
  return (res);
}