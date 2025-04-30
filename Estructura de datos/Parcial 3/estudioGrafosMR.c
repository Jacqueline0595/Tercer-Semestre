#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int **matRel;
    int *vecVer;
    int cVer;
    int nMax;
} GRAFO_MR;

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

int insResMRlar(GRAFO_MR *g, int vO, int vD)
{
    int res = 0, dirVo = -1, dirVd = -1, cont;
    for(cont = 0; cont < g->cVer && vO != *(g->vecVer + cont); cont++);
    if(cont < g->cVer)
    {
        dirVo = cont;
        for(cont = 0; cont < g->cVer && vD != *(g->vecVer + cont); cont++);
        if(cont < g->cVer)
            dirVd = cont;
    }
    if(dirVo != -1 && dirVd != -1)
        *(*(g->matRel + dirVo) + dirVd) = res = 1;
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

void muestraGrafo(GRAFO_MR g)
{
    int ren, col;
    for(ren = 0; ren < g.cVer; ren++)
    {
        printf("%d ", *(g.vecVer + ren));
        for(col = 0; col < g.cVer; col++)
            if(*(*(g.matRel + ren) + col))
                printf("%d ", *(g.vecVer + col));
            printf("\n");
    }
}

void muestraVerNoRels(GRAFO_MR g)
{
    int ren, col, cRel = 0;
    for(ren = 0; ren < g.cVer; ren++)
    {
        cRel = 0;
        for(col = 0; col < g.cVer; col++)
            if(*(*(g.matRel + ren) + col))
                cRel++;
        printf("%d : %d \n", *(g.vecVer + ren), cRel);
    }
}

int verMasRel(GRAFO_MR g)
{
    int ren, col, cRel, cMay = 0, mas;
    mas = *(g.vecVer);
    for(ren = 0; ren < g.cVer; ren++)
    {
        cRel = 0;
        for(col = 0; col < g.cVer; col++)
            cRel += *(*(g.matRel + ren) + col);
        if(cRel > cMay)
        {
            cMay = cRel;
            mas = *(g.vecVer + ren);
        }
    }
    return(mas);
}

int verMasConocido(GRAFO_MR g)
{
    int mas, ren, col, cRel, cMay = 0;
    mas = *(g.vecVer);
    for(ren = 0; ren < g.cVer; ren++)
    {
        cRel = 0;
        for(col = 0; col < g.cVer; col++)
            cRel += *(*(g.matRel + col) + ren);
        if(cRel > cMay)
        {
            cMay = cRel;
            mas = *(g.vecVer + ren);
        }
    }
    return(mas);
}

int formanCamino(GRAFO_MR *g, int v1, int v2, int v3)
{
    int res = 0, cont1, cont2, cont3;

    for(cont1 = 0; cont1 < g->cVer && v1 != *(g->vecVer + cont1); cont1++);
    if(cont1 < g->cVer)
    {
        for(cont2 = 0; cont2 < g->cVer && v2 != *(g->vecVer + cont2); cont2++);
        if(cont2 < g.cVer)
        {
            for(cont3 = 0; cont3 < g->cVer && v3 != *(g->vecVer + cont3); cont3++);
                if(cont3 < g.cVer)
                    res = *(*(g->matRel + cont1) + cont2) * *(*(g->matRel + cont2) + cont3) * *(*(g->matRel + cont3) + cont1);
        }
    }
    
    return res;
}

void contarRelacionesReciprocas(GRAFO_MR *g)
{
    int ren, col, cont;
    for (ren = 0; ren < g.cVer; ren++)
    {
        cont = 0;
        for (col = 0; col < g.cVer; col++)
            if (ren != col) 
                if ( *(*(g.matRel + ren) + col) != 0 && *(*(g.matRel + col) + ren) != 0 )
                    cont++;

        printf("Vertice %d tiene %d relaciones recíprocas. \n", *(g.vecVer + ren), cont);
    }
}

int vectorFuente(GRAFO_MR *g, int vectFu)
{
    int cont1, cont2, cont3, res = 0;

    for (cont1 = 0; cont1 < g.cVer && vectFu != *(g.vecVer + cont1); cont1++);
    if (cont1 < g.cVer)
    {
        for (cont2 = 0; cont2 < g.cVer && *(*(g.matRel + cont1) + cont2) == 0; cont2++);
        if (cont2 < g.cVer)
        {
            for (cont3 = 0; cont3 < g.cVer && *(*(g.matRel + cont3) + cont1) == 0; cont3++);
            if (cont3 == g.cVer)
                res = 1;
        }
    }

    return res;
}

