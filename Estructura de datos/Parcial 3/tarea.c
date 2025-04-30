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

typedef struct
{
    int **matRel;
    int *vecVer;
    int cVer;
    int nMax;
} GRAFO_MR;

typedef struct nodoRel
{
    int verRel;
    struct nodoRel *sigRel;
} *LIS_REL;

typedef struct
{
    int ver;
    LIS_REL cabRel;
} VER;

typedef struct
{
    int nmax, cVer;
    VER *vecVer;
} GRAFO_VR;


int main()
{
    return 0;
}

int iniGrafoMR(GRAFO_MR *g, int nm)
{
    int res = 0, cont;
    g->vecVer = (int *)malloc(nm * sizeof(int));
    if(g->vecVer)
    {
        g->matRel = (int **)malloc(nm * sizeof(int*));
        if(g->matRel)
        {
            res = 1;
            for(cont = 0; cont < nm && res; cont++)
            {
                *(g->matRel + cont) = (int *)malloc(nm * sizeof(int));
                if(!*(g->matRel + cont))
                {
                    while(--cont>=0)
                        free(*(g->matRel + cont));
                    free(g->matRel);
                    free(g->vecVer);
                    res = 0;
                }
            }
            if(res)
            {
                g->nMax = nm;
                g->cVer = 0;
            }
        }
    }
    else 
        free(g->vecVer);
    return(res);
}

int insVerMR(GRAFO_MR *g, int vr)
{
    int res = 0, cont;
    if(g->cVer < g->nMax)
    {
        for(cont = 0; cont < g->cVer && vr != *(g->vecVer + cont); cont++);
        if(cont == g->cVer)
        {
            *(g->vecVer + cont) = vr;
            for(cont=0; cont < g->cVer; cont++)
                *(*(g->matRel + g->cVer) + cont) = *(*(g->matRel + cont) + g->cVer) = 0;
            g->cVer++;
            res = 1;
        }
    }
    return(res);
}

int insRelMR(GRAFO_MR *g, int vO, int vD)
{
    int res = 0, ren, renCol;
    for(ren = 0; ren < g->cVer && vO != *(g->vecVer + ren); ren++);
    if(ren < g->cVer)
    {
        for(renCol = 0; renCol < g->cVer && vD != *(g->vecVer + renCol); renCol++);
        if(renCol < g->cVer)
            res = *(*(g->matRel + ren) + renCol) = 1;
    }
    return(res);
}

int convertirENaMR(GRAFO_EN g, GRAFO_MR *gMR)
{
    int res = 0, contV = 0;
    GRAFO_EN auxE;
    LTS_REL auxR;

    auxE = g;
    while(auxE)
    {
        contV++;
        auxE = auxE->sigVer;
    }

    if(iniGrafoMR(gMR, contV))
    {
        auxE = g;
        while(auxE)
        {
            insVerMR(gMR, auxE->ver);
            auxE = auxE->sigVer;
        }

        for(auxE = g; auxE; auxE = auxE->sigVer)
            for(auxR = auxE->cabRel; auxR; auxR = auxR->sigRel)
                insRelMR(gMR, auxE->ver, auxR->verRel->ver);
        res = 1;
    }
    return res;
}


int sonIguales(GRAFO_EN gEN, GRAFO_VR gVR)
{
    int res = 1;
    GRAFO_EN auxE;
    LTS_REL relEN;
    LIS_REL relVR;
    int cont, contE = 0, encon, contRelEn, contRelVr;

    auxE = gEN;
    while(auxE)
    {
        contE++;
        auxE = auxE->sigVer;
    }

    if(contE != gVR.cVer)
        res = 0;

    auxE = gEN;
    while(auxE && res)
    {
        for(cont = 0; cont < gVR.cVer && (gVR.vecVer + cont).ver != auxE->ver; cont++);
        if(cont == gVR.cVer)
            res = 0; 

        contRelEn = 0;
        for(relEN = auxE->cabRel; relEN; relEN = relEN->sigRel)
        contRelEn++;

        contRelVr = 0;
        for(relVR = (gVR.vecVer + cont).cabRel; relVR; relVR = relVR->sigRel)
            contRelVr++;

        if(contRelEn != contRelVr)
            res = 0;

        relEN = auxE->cabRel;
        while(relEN)
        {
            encon = 0;
            for(relVR = (gVR.vecVer + cont).cabRel; relVR && !encon; relVR = relVR->sigRel)
            {
                if(relEN->verRel->ver == relVR->verRel)
                    encon = 1;
            }
            if(!encon)
                res = 0;
            relEN = relEN->sigRel;
        }
        auxE = auxE->sigVer;
    }

    return(res);
}
