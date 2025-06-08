#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define vacio -1
#define TAM 50
#define STRING 100

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
    int tamanio;
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
long obtenerPosEntidad(const char *nombreDicc, const char *nombreEntidad);

// ---- Funciones de procesamiento principal ----
void procesarMainMenu(int opcion);
void crearDiccionario();
void abrirDiccionario();

// ---- Funciones de procesamiento de entidades ----
void menuDiccionario(char *nombre);
void procesarDiccMenu(int opcion, char *nombre);
void imprimirDiccionario(const char *nombreDicc);
void crearEntidad(char *nombreDiccionario);
void ordenarEntidades(char *nombreDiccionario);
void eliminarEntidad(char *nombreDiccionario);
void modificarEntidad(char *nombreDiccionario);
void seleccionarEntidad(char *nombreDiccionario);

// ---- Funciones de procesamiento de atributos ----

void menuEntidad(char *nombreDiccionario, ENTITIES entidad);
void procesarEntidadMenu(char *nombreDiccionario, int opcion, ENTITIES entidad);
void imprimirAtributos(const char *nombreDicc, ENTITIES entidad);
void crearAtributo(const char *nombreDicc, ENTITIES entidad);
void ordenarAtributosPorNombre(const char *nombreDicc, ENTITIES entidad);

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
        printf("%d. Salir\n", OPCION0);
        printf("Seleccione una opcion: ");
        fgets(opc, TAM, stdin);
        if(esNumeroValido(opc))
        {
            opcion = atoi(opc);
            if(opcion < OPCION0 || opcion > OPCION2)
                printf("Error: Opcion invalida, debe ser un número en el rango\n");
        }
            
        else 
            printf("Error: Opcion invalida, debe ser un número entero positivo\n");

        procesarMainMenu(opcion);
    } while (opcion != OPCION0);
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
        if (!isalpha(nombre[i]) && nombre[i] != '_')
            return 0; // Caracter no válido
    return 1;
}

long obtenerPosEntidad(const char *nombreDicc, const char *nombreEntidad) 
{
    FILE *dic = fopen(nombreDicc, "rb");
    if (!dic) return vacio;

    long inicio;
    fread(&inicio, sizeof(long), 1, dic);

    long pos = inicio;
    ENTITIES entidad;

    while (pos != vacio) 
    {
        fseek(dic, pos, SEEK_SET);
        fread(&entidad, sizeof(ENTITIES), 1, dic);

        if (strcmp(entidad.nombre, nombreEntidad) == 0) 
        {
            fclose(dic);
            return pos;
        }

        pos = entidad.sig;
    }

    fclose(dic);
    return vacio;
}


// ---- Funciones de procesamiento principal ----

void procesarMainMenu(int opcion)
{
    switch (opcion)
    {
        case 0:
            printf("Saliendo del programa...\n");
        break;
        case 1:
            crearDiccionario();
        break;
        case 2:
            abrirDiccionario();
        break;
    }
}

void crearDiccionario()
{
    char nombre[TAM];
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

void abrirDiccionario()
{
    char nombre[TAM];
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
        printf("%d. Salir \n", OPCION0);
        fflush(stdin);
        printf("Seleccione una opcion: ");
        fgets(opc, TAM, stdin);
        if(esNumeroValido(opc))
        {
            opcion = atoi(opc);
            if(opcion < OPCION0 || opcion > OPCION5)
                printf("Error: Opcion invalida, debe ser un número en el rango\n");
        }
            
        else 
            printf("Error: Opcion invalida, debe ser un número entero positivo\n");
        fflush(stdin);
        procesarDiccMenu(opcion, nombre);
    } while(opcion != OPCION0);
}

void procesarDiccMenu(int opcion, char *nombre)
{
    switch (opcion)
    {
        case 0:
            printf("Saliendo del menu de entidades...\n");
        break;
        case 1:
            imprimirDiccionario(nombre);
        break;
        case 2:
            crearEntidad(nombre);
            ordenarEntidades(nombre);
        break;
        case 3:
            eliminarEntidad(nombre);
            ordenarEntidades(nombre);
        break;
        case 4:
            modificarEntidad(nombre);
            ordenarEntidades(nombre);
        break;
        case 5:
            seleccionarEntidad(nombre);
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
    printf("\n------- Información del diccionario %s -------\n", nombreDicc);
    printf("| %-50s | %-19s | %-19s | %-15s |\n", "Nombre", "Lista de datos", "Lista de atributos", "Siguiente");
    printf("|------------------------------------------------------------------------------------------------------------------|\n");

    long pos = inicio;
    ENTITIES entidad;

    while (pos != vacio) 
    {
        fseek(dic, pos, SEEK_SET);
        fread(&entidad, sizeof(ENTITIES), 1, dic);

        printf("| %-50s | %-19ld | %-19ld | %-15ld |\n", entidad.nombre, entidad.listDatos, entidad.listAttri, entidad.sig);

        // Imprimir atributos de la entidad
        if (entidad.listAttri != vacio)
        {
            printf("| %-112s | \n", "Atributos de la entidad");
            printf("| %-40s | %-15s | %-15s | %-15s | %-15s |\n", "Nombre", "Primaria", "Tipo", "Volumen", "Siguiente");
            printf("|------------------------------------------------------------------------------------------------------------------|\n");

            long posAttr = entidad.listAttri;
            ATTRIBUTES attr;

            while (posAttr != vacio)
            {
                fseek(dic, posAttr, SEEK_SET);
                fread(&attr, sizeof(ATTRIBUTES), 1, dic);

                printf("| %-40s | %-15d | %-15d | %-15d | %-15ld |\n", attr.nombre, attr.esPrimaria, attr.tipo, attr.tamanio, attr.sig);
                posAttr = attr.sig;
            }
        }
        else 
            printf("| %-107s | \n", "\tNo hay atributos registrados");

        pos = entidad.sig;
    }

    printf("|------------------------------------------------------------------------------------------------------------------|\n");
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

    if (strlen(nueva.nombre) == 0) 
    {
        printf("El nombre no puede estar vacío.\n");
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

void ordenarEntidades(char *nombreDiccionario) 
{
    FILE *dic = fopen(nombreDiccionario, "rb+");
    if (!dic) 
    {
        printf("Error: No se pudo abrir el diccionario.\n");
        return;
    }

    long inicio;
    fread(&inicio, sizeof(long), 1, dic);

    if (inicio == vacio) 
    {
        fclose(dic);
        return;
    }

    // Paso 1: Leer todas las entidades a memoria (lista temporal)
    typedef struct 
    {
        ENTITIES entidad;
        long pos; // Posición en el archivo
    } NodoEntidad;

    NodoEntidad entidades[100]; // Máximo 100 entidades (ajustable)
    int count = 0;
    long posActual = inicio;

    while (posActual != vacio && count < 100) 
    {
        fseek(dic, posActual, SEEK_SET);
        fread(&entidades[count].entidad, sizeof(ENTITIES), 1, dic);
        entidades[count].pos = posActual;
        posActual = entidades[count].entidad.sig;
        count++;
    }

    if (count <= 1) 
    {
        fclose(dic); // No hay nada que ordenar
        return;
    }

    // Paso 2: Ordenar el array en RAM (alfabéticamente)
    for (int i = 0; i < count - 1; i++) 
    {
        for (int j = i + 1; j < count; j++) 
        {
            if (strcmp(entidades[i].entidad.nombre, entidades[j].entidad.nombre) > 0) {
                NodoEntidad temp = entidades[i];
                entidades[i] = entidades[j];
                entidades[j] = temp;
            }
        }
    }

    // Paso 3: Actualizar los punteros sig en archivo
    for (int i = 0; i < count; i++) 
    {
        if (i < count - 1)
            entidades[i].entidad.sig = entidades[i + 1].pos;
        else
            entidades[i].entidad.sig = vacio;

        fseek(dic, entidades[i].pos, SEEK_SET);
        fwrite(&entidades[i].entidad, sizeof(ENTITIES), 1, dic);
    }

    // Paso 4: Actualizar encabezado del archivo con nueva primera entidad
    fseek(dic, 0, SEEK_SET);
    fwrite(&entidades[0].pos, sizeof(long), 1, dic);

    fclose(dic);
}

void eliminarEntidad(char *nombreDiccionario) 
{
    FILE *dic = fopen(nombreDiccionario, "rb+");
    if (!dic) 
    {
        printf("Error: No se pudo abrir el diccionario.\n");
        return;
    }

    long inicio;
    fread(&inicio, sizeof(long), 1, dic);
    if (inicio == vacio) 
    {
        printf("No hay entidades en el diccionario.\n");
        fclose(dic);
        return;
    }

    char nombreBuscar[TAM];
    printf("Ingrese el nombre de la entidad a eliminar: ");
    fgets(nombreBuscar, TAM, stdin);
    limpiarInput(nombreBuscar);

    if (!esNombreValido(nombreBuscar))
    {
        printf("Error: El nombre solo debe contener letras sin espacios ni números.\n");
        fclose(dic);
        return;
    }

    if (strlen(nombreBuscar) == 0) 
    {
        printf("El nombre no puede estar vacío.\n");
        fclose(dic);
        return;
    }

    toUpperCase(nombreBuscar);

    long actualPos = inicio;
    long anteriorPos = vacio;
    ENTITIES actual;

    while (actualPos != vacio) 
    {
        fseek(dic, actualPos, SEEK_SET);
        fread(&actual, sizeof(ENTITIES), 1, dic);

        if (strcmp(actual.nombre, nombreBuscar) == 0) 
        {
            // Entidad encontrada
            if (anteriorPos == vacio) 
            {
                // Es la primera entidad, actualizar encabezado
                fseek(dic, 0, SEEK_SET);
                fwrite(&actual.sig, sizeof(long), 1, dic);
            } else 
            {
                // Actualizar el enlace de la anterior
                ENTITIES anterior;
                fseek(dic, anteriorPos, SEEK_SET);
                fread(&anterior, sizeof(ENTITIES), 1, dic);
                anterior.sig = actual.sig;
                fseek(dic, anteriorPos, SEEK_SET);
                fwrite(&anterior, sizeof(ENTITIES), 1, dic);
            }

            printf("Entidad '%s' eliminada correctamente.\n", actual.nombre);
            fclose(dic);
            return;
        }

        anteriorPos = actualPos;
        actualPos = actual.sig;
    }

    printf("Error: La entidad '%s' no fue encontrada.\n", nombreBuscar);
    fclose(dic);
}

void modificarEntidad(char *nombreDiccionario) 
{
    FILE *dic = fopen(nombreDiccionario, "rb+");
    if (!dic) 
    {
        printf("Error: No se pudo abrir el diccionario.\n");
        return;
    }

    long inicio;
    fread(&inicio, sizeof(long), 1, dic);
    if (inicio == vacio) 
    {
        printf("No hay entidades en el diccionario.\n");
        fclose(dic);
        return;
    }

    char nombreBuscar[TAM];
    printf("Ingrese el nombre de la entidad que desea modificar: ");
    fgets(nombreBuscar, TAM, stdin);
    limpiarInput(nombreBuscar);

    if (!esNombreValido(nombreBuscar))
    {
        printf("Error: El nombre solo debe contener letras sin espacios ni números.\n");
        fclose(dic);
        return;
    }

    if (strlen(nombreBuscar) == 0) 
    {
        printf("El nombre no puede estar vacío.\n");
        fclose(dic);
        return;
    }

    toUpperCase(nombreBuscar);

    long posActual = inicio;
    ENTITIES entidad;
    int encontrada = 0;

    while (posActual != vacio) 
    {
        fseek(dic, posActual, SEEK_SET);
        fread(&entidad, sizeof(ENTITIES), 1, dic);

        if (strcmp(entidad.nombre, nombreBuscar) == 0) 
        {
            encontrada = 1;
            break;
        }

        posActual = entidad.sig;
    }

    if (!encontrada) 
    {
        printf("Error: La entidad '%s' no fue encontrada.\n", nombreBuscar);
        fclose(dic);
        return;
    }

    // Pedir nuevo nombre
    char nuevoNombre[TAM];
    printf("Ingrese el nuevo nombre para la entidad: ");
    fgets(nuevoNombre, TAM, stdin);
    limpiarInput(nuevoNombre);

    // Validar caracteres
    if (!esNombreValido(nuevoNombre)) 
    {
        printf("Error: El nombre solo debe contener letras sin espacios ni números.\n");
        fclose(dic);
        return;
    }

    toUpperCase(nuevoNombre);

    if (strcasecmp(nombreBuscar, nuevoNombre) == 0) 
    {
        printf("El nombre ingresado es igual al actual. No se realizaron cambios.\n");
        fclose(dic);
        return;
    }


    // Verificar duplicados
    long tempPos = inicio;
    ENTITIES temp;
    while (tempPos != vacio) 
    {
        fseek(dic, tempPos, SEEK_SET);
        fread(&temp, sizeof(ENTITIES), 1, dic);
        if (strcmp(temp.nombre, nuevoNombre) == 0) 
        {
            printf("Error: Ya existe una entidad con ese nombre.\n");
            fclose(dic);
            return;
        }
        tempPos = temp.sig;
    }

    // Actualizar el nombre
    strcpy(entidad.nombre, nuevoNombre);
    fseek(dic, posActual, SEEK_SET);
    fwrite(&entidad, sizeof(ENTITIES), 1, dic);

    printf("Entidad modificada exitosamente. Nuevo nombre: %s\n", entidad.nombre);
    fclose(dic);
}

void seleccionarEntidad(char *nombreDiccionario) 
{
    FILE *dic = fopen(nombreDiccionario, "rb");
    if (!dic) 
    {
        printf("Error: No se pudo abrir el diccionario.\n");
        return;
    }

    long inicio;
    fread(&inicio, sizeof(long), 1, dic);
    if (inicio == vacio) 
    {
        printf("No hay entidades registradas.\n");
        fclose(dic);
        return;
    }

    char nombreBuscado[TAM];
    printf("Ingrese el nombre de la entidad que desea seleccionar: ");
    fgets(nombreBuscado, TAM, stdin);
    limpiarInput(nombreBuscado);

    if (!esNombreValido(nombreBuscado))
    {
        printf("Error: El nombre solo debe contener letras sin espacios ni números.\n");
        fclose(dic);
        return;
    }

    if (strlen(nombreBuscado) == 0) 
    {
        printf("El nombre no puede estar vacío.\n");
        fclose(dic);
        return;
    }

    toUpperCase(nombreBuscado);

    ENTITIES entidad;
    long pos = inicio;
    int encontrada = 0;

    while (pos != vacio) 
    {
        fseek(dic, pos, SEEK_SET);
        fread(&entidad, sizeof(ENTITIES), 1, dic);

        if (strcmp(entidad.nombre, nombreBuscado) == 0) 
        {
            encontrada = 1;
            break;
        }
        pos = entidad.sig;
    }

    fclose(dic);

    if (!encontrada) 
    {
        printf("Error: La entidad '%s' no fue encontrada.\n", nombreBuscado);
        return;
    }

    // Aquí se llama al menú específico de la entidad
    menuEntidad(nombreDiccionario, entidad);
}

// ---- Funciones de procesamiento de atributos ----

void menuEntidad(char *nombreDiccionario, ENTITIES entidad)
{
    char opc[TAM];
    int opcion = 0;

    if(nombreDiccionario == NULL || strlen(nombreDiccionario) == 0)
    {
        printf("Error: Ocurrio un error con el diccionario.\n");
        return;
    }

    do
    {
        printf("\n\t----------- Menu de %s ----------- \n", entidad.nombre);
        printf("----- Seleccione una opcion -----\n");
        printf("%d. Imprimir attributos de la entidad \n", OPCION1);
        printf("%d. Crear attributos de la entidad \n", OPCION2);
        printf("%d. Eliminar attributos de la entidad \n", OPCION3);
        printf("%d. Modificar attributos de la entidad \n", OPCION4);
        printf("%d. Imprimir datos \n", OPCION5);
        printf("%d. Agregar datos a los attributos \n", OPCION6);
        printf("%d. Eliminar datos a los attributos \n", OPCION7);
        printf("%d. Modificar datos a los attributos \n", OPCION8);
        printf("%d. Salir \n", OPCION0);
        fflush(stdin);
        printf("Seleccione una opcion: ");
        fgets(opc, TAM, stdin);
        if(esNumeroValido(opc))
        {
            opcion = atoi(opc);
            if(opcion < OPCION0 || opcion > OPCION8)
                printf("Error: Opcion invalida, debe ser un número en el rango\n");
        }
            
        else 
            printf("Error: Opcion invalida, debe ser un número entero positivo\n");
        fflush(stdin);
        procesarEntidadMenu(nombreDiccionario, opcion, entidad);
    } while(opcion != OPCION0);
}

void procesarEntidadMenu(char *nombreDiccionario, int opcion, ENTITIES entidad)
{
    switch (opcion)
    {
        case 0:
            printf("Saliendo del menu de atributos...\n");
        break;
        case 1:
            printf("\tImprimir la informacion de la entidad '%s'\n", entidad.nombre);
            long posEntidad = obtenerPosEntidad(nombreDiccionario, entidad.nombre);
            if (posEntidad != vacio)
            {
                FILE *dic = fopen(nombreDiccionario, "rb");
                fseek(dic, posEntidad, SEEK_SET);
                fread(&entidad, sizeof(ENTITIES), 1, dic);
                fclose(dic);
            }
            imprimirAtributos(nombreDiccionario, entidad);
        break;
        case 2:
            printf("\tCrear atributos\n");
            crearAtributo(nombreDiccionario, entidad);
            ordenarAtributosPorNombre(nombreDiccionario, entidad);
        break;
        case 3:
            printf("\tEliminar atributos\n");
        break;
        case 4:
            printf("\tModificar atributos\n");
        break;
        case 5:
            printf("\tAgregar datos\n");
        break;
        case 6:
            printf("\tEliminar datos\n");
        break;
        case 7:
            printf("\tModificar datos\n");
        break;
    }
}

void imprimirAtributos(const char *nombreDicc, ENTITIES entidad)
{
    FILE *dic = fopen(nombreDicc, "rb");
    if (!dic)
    {
        printf("Error: No se pudo abrir el diccionario '%s'.\n", nombreDicc);
        return;
    }

    if (entidad.listAttri == vacio)
    {
        printf("La entidad '%s' no tiene atributos registrados.\n", entidad.nombre);
        fclose(dic);
        return;
    }

    printf("\n--- Atributos de la entidad '%s' ---\n", entidad.nombre);
    printf("| %-40s | %-15s | %-15s | %-15s | %-15s |\n", "Nombre", "Primaria", "Tipo", "Volumen", "Siguiente");
    printf("|------------------------------------------------------------------------------------------------------------------|\n");

    long posAttr = entidad.listAttri;
    ATTRIBUTES attr;

    while (posAttr != vacio)
    {
        fseek(dic, posAttr, SEEK_SET);
        fread(&attr, sizeof(ATTRIBUTES), 1, dic);

        const char *tipoStr;
        switch (attr.tipo)
        {
            case 0: tipoStr = "BIT"; break;
            case 1: tipoStr = "INTEGER"; break;
            case 2: tipoStr = "FLOAT"; break;
            case 3: tipoStr = "CHAR"; break;
            case 4: tipoStr = "STRING"; break;
            default: tipoStr = "DESCONOCIDO";
        }

        printf("| %-40s | %-15s | %-15s | %-15d | %-15ld |\n",
               attr.nombre,
               attr.esPrimaria ? "Si" : "No",
               tipoStr,
               attr.tamanio,
               attr.sig);

        posAttr = attr.sig;
    }

    printf("|---------------------------------------------------------------------------------------------|\n");
    fclose(dic);
}

void crearAtributo(const char *nombreDicc, ENTITIES entidad)
{
    FILE *dic = fopen(nombreDicc, "rb+");
    if (!dic)
    {
        printf("Error: no se pudo abrir el diccionario.\n");
        return;
    }

    // Verificar si la entidad tiene datos
    if (entidad.listDatos != vacio)
    {
        printf("No se pueden agregar atributos porque la entidad '%s' ya tiene datos registrados.\n", entidad.nombre);
        fclose(dic);
        return;
    }

    ATTRIBUTES nuevoAtributo;
    int valido, longitudCadena;

    // Solicitar nombre del atributo
    do
    {
        printf("Ingrese el nombre del atributo: ");
        fgets(nuevoAtributo.nombre, STRING, stdin);
        limpiarInput(nuevoAtributo.nombre);

        if (strlen(nuevoAtributo.nombre) == 0) 
        {
            printf("El nombre no puede estar vacío.\n");
            fclose(dic);
            return;
        }

        if (!esNombreValido(nuevoAtributo.nombre))
        {
            printf("Nombre invalido. Solo se permiten letras y guion bajo (_).\n");
            valido = 0;
        }
        else
        {
            valido = 1;
        }

        toUpperCase(nuevoAtributo.nombre);
    } while (!valido);

    // Solicitar si es llave primaria (0 o 1)
    do
    {
        printf("¿Es llave primaria? (1 = sí, 0 = no): ");
        if (scanf("%d", &nuevoAtributo.esPrimaria) != 1 || (nuevoAtributo.esPrimaria != 0 && nuevoAtributo.esPrimaria != 1))
        {
            printf("Valor invalido. Debe ser 0 o 1.\n");
            while (getchar() != '\n');
            valido = 0;
        }
        else
        {
            valido = 1;
        }
    } while (!valido);

    // Solicitar tipo de dato
    printf("Tipos disponibles:\n");
    printf(" 0 - BIT\n");
    printf(" 1 - INTEGER\n");
    printf(" 2 - FLOAT\n");
    printf(" 3 - CHAR\n");
    printf(" 4 - STRING\n");

    do
    {
        printf("Seleccione el tipo de dato: ");
        if (scanf("%d", &nuevoAtributo.tipo) != 1 || nuevoAtributo.tipo < 0 || nuevoAtributo.tipo > 4)
        {
            printf("Tipo invalido. Debe ser un numero entre 0 y 4.\n");
            while (getchar() != '\n');
            valido = 0;
        }
        else
        {
            valido = 1;
        }
    } while (!valido);

    // Calcular tamaño según tipo
    switch (nuevoAtributo.tipo)
    {
        case 0: // BIT
            nuevoAtributo.tamanio = sizeof(unsigned char);
            break;
        case 1: // INTEGER
            nuevoAtributo.tamanio = sizeof(int);
            break;
        case 2: // FLOAT
            nuevoAtributo.tamanio = sizeof(float);
            break;
        case 3: // CHAR
            nuevoAtributo.tamanio = sizeof(char);
            break;
        case 4: // STRING
            do
            {
                printf("Ingrese el tamaño de la cadena (1 a 100): ");
                if (scanf("%d", &longitudCadena) != 1 || longitudCadena <= 0 || longitudCadena > 100)
                {
                    printf("Tamaño invalido. Intente de nuevo.\n");
                    while (getchar() != '\n');
                    valido = 0;
                }
                else
                {
                    valido = 1;
                }
            } while (!valido);
            nuevoAtributo.tamanio = sizeof(char) * longitudCadena;
            break;
    }

    nuevoAtributo.sig = vacio;

    // Buscar posición de inserción
    fseek(dic, 0, SEEK_END);
    long posNuevoAttr = ftell(dic);

    // Actualizar la lista de atributos en la entidad
    if (entidad.listAttri == vacio)
    {
        // Primer atributo
        entidad.listAttri = posNuevoAttr;

        long posEntidad = obtenerPosEntidad(nombreDicc, entidad.nombre);
        if (posEntidad != vacio)
        {
            fseek(dic, posEntidad, SEEK_SET);
            fwrite(&entidad, sizeof(ENTITIES), 1, dic);
        }

        // Buscar la entidad en el archivo y actualizarla
        long pos = vacio;
        long actual;
        ENTITIES temp;

        // Leer cabecera
        fseek(dic, 0, SEEK_SET);
        fread(&actual, sizeof(long), 1, dic);

        while (actual != vacio)
        {
            fseek(dic, actual, SEEK_SET);
            fread(&temp, sizeof(ENTITIES), 1, dic);

            if (strcmp(temp.nombre, entidad.nombre) == 0)
            {
                pos = actual;
                break;
            }
            actual = temp.sig;
        }

        if (pos != vacio)
        {
            fseek(dic, pos, SEEK_SET);
            fwrite(&entidad, sizeof(ENTITIES), 1, dic);
        }
    }
    else
    {
        // Buscar el último atributo para enlazar el nuevo
        long posAttr = entidad.listAttri;
        ATTRIBUTES tempAttr;

        while (posAttr != vacio)
        {
            fseek(dic, posAttr, SEEK_SET);
            fread(&tempAttr, sizeof(ATTRIBUTES), 1, dic);

            if (tempAttr.sig == vacio)
                break;

            posAttr = tempAttr.sig;
        }

        // Enlazar
        tempAttr.sig = posNuevoAttr;
        fseek(dic, posAttr, SEEK_SET);
        fwrite(&tempAttr, sizeof(ATTRIBUTES), 1, dic);
    }

    // Guardar nuevo atributo
    fseek(dic, posNuevoAttr, SEEK_SET);
    fwrite(&nuevoAtributo, sizeof(ATTRIBUTES), 1, dic);

    printf("Atributo agregado correctamente.\n");

    fclose(dic);
}

void ordenarAtributosPorNombre(const char *nombreDicc, ENTITIES entidad)
{
    if (entidad.listAttri == -1)
        return; // No hay atributos que ordenar

    FILE *dic = fopen(nombreDicc, "rb+");
    if (!dic)
    {
        printf("Error: no se pudo abrir el diccionario.\n");
        return;
    }

    // Paso 1: Cargar todos los atributos de la entidad
    long posiciones[100];        // Posiciones físicas en el archivo
    ATTRIBUTES atributos[100];   // Atributos en memoria
    int total = 0;
    long posActual = entidad.listAttri;

    while (posActual != -1 && total < 100)
    {
        fseek(dic, posActual, SEEK_SET);
        fread(&atributos[total], sizeof(ATTRIBUTES), 1, dic);
        posiciones[total] = posActual;
        posActual = atributos[total].sig;
        total++;
    }

    // Paso 2: Ordenar los atributos alfabéticamente por nombre (burbuja simple)
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = i + 1; j < total; j++)
        {
            if (strcmp(atributos[i].nombre, atributos[j].nombre) > 0)
            {
                // Intercambiar atributos
                ATTRIBUTES tempAttr = atributos[i];
                atributos[i] = atributos[j];
                atributos[j] = tempAttr;

                // Intercambiar posiciones
                long tempPos = posiciones[i];
                posiciones[i] = posiciones[j];
                posiciones[j] = tempPos;
            }
        }
    }

    // Paso 3: Reescribir los atributos con los nuevos `sig`
    for (int i = 0; i < total; i++)
    {
        atributos[i].sig = (i < total - 1) ? posiciones[i + 1] : -1;
        fseek(dic, posiciones[i], SEEK_SET);
        fwrite(&atributos[i], sizeof(ATTRIBUTES), 1, dic);
    }

    // Paso 4: Actualizar listAttri de la entidad
    entidad.listAttri = posiciones[0];

    // Buscar y actualizar la entidad en el archivo
    long actual;
    ENTITIES tempEnt;

    fseek(dic, 0, SEEK_SET);
    fread(&actual, sizeof(long), 1, dic);

    while (actual != -1)
    {
        fseek(dic, actual, SEEK_SET);
        fread(&tempEnt, sizeof(ENTITIES), 1, dic);

        if (strcmp(tempEnt.nombre, entidad.nombre) == 0)
        {
            fseek(dic, actual, SEEK_SET);
            fwrite(&entidad, sizeof(ENTITIES), 1, dic);
            break;
        }
        actual = tempEnt.sig;
    }

    fclose(dic);
}


// ---- Funciones de procesamiento de datos ----