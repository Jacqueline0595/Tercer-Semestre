/*
INSTRUCCIONES
1.- Escribir el código correspondiente a cada función.
2.- ** Solo ** implementar las partes de código faltantes, ** no ** modificar el código ya escrito.

Nombre del alumno: "Escriba aquí su nombre completo"
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

}

/* Función para crear un nodo ingrediente */
int creaNodoIngre(LISTA_INGRE *nuevo, char *ingre)
{

}

/* Función para crear un nodo receta */
int creaNodoRece(LISTA_RECE *nuevo, char *rece)
{

}

/* Función para crear un nodo tipo */
int creaNodoTipo(RECETARIO *nuevo, char *tipo)
{

}

/* Inserta ingrediente: Función para insertar el ingrediente */
int insIngre(LISTA_INGRE *li, char *ingre)
{

}

/* Inserta ingrediente: Función para buscar la receta */
int insIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{


}

/* Inserta ingrediente: Función para buscar el tipo */
int insIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{


}

/* Inserta receta: Función para insertar la receta */
int insRece(LISTA_RECE *lr, char *rece)
{


}

/* Inserta receta: Función para buscar el tipo de la receta */
int insReceta(RECETARIO r, char *tipo, char *rece)
{

}

/*Función para insertar un tipo de receta */
int insTipo(RECETARIO *r, char *tipo)
{

}

/* Función para capturar Tipos de recetas, inserlos en el recetario */
void capturaTipos(RECETARIO *r)
{

}

/* Función para captura las recetas, insertarlas en recetario en el tipo al que pertenecen */
void capturaRecetas(RECETARIO r)
{

}

/* Esta Función captura los ingredientes, para insertarlos en el recetario */
void capturaIngredientes(RECETARIO r)
{

}

/* Función para mostrar el recetario completo */
void muestraRecetario(RECETARIO r)
{

}

/* Esta función muestra las recetas de un tipo de receta */
void muestraRecetasTipo(RECETARIO r, char *tipo);

/* Esta función muestra los ingredientes de una receta */
void muestraIngredientesReceta(RECETARIO r, char *tipo, char *rece);

/* Esta función muestra el No. de receta que tiene cada tipo de receta */
void muestraNoReceXtipo(RECETARIO r);

/* Esta función muestra el No. de ingredientes de cadad receta */
void muestraNoIngreXrece(RECETARIO r);

/* Función para contar el No. de tipos de recetas */
int cuentaTipos(RECETARIO r)
{

}

/* Cuenta Recetas: Función para contar las recetas */
int cuentaRece(LISTA_RECE lr)
{

}

/* Cuenta Recetas: Función para buscar el tipo de las recetas a contar*/
int cuentaRecetas(RECETARIO r, char *tipo)
{

}

/* Cuenta ingredientes:Función para buscar el tipo */
int cuentaIngredientes(RECETARIO r, char *tipo, char *rece)
{

}

/* Cuenta ingredientes: Función para buscar la receta */
int cuentaIngreBuscaRece(LISTA_RECE lr, char *rece)
{

}

/* Función para contar los ingredientes */
int cuentaIngre(LISTA_INGRE li)
{

}

/* Función para contar y mostrar el No. de recetas en cada tipo */
void muestraNoRece(RECETARIO r)
{

}

/* Función para contar y mostrar el No. de ingredientes por cada receta */
void muestraNoIngre(RECETARIO r)
{

}

/* Función para encontrar el nombre del Tipo de receta con Mas Recetas(TMR) */
void encuentraTMR(RECETARIO r, char *nomTMR)
{

}

/* Función para encontrar el nombre de la Receta con Mas Ingredientes(RMI) 
así como también el tipo al que pertenece */
void encuentraRMI(RECETARIO r, char *tipoRMI, char *nomRMI)
{

}

/* Función para contar el número de recetas que usan un ingrediente */
int cuentaReceIngre(RECETARIO r, char *ingre)
{

}

/* Función para elimina un ingrediente, despues de haber encontrado su receta
y tipo al que pertenece */
int eliminaIngre(LISTA_INGRE *li, char *ingre)
{

}

/* Función para buscar la receta a la que pertenece el ingrediente a eliminar*/
int eliminaIngreBuscaRece(LISTA_RECE lr, char *rece, char *ingre)
{

}

/* Esta función busca el tipo de receta, al que pertenece la receta del
ingrediente a eliminar */
int eliminaIngrediente(RECETARIO r, char *tipo, char *rece, char *ingre)
{

}

/* Función para eliminar todos los ingredientes de una receta */
void eliminaIngredientes(LISTA_INGRE *li)
{

}

/* Función para buscar una receta y poder eliminar sus ingredientes */
int eliminaXreceta(LISTA_RECE *lr, char *rece)
{

}

/* Función para buscar tipo de la receta a eliminar */
int eliminaReceta(RECETARIO r, char *tipo, char *rece)
{

}

/* Funciòn para eliminar las todas las recetas de un tipo, eliminando
previamente todos los ingredientes
*/
void eliminaRecetas(LISTA_RECE lr)
{

}

/* Función para eliminar un tipo de receta */
int eliminaTipo(RECETARIO *r, char *tipo)
{

}

/* Función para eliminar un recetario completo */
void eliminaRecetario(RECETARIO *r)
{

}
