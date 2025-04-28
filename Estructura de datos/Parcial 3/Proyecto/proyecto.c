/*
INSTRUCCIONES
1.- Escribir el código correspondiente a cada función.
2.- ** Solo ** implementar las partes de código faltantes, ** no ** modificar el código ya escrito.

Nombre del alumno: "Janelle Jacqueline Gomez Benitez"
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

/* 20.- Esta función busca el tipo de receta para contar cuantas recetas tiene se usa como base para la siguiente función */
int cuentaRecetas(RECETARIO r, char *tipo);

/* 21.- Esta función cuenta el No. de recetas de un tipo previamente buscado */
int cuentaRece(LISTA_RECE lr);

/* 22.- Esta función busca el tipo de receta como base para la siguiente función */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece);

/* 23.- Esta función busca una receta para poder contar cuantas recetas tiene se usa como base para la siguiente función 
*/
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece);

/* 24.- Esta función cuenta el No. de ingredientes de una receta previamente buscada, que pertece a un tipo también previamente buscado. */
int cuentaIngre(LISTA_INGRE li);

/* 25.- Esta función encuentra el nombre del tipo de receta con mas recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR);

/*26.-  Esta función encuentra el nombre de la receta con mas ingredientes (RMI) así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI);

/* 27.- Esta función cuenta el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre);

/* 28.- Esta función elimina un ingrediente, despues de haber encontrado sureceta y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre);

/* 29.- Esta función busca la receta para poder eliminar el ingrediente */
int eliminaReceIngre(LISTA_RECE lr, char *rece, char *ingre);

/* 30.- Esta función busca el tipo de receta, para ubicar la lista de recetasdonde se ubica el ingrediente a eliminar */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre);

/* 31.- Esta función elimina todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li);

/* 32.- Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaIngresBuscaReceXreceta(LISTA_RECE *lr, char *rece);

/* 33.- Esta función elimina todas las recetas de un tipo, eliminando previamente todos los ingredientes  */
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
    int res=0;
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
    int res=0;
    *nuevo = (LISTA_RECE)malloc(sizeof(struct nodoRece));
    if(*nuevo)
    {
        strcpy((*nuevo)->nomRece, rece);
        (*nuevo)->sigRece = NULL;
        (*nuevo)->cabIngre = NULL;
        res = 1;
    }
    return(res);
}

/* Función para crear un nodo tipo */
int creaNodoTipo(RECETARIO *nuevo, char *tipo)
{
    int res=0;
    *nuevo = (RECETARIO)malloc(sizeof(struct nodoTipo));
    if(*nuevo)
    {
        strcpy((*nuevo)->nomTipo, tipo);
        (*nuevo)->sigTipo = NULL;
        (*nuevo)->cabRece = NULL;
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
    int res;
    LISTA_RECE nuevo;
    res = creaNodoRece(&nuevo, rece);
    if (res)
      nuevo->sigRece = *lr;
    *lr = nuevo;
    return (res);
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
    int res;
    RECETARIO nuevo;
    res = creaNodoTipo(&nuevo, tipo);
    if (res)
      nuevo->sigTipo = *r;
    *r = nuevo;
    return (res);
  }

/* Función para capturar Tipos de recetas, inserlos en el recetario */
void capturaTipos(RECETARIO *r)
{
    int res;
    char resp, tipo[30];
    do 
    {
        printf("\nTipo: ");
        fflush(stdin);
        scanf("%s", tipo);
        res = insTipo(r, tipo);
        if (res) 
        {
            printf("\n¿Otro tipo? (s/n)");
            fflush(stdin);
            scanf("%c", &resp);
        }
    } while (res && resp == 's');
}

/* Función para captura las recetas, insertarlas en recetario en el tipo al que pertenecen */
void capturaRecetas(RECETARIO r)
{
    int res;
    char resp, rece[30], tipo[30];
    do 
    {
        printf("\nTipo De Receta: ");
        fflush(stdin);
        scanf("%s", tipo);
        printf("\nReceta: ");
        fflush(stdin);
        scanf("%s", rece);
        res = insReceta(r, tipo, rece);
        if (res) 
        {
            printf("\n¿Otra receta? (s/n)");
            fflush(stdin);
            scanf("%c", &resp);
        }
    } while (res && resp == 's');
}

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r)
{
    int res;
    char resp, ingre[30], rece[30], tipo[30];
    do 
    {
        printf("\nTipo De Receta: ");
        fflush(stdin);
        scanf("%s", rece);
        printf("\nReceta: ");
        fflush(stdin);
        scanf("%s", rece);
        printf("\nIngrediente: ");
        fflush(stdin);
        scanf("%s", ingre);
        res = insIngrediente(r, tipo, rece, ingre);
        if (res) 
        {
            printf("\n¿Otro ingrediente? (s/n)");
            fflush(stdin);
            scanf("%c", &resp);
        }
    } while (res && resp == 's');
}

/* Función para mostrar el recetario completo */
void muestraRecetario(RECETARIO r)
{
    LISTA_RECE auxRece;
    LISTA_INGRE auxIngre;
    while (r) 
    {
        printf("\nTipo: %s", r->nomTipo);
        auxRece = r->cabRece;
        while (auxRece) 
        {
            printf("\nReceta: %s", auxRece->nomRece);
            auxIngre = auxRece->cabIngre;
            while (auxIngre) 
            {
                printf("\nIngrediente: %s", auxIngre->nomIngre);
                auxIngre = auxIngre->sigIngre;
            }
            auxRece = auxRece->sigRece;
        }
        r = r->sigTipo;
    }
}

/* Esta función muestra las recetas de un tipo de receta */
void muestraRecetasTipo(RECETARIO r, char *tipo)
{
    LISTA_RECE auxRece;
    while (r && strcmp(tipo, r->nomTipo) != 0)
        r = r->sigTipo;
    if (r) 
    {
        auxRece = r->cabRece;
        while (auxRece) 
        {
            printf("\nReceta: %s", auxRece->nomRece);
            auxRece = auxRece->sigRece;
        }
    }
}

/* Esta función muestra los ingredientes de una receta */
void muestraIngredientesReceta(RECETARIO r, char *tipo, char *rece)
{
    LISTA_RECE auxRece;
    LISTA_INGRE auxIngre;
    while (r && strcmp(tipo, r->nomTipo) != 0)
    r = r->sigTipo;
    if (r) {
    auxRece = r->cabRece;
    while (auxRece && strcmp(rece, auxRece->nomRece) != 0)
        auxRece = auxRece->sigRece;
    if (auxRece) {
        auxIngre = auxRece->cabIngre;
        while (auxIngre) {
        printf("\nIngrediente: %s", auxIngre->nomIngre);
        auxIngre = auxIngre->sigIngre;
        }
    }
    }
}

/* Esta función muestra el No. de receta que tiene cada tipo de receta */
void muestraNoReceXtipo(RECETARIO r)
{
    int cont;
    while (r)
    {
        cont = 0;
        cont = cuentaRece(r->cabRece);
        printf("\nTipo: %s tiene %d recetas", r->nomTipo, cont);
        r = r->sigTipo;
    }
}

/* Esta función muestra el No. de ingredientes de cadad receta */
void muestraNoIngreXrece(RECETARIO r)
{
    LISTA_RECE auxRece;
    int cont;
    while (r) 
    {
        printf("Receta: %s\n", r->nomTipo);
        auxRece = r->cabRece;
        while (auxRece)
        {
            cont = cuentaIngreBuscaRece(auxRece, auxRece->nomRece);
            printf("Receta: %s tiene %d ingredientes", auxRece->nomRece, cont);
            auxRece = auxRece->sigRece;
        }
        r = r->sigTipo;
    }
}

/* Función para contar el No. de tipos de recetas */
int cuentaTipos(RECETARIO r)
{
    int cont = 0;
    while (r) 
    {
        cont++;
        r = r->sigTipo;
    }
    return (cont);
}

/* Cuenta Recetas: Función para contar las recetas */
int cuentaRece(LISTA_RECE lr)
{
    int cont = 0;
    while (lr) 
    {
        cont++;
        lr = lr->sigRece;
    }
    return (cont);
}

/* Cuenta Recetas: Función para buscar el tipo de las recetas a contar */
int cuentaRecetas(RECETARIO r, char *tipo)
{
    int cont = 0;
    LISTA_RECE auxRece;
    while (r && strcmp(tipo, r->nomTipo) != 0)
        r = r->sigTipo;
    if (r) 
    {
        auxRece = r->cabRece;
        cont = cuentaRece(auxRece);
    }
    return (cont);
}

/* Cuenta ingredientes:Función para buscar el tipo */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece)
{
    int cont = 0;
    LISTA_RECE auxRece;
    while (r && strcmp(tipo, r->nomTipo) != 0)
        r = r->sigTipo;
    if (r) 
    {
        auxRece = r->cabRece;
        while (auxRece && strcmp(rece, auxRece->nomRece) != 0)
            auxRece = auxRece->sigRece;
        if (auxRece)
            cont = cuentaIngre(auxRece->cabIngre);
    }
    return (cont);
}

/* Cuenta ingredientes: Función para buscar la receta */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece)
{
    int cont = 0;
    LISTA_INGRE auxIngre;
    while (lr && strcmp(rece, lr->nomRece) != 0)
        lr = lr->sigRece;
    if (lr) 
    {
        auxIngre = lr->cabIngre;
        cont = cuentaIngre(auxIngre);
    }
    return (cont);
}

/* Función para contar los ingredientes */
int cuentaIngre(LISTA_INGRE li)
{
    int cont = 0;
    while (li)
    {
        cont++;
        li = li->sigIngre;
    }
    return (cont);
}

/* Función para contar y mostrar el No. de recetas en cada tipo */
void muestraNoRece(RECETARIO r)
{
    int cont;
    while (r)
    {
        cont = 0;
        printf("Tipo de receta: %s\n", r->nomTipo);
        cont = cuentaRecetas(r, r->nomTipo);
        printf("Número de recetas en este tipo: %d\n", cont);
        r = r->sigTipo;
    }
}

/* Función para contar y mostrar el No. de ingredientes por cada receta */
void muestraNoIngre(RECETARIO r)
{
    int cont;
    while (r)
    {
        cont = 0;
        printf("Tipo de receta: %s\n", r->nomTipo);
        cont = cuentaIngreBuscaRece(r->cabRece, r->nomTipo);
        printf("Número de recetas en este tipo: %d\n", cont);
        r = r->sigTipo;
    }
}

/* Función para encontrar el nombre del Tipo de receta con Mas Recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR)
{
    int cont, contTMR = 0;
    while (r) 
    {
        cont = 0;
        cont = cuentaRecetas(r, r->nomTipo);
        if (cont > contTMR) 
        {
            contTMR = cont;
            strcpy(nomTMR, r->nomTipo);
        }
        r = r->sigTipo;
    }
}

/* Función para encontrar el nombre de la Receta con Mas Ingredientes(RMI)
así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI)
{
    int cont, contRMI = 0;
    LISTA_RECE auxRece;
    while (r) 
    {
        cont = 0;
        auxRece = r->cabRece;
        while (auxRece) 
        {
            cont = cuentaIngreBuscaRece(auxRece, auxRece->nomRece);
            if (cont > contRMI) 
            {
                contRMI = cont;
                strcpy(tipoRMI, r->nomTipo);
                strcpy(nomRMI, auxRece->nomRece);
            }
            auxRece = auxRece->sigRece;
        }
        r = r->sigTipo;
    }
}

/* Función para contar el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre)
{
    int cont = 0;
    LISTA_RECE auxRece;
    LISTA_INGRE auxIngre;
    while (r)
    {
        auxRece = r->cabRece;
        while (auxRece)
        {
            auxIngre = auxRece->cabIngre;
            while (auxIngre)
            {
                if (strcmp(auxIngre->nomIngre, ingre) == 0)
                    cont++;
                auxIngre = auxIngre->sigIngre;
            }
            auxRece = auxRece->sigRece;
        }
        r = r->sigTipo;
    }
    return (cont);
}

/* Función para elimina un ingrediente, despues de haber encontrado su receta
y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre)
{
    int res;
    LISTA_INGRE aux;
    if (*li && strcmp((*li)->nomIngre, ingre) == 0)
    {
        aux = *li;
        *li = (*li)->sigIngre;
        free(aux);
        res = 1;
    } else if (*li && strcmp((*li)->nomIngre, ingre) > 0)
        res = eliminaIngre(&(*li)->sigIngre, ingre);
    else
        res = 0;
    return (res);
}

/* Función para buscar la receta a la que pertenece el ingrediente a eliminar*/
int eliminaIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{
    int res;
    if (lr && strcmp(lr->nomRece, rece) == 0)
        res = eliminaIngre(&lr->cabIngre, ingre);
    else if (lr && strcmp(lr->nomRece, rece) > 0)
        res = eliminaIngreBuscaRece(lr->sigRece, rece, ingre);
    else
        res = 0;
    return (res);
}

/* Esta función busca el tipo de receta, al que pertenece la receta del
ingrediente a eliminar */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{
    int res;
    if (r && strcmp(r->nomTipo, tipo) == 0)
        res = eliminaIngreBuscaRece(r->cabRece, rece, ingre);
    else if (r && strcmp(r->nomTipo, tipo) > 0)
        res = eliminaIngrediente(r->sigTipo, tipo, rece, ingre);
    else
        res = 0;
    return (res);
}

/* Función para eliminar todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li)
{
    LISTA_INGRE aux;
    while (*li) 
    {
        aux = *li;
        *li = (*li)->sigIngre;
        free(aux);
    }
}

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaXreceta(LISTA_RECE *lr, char *rece)
{
    int res;
    if (*lr && strcmp((*lr)->nomRece, rece) == 0) 
    {
        eliminaIngredientes(&(*lr)->cabIngre);
        *lr = (*lr)->sigRece;
        res = 1;
    } else if (*lr && strcmp((*lr)->nomRece, rece) > 0)
        res = eliminaXreceta(&(*lr)->sigRece, rece);
    else
        res = 0;
    return (res);
}

/* Función para buscar tipo de la receta a eliminar */
int eliminaReceta(RECETARIO r, char *tipo, char *rece)
{
    int res;
    if (r && strcmp(r->nomTipo, tipo) == 0)
        res = eliminaXreceta(&(r->cabRece), rece);
    else if (r && strcmp(r->nomTipo, tipo) < 0)
        res = eliminaReceta(r->sigTipo, tipo, rece);
    else
        res = 0;
    return (res);
}

/* Funciòn para eliminar las todas las recetas de un tipo, eliminando
previamente todos los ingredientes
*/
void eliminaRecetas(LISTA_RECE lr)
{
    LISTA_RECE aux;
    while(lr) 
    {
        eliminaIngredientes(&(lr->cabIngre));
        aux = lr;
        lr = lr->sigRece;
        free(aux);
    }
}

/* Función para eliminar un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo)
{
    int res;
    RECETARIO aux;
    if (*r && strcmp((*r)->nomTipo, tipo) == 0)
    {
        eliminaRecetas((*r)->cabRece);
        aux = *r;
        *r = (*r)->sigTipo;
        free(aux);
        res = 1;
    } else if (*r && strcmp((*r)->nomTipo, tipo) > 0)
        res = eliminaTipo(&(*r)->sigTipo, tipo);
    else
        res = 0;
    return (res);
}

/* Función para eliminar un recetario completo */
void eliminaRecetario(RECETARIO *r)
{
    RECETARIO aux;
    while (*r)
    {
        eliminaRecetas((*r)->cabRece);
        aux = *r;
        *r = (*r)->sigTipo;
        free(aux);
    }
}