#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define vacio -1
#define TAM 50

typedef struct entity
{
    char nombre[TAM];
    long listDatos;
    long listAttri;
    long sig;
} ENTITIES;

typedef struct attribute
{
    char nombre[TAM];
    int esPrimaria;
    int tipo;
    int tanio;
    long sig;
} ATTRIBUTES;

enum Options 
{ 
    OPCION0,
    OPCION1, 
    OPCION2, 
    OPCION3,
    OPCION4,
    OPCION5,
    OPCION6,
    OPCION7,
    OPCION8
};

// ---- Funciones de validaciones ----
int esNumeroValido(const char *string);
void limpiarInput(char *input);
void toUpperCase(char *string);
int esNombreValido(const char *nombre);

// ---- Funciones de procesamiento principal ----
void procesarMainMenu(int opcion);
void crearDiccionario(char *nombre);
void abrirDiccionario(char *nombre);

// ---- Funciones de procesamiento de entidades ----
void menuDiccionario(char *nombre);
void procesarDiccMenu(int opcion, char *nombre);
void imprimirDiccionario(const char *nombreDicc);
void crearEntidad(char *nombreDiccionario);

// ---- Funciones de procesamiento de atributos ----



// ---- Funciones de procesamiento de datos ----

int main() 
{
    char opc[TAM];
    int opcion = 0;
    do
    {
        printf("\t----- Bienvenido al diccionario de datos -----\n");
        printf("----- Seleccione una opcion -----\n");
        printf("%d. Crear un nuevo diccionario de datos\n", OPCION1);
        printf("%d. Abrir un diccionario de datos\n", OPCION2);
        printf("%d. Salir\n", OPCION3);
        printf("Seleccione una opcion: ");
        fgets(opc, TAM, stdin);
        if(esNumeroValido(opc))
        {
            opcion = atoi(opc);
            if(opcion < OPCION1 || opcion > OPCION3)
                printf("Error: Opcion invalida, debe ser un número en el rango\n");
        }
            
        else 
            printf("Error: Opcion invalida, debe ser un número entero positivo\n");

        procesarMainMenu(opcion);
    } while (opcion != OPCION3);
    return 0;
}

// ---- Funciones de validaciones ----

int esNumeroValido(const char *string) 
{
    if (string[0] == '\0' || string[0] == '\n') return 0;

    for (int i = 0; string[i] != '\0' && string[i] != '\n'; i++)
        if (!isdigit(string[i])) return 0;
        
    return 1;
}

void limpiarInput(char *input)
{
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
        input[len - 1] = '\0';
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void toUpperCase(char *string)
{
    int length = strlen(string);
    for(int i = 0; i < length; i++)
    {
        string[i] = toupper((unsigned char)string[i]);
    }
}

int esNombreValido(const char *nombre) 
{
    for (int i = 0; nombre[i] != '\0'; i++) 
        if (!isalpha(nombre[i])) 
            return 0; // Caracter no válido
    return 1;
}

// ---- Funciones de procesamiento principal ----

void procesarMainMenu(int opcion)
{
    char nombre[TAM];

    switch (opcion)
    {
        case 1:
            printf("\tCrear un nuevo diccionario de datos\n");
            crearDiccionario(nombre);
        break;
        case 2:
            printf("\tAbrir un diccionario de datos\n");
            abrirDiccionario(nombre);
        break;
        case 3:
            printf("Saliendo del programa...\n");
        break;
    }
}

void crearDiccionario(char *nombre)
{
    long num = vacio;
    fflush(stdin);
    printf("Ingrese el nombre del diccionario: ");
    fgets(nombre, TAM, stdin);
    limpiarInput(nombre);

    FILE *existeArch = fopen(nombre, "rb");
    if(existeArch)
    {
        fclose(existeArch);
        printf("Error: El archivo '%s' ya existe. Por favor, introduzca otro.\n", nombre);
        return;
    }

    FILE *dic = fopen(nombre, "wb");
    if(!dic)
    {
        printf("Error: No se pudo crear el archivo.\n");
        return;
    }
    fwrite(&num, sizeof(long), 1, dic);
    fclose(dic);
    menuDiccionario(nombre);
}

void abrirDiccionario(char *nombre)
{
    fflush(stdin);
    printf("Ingrese el nombre del diccionario que desea abrir: ");
    fgets(nombre, TAM, stdin);
    limpiarInput(nombre);

    FILE *diccionario = fopen(nombre, "rb+");
    if (!diccionario)
    {
        printf("Error: No se pudo encontrar o abrir el archivo '%s'.\n", nombre);
        return;
    }

    fclose(diccionario);
    menuDiccionario(nombre);
}

// ---- Funciones de procesamiento de entidades ----

void menuDiccionario(char *nombre)
{
    char opc[TAM];
    int opcion = 0;

    if(nombre == NULL || strlen(nombre) == 0)
    {
        printf("Error: Ocurrio un error con el diccionario.\n");
        return;
    }

    do
    {
        printf("\n\t----------- Menu de %s ----------- \n", nombre);
        printf("----- Seleccione una opcion -----\n");
        printf("%d. Imprimir la informacion del diccionario \n", OPCION1);
        printf("%d. Crear una entidad \n", OPCION2);
        printf("%d. Eliminar una entidad \n", OPCION3);
        printf("%d. Modificar una entidad \n", OPCION4);
        printf("%d. Seleccionar una entidad \n", OPCION5);
        printf("%d. Poner informacion a la entidad \n", OPCION6);
        printf("%d. Salir \n", OPCION7);
        fflush(stdin);
        printf("Seleccione una opcion: ");
        fgets(opc, TAM, stdin);
        if(esNumeroValido(opc))
        {
            opcion = atoi(opc);
            if(opcion < OPCION1 || opcion > OPCION7)
                printf("Error: Opcion invalida, debe ser un número en el rango\n");
        }
            
        else 
            printf("Error: Opcion invalida, debe ser un número entero positivo\n");
        fflush(stdin);
        procesarDiccMenu(opcion, nombre);
    } while(opcion != OPCION7);
}

void procesarDiccMenu(int opcion, char *nombre)
{
    switch (opcion)
    {
        case 1:
            printf("\tImprimir la informacion del diccionario '%s'\n", nombre);
            imprimirDiccionario(nombre);
        break;
        case 2:
            printf("\tCrear una entidad\n");
            crearEntidad(nombre);
        break;
        case 3:
            printf("\tEliminar una entidad\n");
        break;
        case 4:
            printf("\tModificar una entidad\n");
        break;
        case 5:
            printf("\tSeleccionar una entidad\n");
        break;
        case 6:
            printf("\tPoner informacion a la entidad\n");
        break;
        case 7:
            printf("Saliendo del menu de entidades...\n");
        break;
    }
}

void imprimirDiccionario(const char *nombreDicc) 
{
    FILE *dic = fopen(nombreDicc, "rb");
    if (!dic) 
    {
        printf("Error: No se pudo abrir el diccionario '%s'.\n", nombreDicc);
        return;
    }

    long inicio;
    fread(&inicio, sizeof(long), 1, dic);

    if (inicio == vacio) 
    {
        printf("El diccionario está vacío. No hay entidades registradas.\n");
        fclose(dic);
        return;
    }

    printf("\n--- Entidades en el diccionario '%s' ---\n", nombreDicc);

    long pos = inicio;
    ENTITIES entidad;

    printf("\n------- Informacion del diccionario %s -------\n", nombreDicc);
    printf("| %-30s | %-20s | %-20s | %-10s |\n", "Nombre", "Lista de datos", "Lista de atributos", "Siguiente");
    printf("|-------------------------------------------------------------------------------------------|\n");

    while (pos != vacio) 
    {
        fseek(dic, pos, SEEK_SET);
        fread(&entidad, sizeof(ENTITIES), 1, dic);

        printf("| %-30s | %-20ld | %-20ld | %-10ld |\n", entidad.nombre, entidad.listAttri, entidad.listDatos, entidad.sig);
        printf("|-------------------------------------------------------------------------------------------|\n");

        pos = entidad.sig;
    }

    fclose(dic);
}


void crearEntidad(char *nombreDiccionario) 
{
    FILE *dic = fopen(nombreDiccionario, "rb+");
    if (!dic) 
    {
        printf("Error: No se pudo abrir el diccionario.\n");
        return;
    }

    ENTITIES nueva;
    long inicio;
    fseek(dic, 0, SEEK_SET);
    fread(&inicio, sizeof(long), 1, dic);

    printf("Ingrese el nombre de la nueva entidad: ");
    fgets(nueva.nombre, TAM, stdin);
    limpiarInput(nueva.nombre);

    if (!esNombreValido(nueva.nombre))
    {
        printf("Error: El nombre solo debe contener letras sin espacios ni números.\n");
        fclose(dic);
        return;
    }

    toUpperCase(nueva.nombre);

    // Verificar si ya existe una entidad con ese nombre
    long pos = inicio;
    ENTITIES temp;
    while (pos != vacio) 
    {
        fseek(dic, pos, SEEK_SET);
        fread(&temp, sizeof(ENTITIES), 1, dic);
        if (strcmp(temp.nombre, nueva.nombre) == 0) 
        {
            printf("Error: Ya existe una entidad con ese nombre.\n");
            fclose(dic);
            return;
        }
        pos = temp.sig;
    }

    // Crear nueva entidad
    nueva.listDatos = vacio;
    nueva.listAttri = vacio;
    nueva.sig = vacio;

    fseek(dic, 0, SEEK_END);
    long nuevaPos = ftell(dic);
    fwrite(&nueva, sizeof(ENTITIES), 1, dic);

    // Si no hay entidades, actualizar encabezado
    if (inicio == vacio) 
    {
        fseek(dic, 0, SEEK_SET);
        fwrite(&nuevaPos, sizeof(long), 1, dic);
    } else 
    {
        // Buscar el último nodo para enlazarlo
        pos = inicio;
        while (1) 
        {
            fseek(dic, pos, SEEK_SET);
            fread(&temp, sizeof(ENTITIES), 1, dic);
            if (temp.sig == vacio) break;
            pos = temp.sig;
        }
        temp.sig = nuevaPos;
        fseek(dic, pos, SEEK_SET);
        fwrite(&temp, sizeof(ENTITIES), 1, dic);
    }

    printf("Entidad '%s' creada exitosamente.\n", nueva.nombre);
    fclose(dic);
}

// ---- Funciones de procesamiento de atributos ----



// ---- Funciones de procesamiento de datos ----