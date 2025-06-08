#include <stdio.h>

int main()
{
    printf("\n--- Entidades en el diccionario ---\n");
    printf("\n------- Informacion del diccionario -------\n");
    printf("| %-50s | %-19s | %-19s | %-15s |\n", "Nombre", "Lista de datos", "Lista de atributos", "Siguiente");
    printf("|------------------------------------------------------------------------------------------------------------------|\n");

    printf("| %-107s | \n", "\tNo hay atributos registrados");
    printf("| %-112s | \n", "Atributos de la entidad");
    printf("| %-40s | %-15s | %-15s | %-15s | %-15s |\n", "Nombre", "Primario", "Tipo", "Volumen", "Siguiente");
    printf("|------------------------------------------------------------------------------------------------------------------|\n");

    printf("| %-107s | \n", "\tNo hay datos registrados");
    printf("| %-112s | \n", "Datos de la entidad");
    printf("| %-40s | %-15s | %-15s | %-15s | %-15s |\n", "Nombre", "Primario", "Tipo", "Volumen", "Siguiente");
    printf("|------------------------------------------------------------------------------------------------------------------|\n");
    return 0;
}