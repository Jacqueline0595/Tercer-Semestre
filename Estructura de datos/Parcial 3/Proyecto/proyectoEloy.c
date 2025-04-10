/*
INSTRUCCIONES
1.- Escribir el código correspondiente a cada función.
2.- ** Solo ** implementar las partes de código faltantes, ** no ** modificar el código ya escrito.

Nombre del alumno: "Hernández Hernández Eloy Emilio"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estructura ingrediente */
typedef struct nodoIngre
{ 
char nomIngre[25];
struct nodoIngre *sigIngre;
} *LISTA_INGRE;

/* Estructura receta */
typedef struct nodoRece
{
char nomRece[25];
LISTA_INGRE cabIngre;
struct nodoRece *sigRece;
} *LISTA_RECE;

/* Estructura tipo receta */
typedef struct nodoTipo
{
char nomTipo[25];
LISTA_RECE cabRece;
struct nodoTipo *sigTipo;
} *RECETARIO;

/* 1.- Esta función inicializa el recetario */
void iniRecetario(RECETARIO *r);

/* 2.- Esta función creará un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre);

/* 3.- Esta función creará un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece);

/* 4.- Esta función creará un nodo tipo-receta */
int creaNodoTipo(RECETARIO *nuevo, char *tipo);

/* 5.- Esta función busca el tipo de receta donde según la receta se insertará el ingrediente */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* 6.- Esta función busca la receta donde insertará el ingrediente */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre);

/* 7.- Esta función inserta el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre);

/* 8.- Esta función busca el tipo de receta donde se inserta la receta */
int insReceta(RECETARIO r, char *tipo, char *rece);

/* 9.- Esta función inserta una receta */
int insRece(LISTA_RECE *lr, char *rece);

/* 10.- Esta función inserta un tipo de receta */
int insTipo(RECETARIO *r, char *tipo);

/* 11.- Esta Función captura los tipos de recetas, para insertarlos en el recetario */
void capturaTipos(RECETARIO *r);

/* 12.- Esta Función captura las recetas, para insertarlas en el recetario */
void capturaRecetas(RECETARIO r);

/* 13.- Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r);

/* 14.- Esta función muestra toda la información del rcetario */
void muestraRecetario(RECETARIO r);

/* 15.- Esta función muestra las recetas de un tipo de receta */
void muestraRecetasTipo(RECETARIO r, char *tipo);

/* 16.- Esta función muestra los ingredientes de una receta */
void muestraIngredientesReceta(RECETARIO r, char *tipo, char *rece);

/* 17.- Esta función muestra el No. de receta que tiene cada tipo de receta */
void muestraNoReceXtipo(RECETARIO r);

/* 18.- Esta función muestra el No. de ingredientes de cadad receta */
void muestraNoIngreXrece(RECETARIO r);

/* 19.- Esta función calcula y retorna cuantos tipos de recta tiene un recetario */
int cuentaTipos(RECETARIO r);

/* 20.- Esta función busca el tipo de receta para contar cuantas recetas tiene
se usa como base para la siguiente función 
*/
int cuentaRecetas(RECETARIO r, char *tipo);

/* 21.- Esta función cuenta el No. de recetas de un tipo previamente buscado */
int cuentaRece(LISTA_RECE lr);

/* 22.- Esta función busca el tipo de receta como base para la siguiente función */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece);

/* 23.- Esta función busca una receta para poder contar cuantas recetas tiene
se usa como base para la siguiente función 
*/
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece);

/* 24.- Esta función cuenta el No. de ingredientes de una receta previamente buscada,
que pertece a un tipo también previamente buscado.
*/
int cuentaIngre(LISTA_INGRE li);

/* 25.- Esta función encuentra el nombre del tipo de receta con mas recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR);

/*26.-  Esta función encuentra el nombre de la receta con mas ingredientes (RMI) 
así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI);

/* 27.- Esta función cuenta el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre);

/* 28.- Esta función elimina un ingrediente, despues de haber encontrado su
receta y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre);

/* 29.- Esta función busca la receta para poder eliminar el ingrediente */
int eliminaReceIngre(LISTA_RECE lr, char *rece, char *ingre);

/* 30.- Esta función busca el tipo de receta, para ubicar la lista de recetas
donde se ubica el ingrediente a eliminar 
*/
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* 31.- Esta función elimina todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li);

/* 32.- Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaIngresBuscaReceXreceta(LISTA_RECE *lr, char *rece);

/* 33.- Esta función elimina todas las recetas de un tipo, eliminando
previamente todos los ingredientes  */
void eliminaRecetas(LISTA_RECE lr);

/* 34.- Esta función elimina un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo);

/*35.- Esta función elimina un recetario completo */
void eliminaRecetario(RECETARIO *r);

#include "evalua/evaluar.h"

int main()
{
/* Puede escribir a continuación código para probar sus funciones
    aunque no es necesario */ 
    
    
/* NO BORRAR ESTA LINEA */
evaluar();    
}


/* Función para inicualizar la estructura principal */
void iniRecetario(RECETARIO *r)
{
    *r = NULL;
}

/* Función para crear un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre)
{
    int res = 0;
    *nuevo = (LISTA_INGRE)malloc(sizeof(struct nodoIngre));
    if(*nuevo)
    {
        strcpy((*nuevo)->nomIngre, ingre);
        (*nuevo)->sigIngre = NULL;
        res = 1;
    }
    return(res);
}

/* Función para crear un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece)
{
    int res = 0;
    *nuevo = (LISTA_RECE)malloc(sizeof(struct nodoRece));
    if(*nuevo)
    {
        strcpy((*nuevo)->nomRece, rece);
        (*nuevo)->cabIngre = NULL;
        (*nuevo)->sigRece = NULL;
        res = 1;
    }
    return(res);
}

/* Función para crear un nodo tipo */
int creaNodoTipo(RECETARIO *nuevo, char *tipo)
{
    int res = 0;
    *nuevo = (RECETARIO)malloc(sizeof(struct nodoTipo));
    if(*nuevo)
    {
        strcpy((*nuevo)->nomTipo, tipo);
        (*nuevo)->cabRece = NULL;
        (*nuevo)->sigTipo = NULL;
        res = 1;
    }
    return(res);
}

/* Inserta ingrediente: Función para insertar el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre)
{
    int res = 0;
    LISTA_INGRE nuevo;
    creaNodoIngre(&nuevo, ingre);
    if(nuevo)
    {
        nuevo->sigIngre = *li;
        *li = nuevo;
        res = 1;            
    }
    return(res);
}

/* Inserta ingrediente: Función para buscar la receta */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
    int res = 0;
    while(lr != NULL)
    {
        if(strcmp(lr->nomRece, rece) == 0)
        {
            insIngre(&(lr->cabIngre), ingre);
            res = 1;
        }
        lr = lr->sigRece;
    }
    return(res);
}

/* Inserta ingrediente: Función para buscar el tipo */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
    int res = 0;
    while(r != NULL)
    {
        if(strcmp(r->nomTipo, tipo) == 0)
        {
            insIngreBuscaRece(r->cabRece, rece, ingre);
            res = 1;
        }
        r = r->sigTipo;
    }
    return(res);
}

/* Inserta receta: Función para insertar la receta */
int insRece(LISTA_RECE *lr, char *rece)
{
    int res = 0;
    LISTA_RECE nuevo;
    creaNodoRece(&nuevo, rece);
    if(nuevo)
    {
        nuevo->sigRece = *lr;
        *lr = nuevo;
        res = 1;  
    }
    return(res);
}

/* Inserta receta: Función para buscar el tipo de la receta */
int insReceta(RECETARIO r, char *tipo, char *rece)
{
    int res = 0;
        while(r)
        {
            if(strcmp(r->nomTipo, tipo)== 0)
            {
                insRece(&(r->cabRece), rece);
                res  = 1;
            }   
            r = r->sigTipo;    
        }
    return(res);
}

/*Función para insertar un tipo de receta */
int insTipo(RECETARIO *r, char *tipo)
{
    int res = 0;
    RECETARIO nuevo;
    creaNodoTipo(&nuevo, tipo);
    if(nuevo)
    {
        nuevo->sigTipo = *r;
        *r = nuevo;
        res = 1;    
    }
    return(res);
}

/* Función para capturar Tipos de recetas, inserlos en el recetario */
void capturaTipos(RECETARIO *r)
{
    char tipo[25];
    int i, n;
    printf("Numero de tipos a insertar:\n");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++)
    {
        printf("Escriba el tipo:\n ");
        scanf("%s", tipo);
        insTipo(r, tipo);
    }
}

/* Función para captura las recetas, insertarlas en recetario en el tipo al que pertenecen */
void capturaRecetas(RECETARIO r)
{
    char tipo[25], rece[25];
    int i, n;
    printf("Numero de recetas a ingresar:\n");
    scanf("%d", &n);
    printf("Escriba el tipo:\n");
    scanf("%s", tipo);
    
    for(i = 0; i<n;i++)
    {
        printf("Escriba el nombre de la receta:\n");
        scanf("%s", rece);
        insReceta(r,tipo, rece);
    }        
}

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r)
{
    int numIng, i;
    char ing[50], tipo[50], rece[50];
    printf("Escriba la cantidad de ingredientes:\n");
    scanf("%d", &numIng);
    printf("Nombre del tipo;\n");
    scanf("%s", tipo);
    printf("Nombre de la receta:\n");
    scanf("%s", rece);
    
    for(i = 0; i < numIng; i++)
    {
        printf("ingresa Nombre del ingrediente:\n");
        scanf("%s", ing);
        insIngrediente(r,tipo,rece,ing);    
    }
    
}

/* Función para mostrar el recetario completo */
void muestraRecetario(RECETARIO r)
{
    LISTA_RECE receta;
    LISTA_INGRE ingrediente;
    while(r)
    {
        printf("Tipo: %s\n", r->nomTipo);
        receta = r->cabRece;
        while(receta)
        {
            printf("\tReceta: %s\n", receta->nomRece);
            ingrediente = receta->cabIngre;
            while(ingrediente)
            {
                printf("Ingrediente: %s\n", ingrediente->nomIngre);
                ingrediente = ingrediente->sigIngre;
            }
            receta = receta->sigRece;
        }
        r = r->sigTipo;
    }
}

/* Esta función muestra las recetas de un tipo de receta */
void muestraRecetasTipo(RECETARIO r, char *tipo)
{
    while(r)
    {
        if(strcmp(r->nomTipo, tipo) == 0)
        {
            LISTA_RECE receta = r->cabRece;
            while(receta)
            {
                printf("%s", receta->nomRece);
                receta = receta->sigRece;
            }
        }
        r = r->sigTipo;
    }
}

/* Esta función muestra los ingredientes de una receta */
void muestraIngredientesReceta(RECETARIO r, char *tipo, char *rece)
{
    LISTA_RECE receta;
    LISTA_INGRE ingre;
    while(r)
    {
        if(strcmp(r->nomTipo, tipo)== 0)
        {
            receta = r->cabRece;
            while(receta)
            {
                if(strcmp(receta->nomRece, rece)==0)
                {
                    ingre = receta->cabIngre;
                    while(ingre)
                    {
                        printf("%s", ingre->nomIngre);
                        ingre = ingre->sigIngre;
                    }
                }
                receta = receta->sigRece;
            }
        }
        r = r->sigTipo;
    }
}

/* Esta función muestra el No. de receta que tiene cada tipo de receta */
void muestraNoReceXtipo(RECETARIO r)
{
    int NoTipos;
    LISTA_RECE receta;
    while(r)
    {
        NoTipos = 0;
        receta = r->cabRece;
        while(receta)
        {
            NoTipos++;
            receta = receta->sigRece;
        }
        printf("%s %d", r->nomTipo, NoTipos);
        r = r->sigTipo;
    }
}

/* Esta función muestra el No. de ingredientes de cadad receta */
void muestraNoIngreXrece(RECETARIO r)
{
    LISTA_RECE receta;
    LISTA_INGRE ingre;
    while(r)
    {
        receta = r->cabRece;
        while(receta)
        {
            printf("%s", receta->nomRece);
            ingre = receta->cabIngre;
            while(ingre)
            {
                printf("%s", ingre->nomIngre);
                ingre = ingre->sigIngre;
            }
            receta = receta->sigRece;
        }
        r =  r->sigTipo;
    }
}

/* Función para contar el No. de tipos de recetas */
int cuentaTipos(RECETARIO r)
{
    int NoTipos = 0;
    while(r)
    {
        NoTipos++;
        r = r->sigTipo;
    }
    return(NoTipos);
}

/* Cuenta Recetas: Función para contar las recetas */
int cuentaRece(LISTA_RECE lr)
{
    int Nrece = 0;
    while(lr)
    {
        Nrece++;
        lr=lr->sigRece;
    }
    return(Nrece);
}

/* Cuenta Recetas: Función para buscar el tipo de las recetas a contar*/
int cuentaRecetas(RECETARIO r, char *tipo)
{
    LISTA_RECE lr;
    int cont = 0;
    while(r)
    {
        if(strcmp(r->nomTipo, tipo) == 0)
        {
            lr = r->cabRece;
            while(lr)
            {
            cont++;
            lr = lr->sigRece;
            }
        }
        r = r->sigTipo;
    }
}

/* Cuenta ingredientes:Función para buscar el tipo */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece)
{
    int cont = 0;
    LISTA_RECE lr;
    LISTA_INGRE ing;
    while(r)
    {
        if(strcmp(r->nomTipo, tipo)==0)
        {
            lr = r->cabRece;
            while(lr)
            {
                if(strcmp(lr->nomRece, rece)==0)
                {
                    ing = lr->cabIngre;
                    while(ing)
                    {
                        cont++;
                        ing = ing->sigIngre;
                    }
                }
                lr = lr->sigRece;
            }
        }
        r = r->sigTipo;
    }
    return(cont);
}

/* Cuenta ingredientes: Función para buscar la receta */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece)
{
    LISTA_INGRE ingre;
    int cont = 0;
    while(lr)
    {
        if(strcmp(lr->nomRece, rece)==0)
        {
            ingre = lr->cabIngre;
            while(ingre)
            {
                cont++;
                ingre = ingre->sigIngre;
            }
        }
        lr = lr->sigRece;
    }
    return(cont);
}

/* Función para contar los ingredientes */
int cuentaIngre(LISTA_INGRE li)
{
    int NumI = 0;
    while(li)
    {
        NumI++;
        li = li->sigIngre;
    }
    return(NumI);
}

/* Función para contar y mostrar el No. de recetas en cada tipo */
void muestraNoRece(RECETARIO r)
{
    LISTA_RECE receta;
    while(r)
    {
        int n = 0;
        receta = r->cabRece;
        while(receta)
        {
            n++;
            receta = receta->sigRece;
        }
        printf("TIPO: %s Cant: %d\n", r->nomTipo, n);
    }
}

/* Función para contar y mostrar el No. de ingredientes por cada receta */
void muestraNoIngre(RECETARIO r)
{
    LISTA_RECE lr;
    LISTA_INGRE li;
    while(r)
    {
        lr = r->cabRece;
        while(lr)
        {
            li = lr->cabIngre;
            int contLi = 0;
            while(li)
            {
                printf("%s\n", li->nomIngre);
                contLi++;
                li = li->sigIngre;
            }
            printf("%d\n", contLi);
            lr = lr->sigRece;
        }
    }
}

/* Función para encontrar el nombre del Tipo de receta con Mas Recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR)
{
    int tmr = 0;
    LISTA_RECE lr;
    while(r)
    {
        int cont = 0;
        lr= r->cabRece;
        while(lr)
        {
            cont++;
            lr=lr->sigRece;
        }
        if(cont > tmr)
        {
            strcpy(nomTMR, r->nomTipo);
        }
        r = r->sigTipo;
    }
}

/* Función para encontrar el nombre de la Receta con Mas Ingredientes(RMI) 
así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI)
{
    char tipo[30];
    char nom[30];
    int MI = 0;
    LISTA_RECE lr;
    LISTA_INGRE li;
    while(r)
    {
        lr = r->cabRece;
        
        while(lr)
        {
            li = lr->cabIngre;
            int temp = 0;
            
            while(li)
            {
                temp++;
                li = li->sigIngre;
            }
            
            if(temp > MI)
            {
                MI = temp;
                strcpy(tipo, r->nomTipo);
                strcpy(nom, lr->nomRece);
            }
            
            lr = lr->sigRece;
        }
        r = r->sigTipo;
    }
    strcpy(tipoRMI, tipo);
    strcpy(nomRMI, nom);
    printf("%s %s %d", tipoRMI, nomRMI, MI);
}

/* Función para contar el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre)
{
    int numR = 0;
    LISTA_RECE lr;
    LISTA_INGRE li;
    while(r)
    {
        lr =  r->cabRece;
        while(lr)
        {
            li = lr->cabIngre;
            while(li)
            {
                if(strcmp(li->nomIngre, ingre)==0)
                numR++;
                li = li->sigIngre;   
            }
            lr = lr->sigRece;
        }
        r = r->sigTipo;
    }
    return(numR);
}

/* Función para elimina un ingrediente, despues de haber encontrado su receta
y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre)
{
    int res = 0;
    LISTA_INGRE ant, temp;
    while(*li)
    {
        ant = *li;
        *li = (*li)->sigIngre;
        
        if(*li == ant && strcmp((*li)->nomIngre, ingre)==0)
        {
            free(li);
            res = 1;
        }    
        else if((*li)->sigIngre == NULL)
        {
                temp = *li;
                ant->sigIngre = NULL;
                free(temp);
                res = 1;
        }
        ant->sigIngre = (*li)->sigIngre;
        res = 1;
    }
    return(res);
}

/* Función para buscar la receta a la que pertenece el ingrediente a eliminar*/
int eliminaIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
    int res = 0;
    LISTA_INGRE li;
    
    while(lr)
    {
        if(strcmp(lr->nomRece, rece)==0)
        {
            li = lr->cabIngre;
            while(li)
            {
                if(strcmp(li->nomIngre, ingre)==0)
                {
                    eliminaIngre(&li,ingre);
                    res = 1;
                }    
                li = li->sigIngre;    
            }
        }
        lr = lr->sigRece;
    }
    return(res);
}

/* Esta función busca el tipo de receta, al que pertenece la receta del
ingrediente a eliminar */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
    int res = 0;
    LISTA_RECE lr;
    LISTA_INGRE li;
    while(r)
    {
        if(strcmp(r->nomTipo, tipo)==0)
        {
            lr = r->cabRece;
            while(lr)
            {
                if(strcmp(lr->nomRece, rece)==0)
                {
                    li = lr->cabIngre;
                    while(li)
                    {
                        if(strcmp(li->nomIngre, ingre)==0)
                        {
                            eliminaIngre(&li, ingre);
                            res = 1;
                        }
                        li = li->sigIngre;
                    }
                }
                lr = lr->sigRece;
            }
        }
        r = r->sigTipo;
    }
    return(res);
}

/* Función para eliminar todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li)
{
    while(*li)
    {
        char aux[30];
        strcpy(aux, (*li)->nomIngre);
        eliminaIngre(li, aux);
    }
}

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaXreceta(LISTA_RECE *lr, char *rece)
{
    int res = 0; 
    while(*lr)
    {
        if(strcmp((*lr)->nomRece, rece)==0)
        {
            eliminaIngredientes(&(*lr)->cabIngre);
            res = 1;
        }
        *lr = (*lr)->sigRece;
    }
    return(res);
}

/* Función para buscar tipo de la receta a eliminar */
int eliminaReceta(RECETARIO r, char *tipo, char *rece)
{
    int res = 0;
    while(r)
    {
        if(strcmp(r->nomTipo, tipo)==0)
        {
            eliminaXreceta(&(r->cabRece), rece);
            res = 1;
        }
        r = r->sigTipo;
    }
    return(res);
}

/* Funciòn para eliminar las todas las recetas de un tipo, eliminando
previamente todos los ingredientes
*/
void eliminaRecetas(LISTA_RECE lr)
{
    while(lr)
    {
        eliminaIngredientes(&(lr->cabIngre));
    }
}

/* Función para eliminar un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo)
{
    int res = 0;
    while(*r)
    {
        if(strcmp((*r)->nomTipo, tipo)==0)
        {
            eliminaRecetas((*r)->cabRece);
            res = 1;
        }
        *r = (*r)->sigTipo;
    }
    return(res);
}

/* Función para eliminar un recetario completo */
void eliminaRecetario(RECETARIO *r)
{
    while(*r)
    {
        eliminaTipo(r, (*r)->nomTipo);
    }
}