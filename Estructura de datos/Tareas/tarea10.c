#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    //Datos comunes
    char nom[25];
    char dom[25];
    char tel[18];
    //Datos genéricos
    int tipo; // 1-Alumno, 2-profr, 3-empleado
    void *ptrGen;
} GEN;

typedef struct
{
    float cal1, cal2, cal3;
    float prom;
} ALU;

typedef struct
{
    float sueldo;
    int hTrab;
    char sec; //p-primaria, s-secundaria, b-bachillerato
}PROF;

typedef struct
{
    float sBase;
    int dpto; // 1, 2 o 3
    float bono;
} EMPLE;

int pideN();
int asignaMem(GEN **ptr, int n);
void capturaTipos(GEN *ptr, int n);
void capturaDatos(GEN *ptr, int n);
void muestraDatos(GEN *ptr, int n);
void calculaProms(GEN *ptr, int n);
float calculaTotSueldoProf(GEN *ptr, int n);
void muestraTotalSueldo(float total);
void liberaMem(GEN *ptr, int n);

int main()
{
    GEN *ptrEscuela;
    int res, nElem;
    float totalSueldo;

    nElem = pideN();
    res = asignaMem(&ptrEscuela, nElem);
    if(res)
    {
        capturaDatos(ptrEscuela, nElem);
        muestraDatos(ptrEscuela, nElem);
        calculaProms(ptrEscuela, nElem);
        muestraDatos(ptrEscuela, nElem);
        totalSueldo=calculaTotSueldoProf(ptrEscuela, nElem);
        muestraTotalSueldo(totalSueldo);
        liberaMem(ptrEscuela, nElem);
    }
    else
        printf("Lastima, no hay memoria\n");
}

/* Función para capturar el No. de elementos */
int pideN()
{
    int n;

    printf("No. de elementos: ");
    scanf("%d", &n);
    return(n);
}

/* Función para asignar memoria al arreglo */
int asignaMem(GEN **ptr, int n)
{
    int resp = 0, i;

    *ptr = (GEN *) malloc( n * sizeof( GEN ));
    if(*ptr) // ¿Apunta ?
    {
        resp = 1;
        // Capturar todos los tipos, puede ser con una función
        capturaTipos(*ptr, n);
        for(i=0; i<n && resp; i++)
        {
            switch( (*ptr + i)->tipo)
            {
                case 1://Alumno
                    (*ptr + i)->ptrGen = malloc(sizeof(ALU) );
                break;
                case 2:// Profesor
                    (*ptr + i)->ptrGen = malloc(sizeof(PROF));
                break;
                case 3://Empleado
                    (*ptr + i)->ptrGen = malloc(sizeof(EMPLE));
            } //switch
            if( !(*ptr+i)->ptrGen) // ¿No apunta ?
            {
                while(--i>=0)
                    free( (*ptr + i)->ptrGen);
                free(*ptr);
                resp = 0; // Romper el ciclo
            }//if memoria para datos
        } // for
    } // if - memoria para el arreglo
    return(resp);
}

/* Función para capturar los tipos */
void capturaTipos(GEN *ptr, int n)
{
    int i;

    for(i=0; i<n; i++)
    {
        printf("Tipo para el dato No. %d: ", i);
        scanf("%d", &(ptr+i)->tipo);
    }
}

/* Función para captura los datos en el arreglo */
void capturaDatos(GEN *ptr, int n)
{
    int i;

    for(i=0; i<n; i++)
    {
        //Datos comunes
        fflush(stdin);
        printf("Dato No. %d\n", i);
        printf("Nombre: ");
        gets((ptr + i)->nom );
        printf("Domicilio: ");
        gets((ptr+i)->dom );
        printf("Tel: ");
        gets((ptr + i)->tel);
        //Genéricos (no comunes)
        switch( (ptr + i)->tipo )
        {
            case 1:// Alumno
                printf("1era. calificaci\xa2n: ");
                scanf("%f", &((ALU *) (ptr + i)->ptrGen)->cal1);
                printf("2da. calificaci\xa2n: ");
                scanf("%f", &((ALU *) (ptr + i)->ptrGen)->cal2);
                printf("3era. calificaci\xa2n: ");
                scanf("%f", &((ALU *) (ptr + i)->ptrGen)->cal3);
                ((ALU *) (ptr + i)->ptrGen)->prom = 0;
            break;
            case 2:// Profesor
                printf("Sueldo por hora: ");
                scanf("%f", &((PROF *) (ptr + i)->ptrGen)->sueldo);
                printf("Horas trabajadas: ");
                scanf("%d", &((PROF *) (ptr + i)->ptrGen)->hTrab);
                fflush(stdin);
                printf("Secci\xa2n: ");
                scanf("%c", &((PROF *) (ptr + i)->ptrGen)->sec);
            break;
            case 3:// Empleado
                printf("Sueldo base: ");
                scanf("%f", &((EMPLE *) (ptr + i)->ptrGen)->sBase);
                printf("Departamento(1,2 o 3): ");
                scanf("%d", &((EMPLE *) (ptr + i)->ptrGen)->dpto);
                printf("Bono: ");
                scanf("%f", &((EMPLE *) (ptr + i)->ptrGen)->bono);
            break;
        } //switch
    } //for
}

/* Función para mostrar los datos del arreglo */
void muestraDatos(GEN *ptr, int n)
{
    int i;

    for(i=0; i<n; i++)
    {
        //Datos comunes
        printf("-------------------\nElemento No. %d\n-------------------\n", i);
        printf("Nombre: %s\n", (ptr+i)->nom);
        printf("Domicilio: %s\n", (ptr+i)->dom);
        printf("Tel: %s\n", (ptr+i)->tel);
        //No comunes(genéricos)
        switch( (ptr+i)->tipo)
        {
            case 1://Alumno
                printf("Alumno:\n");
                printf("Calificaci\xa2n#1: %.2f\n", ((ALU *) (ptr+i)->ptrGen)->cal1);
                printf("Calificaci\xa2n#2: %.2f\n", ((ALU *) (ptr+i)->ptrGen)->cal2);
                printf("Calificaci\xa2n#3: %.2f\n", ((ALU *) (ptr+i)->ptrGen)->cal3);
                printf("Promedio: %.2f\n", ((ALU *) (ptr+i)->ptrGen)->prom);
            break;
            case 2://PROF
                printf("Profesor:\n");
                printf("Sueldo por hora: %.2f\n", ((PROF *) (ptr+i)->ptrGen)->sueldo);
                printf("No. de horas trabajas: %d\n", ((PROF *) (ptr+i)->ptrGen)->hTrab);
                printf("Secci\xa2n: %c\n", ((PROF *) (ptr+i)->ptrGen)->sec);
            break;
            case 3://Empleado
                printf("Empleado:\n");
                printf("Sueldo base: %.2f\n", ((EMPLE *) (ptr+i)->ptrGen)->sBase);
                printf("Departamento: %d\n", ((EMPLE *) (ptr+i)->ptrGen)->dpto);
                printf("Valor de bono: %.2f\n", ((EMPLE *) (ptr+i)->ptrGen)->bono);
            break;
        }
    }
}

/* Función para calcular y asignar el promedio a cada alumno */
void calculaProms(GEN *ptr, int n)
{
    int i;

    for(i=0; i<n; i++)
        if( (ptr+i)->tipo == 1) //¿Alumno?
            ( (ALU *) (ptr+i)->ptrGen)->prom = ( ((ALU *) (ptr+i)->ptrGen)->cal1 + ((ALU *) (ptr+i)->ptrGen)->cal2 + ((ALU *) (ptr+i)->ptrGen)->cal3 )/3;
}

/* Funión para calcular el total pagado por concepto de sueldo a profesores */
float calculaTotSueldoProf(GEN *ptr, int n)
{
    int i;
    float total=0;

    for(i=0; i<n; i++)
        if( (ptr+i)->tipo == 2) //¿Profesor?
            total += ((PROF *) (ptr+i)->ptrGen)->sueldo * ((PROF *) (ptr+i)->ptrGen)->hTrab;

    return(total);
}

/* Función para entregar total de sueldo para profesores */
void muestraTotalSueldo(float total)
{
    printf("Total = %.2f\n", total);
}

/* Función para liberar la memoria */
void liberaMem(GEN *ptr, int n)
{
    int i;

    for(i=0; i<n; i++)
        free((ptr+i)->ptrGen);

    free(ptr);
}
