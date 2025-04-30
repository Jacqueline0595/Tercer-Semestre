#include <stdlib.h>
#include <stdio.h>

typedef struct nodoRel
{
    struct nodoVer *verRel;
    struct nodoRel *sigRel;
} *LTS_REL;

typedef struct nodoVer
{
    int ver;
    LTS_REL cabRel;
    struct nodoVer *sigVer;
} *GRAFO_EN;

int main()
{
    return 0;
}

void iniGrafoEN(GRAFO_EN *g)
{
    *g = NULL;
}

int creaNodo(GRAFO_EN *g, int vertice)
{
    int res=0;
    *g = (GRAFO_EN)malloc(sizeof(struct nodoVer));
    if(*g)
    {
        (*g)->cabRel = NULL;
        (*g)->sigVer = NULL;
        (*g)->ver = vertice;
        res = 1;
    }
    return(res);
}

int creaNodoRel(LTS_REL *rel, int vertice)
{
    int res=0;
    *rel = (LTS_REL)malloc(sizeof(struct nodoRel));
    if(*rel)
    {
        (*rel)->verRel = vertice;
        (*rel)->sigRel = NULL;
        res = 1;
    }
    return(res);
}

int insVerEN(GRAFO_EN *g, int vr)
{
    int res = 0;
    GRAFO_EN nuevo, aux;
    aux = *g;
    while(aux && vr != aux->ver)
        aux = aux->sigVer;
    if(!aux)
    {
        res = creaNodo(&nuevo, vr);
        if(res)
        {
            nuevo->sigVer = *g;
            *g = nuevo;
        }
    }
    return(res);
}

int insRelGrafoEN(GRAFO_EN g, int vo, int vd)
{
    int res = 0;
    GRAFO_EN auxO, auxD;
    LTS_REL aux, nuevo;
    for(auxD = g; auxD && vo != auxD->ver; auxD = auxD->sigVer);
    if(auxD)
    {
        for(auxO = g; auxO && vo != auxO->ver; auxO = auxO->sigVer);
        if(auxO)
        {
            aux = auxO->cabRel;
            while(aux && vd != aux->verRel)
                aux = aux->sigRel;
            if(!aux)
            {
                res = creaNodoRel(&nuevo, auxD);
                if(res)
                {
                    nuevo->sigRel = auxO->cabRel;
                    auxO->cabRel = nuevo;
                }
            }
        }
    }
    return(res);
}

int contVerRel(GRAFO_EN cab)
{
    int contV = 0, verCon = 0, rel = 0;
    GRAFO_EN aux;
    LTS_REL auxR;

    aux = cab;
    while(aux)
    {
        contV++;
        aux = aux->sigVer;
    }

    aux = cab;
    while(aux)
    {
        rel = 0;
        auxR = aux->cabRel;
        while(auxR)
        {
            if(auxR->verRel != aux) 
                rel++;
            auxR = auxR->sigRel;
        }
        if(rel == (contV-1))
            verCon++;
        aux = aux->sigVer;
    }
    return(verCon);
}
