#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define vacio -1
#define N 50

typedef struct entidad
{
	char nom[N];
	long listDatos;
	long ListAtrubutos;
	long sig;
} Entidades; 

typedef struct Atribute
{
	char name[50];
	bool isPrimary;
	long type;
	long size; 
	long nextAtribute;
} ATTRIBUTE;

void imprimirAtributos(FILE *Diccionario, long ListAtrubutos);
long appendAttribute(FILE *dataDictionary, ATTRIBUTE newAttribute);
void reorderAttributes(FILE *dataDictionary, long currentAttributePointer, const char *newAttributeName, long newAttributeDirection, bool clavePrim);
void CreateAttribute(FILE *dataDictionary, Entidades currentEntity);
int eliminaAtributo(FILE *Diccionario, char nom[N], long cab);
void modificaAtributo(FILE *dataDictionary, char nom[50], long cab);
void menuAtributos(char *diccionario, Entidades entidad);
int elimina(FILE *Diccionario, char nom[N]);
void OrdenarEntidad(FILE *Diccionario, long EntidadActual, const char *nuevoNombreEntidad, long nuevaDirEntidad);
long AgregarEntidad(FILE *Diccionario, Entidades nuevaEntidad);
void imprimirDatos(FILE *Diccionario, long LDatos, long LAtributos);
void imprimir(FILE *Diccionario);
Entidades findEntity(FILE *dataDictionary, char entityName[50]);
void modificarEntidad(FILE *Diccionario, char nom[50]);
void AgregarDato(FILE *Diccionario, long nuevoDato, long LDatos, long LAtributos);
void insertarDatos(FILE *Diccionario, Entidades entidad);
void EntidadesMenu(char diccionario[N]);
void menu();

void imprimirAtributos(FILE *Diccionario, long ListAtrubutos)
{
	ATTRIBUTE atributo;
	long direccion;
	
	printf("Atributos\n");

	fseek(Diccionario, ListAtrubutos, SEEK_SET);
	fread(&direccion, sizeof(long), 1, Diccionario);

	if (direccion == -1 || ListAtrubutos == -1)
	{
		printf("---No hay Atributos\n");
	}
	else
	{
		while (direccion != -1)
		{
			fseek(Diccionario, direccion, SEEK_SET);
			fread(&atributo.name, N, 1, Diccionario);
			fread(&atributo.isPrimary, sizeof(bool), 1, Diccionario);
			fread(&atributo.type, sizeof(long), 1, Diccionario);
			fread(&atributo.size, sizeof(long), 1, Diccionario);
			fread(&direccion, sizeof(long), 1, Diccionario);
			printf("  +%s\n", atributo.name);
		}
	}
}

long appendAttribute(FILE *dataDictionary, ATTRIBUTE newAttribute)
{
	fseek(dataDictionary, 0, SEEK_END);
	long entityDirection = ftell(dataDictionary);
	
	fwrite(newAttribute.name, 50, 1, dataDictionary);
	fwrite(&newAttribute.isPrimary, sizeof(bool), 1, dataDictionary);
	fwrite(&newAttribute.type, sizeof(long), 1, dataDictionary);
	fwrite(&newAttribute.size, sizeof(long), 1, dataDictionary);
	fwrite(&newAttribute.nextAtribute, sizeof(long), 1, dataDictionary);
	
	return entityDirection;
}

void reorderAttributes(FILE *dataDictionary, long currentAttributePointer, const char *newAttributeName, long newAttributeDirection, bool clavePrim)
{
	long currentAttributeDirection = -1;
	
	fseek(dataDictionary, currentAttributePointer, SEEK_SET);
	fread(&currentAttributeDirection, sizeof(currentAttributeDirection), 1, dataDictionary);
	
	if (currentAttributeDirection == -1L)
	{
		fseek(dataDictionary, currentAttributePointer, SEEK_SET);
		fwrite(&newAttributeDirection, sizeof(long), 1, dataDictionary);
	}
	else
	{
		char currentAttributeName[50];
		long nextHeaderPointer;
		bool sigClavePrim;
		
		fseek(dataDictionary, currentAttributeDirection, SEEK_SET);
		fread(&currentAttributeName, sizeof(char), 50, dataDictionary);
		nextHeaderPointer = ftell(dataDictionary) + sizeof(bool) + (sizeof(long) * 2);
		fread(&sigClavePrim, sizeof(bool), 1, dataDictionary);

		if (clavePrim)
		{
			if (sigClavePrim == clavePrim)
			{
				printf("Ya existe esa clave!\n");
				return;
			}
			fseek(dataDictionary, currentAttributePointer, SEEK_SET);
			fwrite(&newAttributeDirection, sizeof(long), 1, dataDictionary);
			fseek(dataDictionary, newAttributeDirection + 50 + sizeof(bool) + (sizeof(long) * 2), SEEK_SET);
			fwrite(&currentAttributeDirection, sizeof(long), 1, dataDictionary);
			return;
		}

		if (strcmp(currentAttributeName, newAttributeName) == 0)
		{
			printf("Ya existe un atributo con el mismo nombre, favor de seleccionar otro.\n");
			return;
		}
		else
		{
			if (strcmp(currentAttributeName, newAttributeName) < 0 || sigClavePrim || clavePrim)
			{
				reorderAttributes(dataDictionary, nextHeaderPointer, newAttributeName, newAttributeDirection, 0);
			}
			else
			{
				
				fseek(dataDictionary, currentAttributePointer, SEEK_SET);
				fwrite(&newAttributeDirection, sizeof(long), 1, dataDictionary);
				
				fseek(dataDictionary, newAttributeDirection + 50 + sizeof(bool) + (sizeof(long) * 2), SEEK_SET);
				fwrite(&currentAttributeDirection, sizeof(long), 1, dataDictionary);
			}
		}
	}
}

void CreateAttribute(FILE *dataDictionary, Entidades currentEntity)
{
	ATTRIBUTE newAttribute;
	int tamanio, aux;
	
	printf("\nNombre del nuevo atributo: ");
	
	scanf("%s", newAttribute.name);
	
	printf("Es la clave primaria? 1)Si 0)No : ");
	scanf("%d", &aux);
	newAttribute.isPrimary = aux;
	
	printf("Tipo de atributo? 1)int 2)long 3)float 4)char 5)bool : ");
	scanf("%d", &aux);
	newAttribute.type = aux;
	
	switch (newAttribute.type)
	{
	case 1:
		newAttribute.size = sizeof(int);
		break;
		
	case 2:
		newAttribute.size = sizeof(long);
		break;
		
	case 3:
		newAttribute.size = sizeof(float);
		break;
		
	case 4:
		printf("Cuantas letras tiene?: ");
		scanf("%d", &tamanio);
		newAttribute.size = sizeof(char) * tamanio;
		break;
		
	case 5:
		newAttribute.size = sizeof(bool);
		break;
	default:
		printf("Tipo no valido, favor de volver a intentarlo.\n");
		break;
	}
	
	newAttribute.nextAtribute = vacio;
	
	long attributeDirection = appendAttribute(dataDictionary, newAttribute);
	reorderAttributes(dataDictionary, currentEntity.ListAtrubutos, newAttribute.name, attributeDirection, newAttribute.isPrimary);
}

int eliminaAtributo(FILE *Diccionario, char nom[N], long cab)
{
	rewind(Diccionario);
	if (!Diccionario)
		return 0;
	
	ATTRIBUTE atributo;
	long ant, ptr, ptrdir;
	
	fseek(Diccionario, cab, SEEK_SET);
	fread(&ptr, sizeof(long), 1, Diccionario);
	if (ptr == -1)
	{
		fclose(Diccionario);
		return 0; 
	}
	fseek(Diccionario, ptr, SEEK_SET);
	fread(atributo.name, N, 1, Diccionario);
	fread(&atributo.isPrimary, sizeof(bool), 1, Diccionario);
	fread(&atributo.type, sizeof(long), 1, Diccionario);
	fread(&atributo.size, sizeof(long), 1, Diccionario);
	ptrdir = ftell(Diccionario);               
	fread(&ptr, sizeof(long), 1, Diccionario); 
	if (strcmp(atributo.name, nom) == 0)
	{
		fseek(Diccionario, cab, SEEK_SET);
		fwrite(&ptr, sizeof(long), 1, Diccionario); 
		return 1;                                   
	}

	while (ptr != -1 && strcmp(atributo.name, nom) != 0)
	{
		ant = ptrdir;
		fseek(Diccionario, ptr, SEEK_SET);
		fread(atributo.name, N, 1, Diccionario);
		fread(&atributo.isPrimary, sizeof(bool), 1, Diccionario);
		fread(&atributo.type, sizeof(long), 1, Diccionario);
		fread(&atributo.size, sizeof(long), 1, Diccionario);
		ptrdir = ftell(Diccionario);               
		fread(&ptr, sizeof(long), 1, Diccionario); 
	}

	if (ptr == -1 && strcmp(atributo.name, nom) != 0)
	{
		return 0;
	}

	fseek(Diccionario, ant, SEEK_SET);          
	
	fwrite(&ptr, sizeof(long), 1, Diccionario); 
	return 1;
}

void modificaAtributo(FILE *dataDictionary, char nom[50], long cab)
{
	rewind(dataDictionary);
	long DirAtributo;
	ATTRIBUTE newAttribute;
	
	fseek(dataDictionary, cab, SEEK_SET);
	fread(&DirAtributo, sizeof(long), 1, dataDictionary);
	if (DirAtributo == -1)
	{
		printf("No hay Atributos");
		return;
	}
	
	fseek(dataDictionary, DirAtributo, SEEK_SET);
	fread(newAttribute.name, 50, 1, dataDictionary);
	fread(&newAttribute.isPrimary, sizeof(bool), 1, dataDictionary);
	fread(&newAttribute.type, sizeof(long), 1, dataDictionary);
	fread(&newAttribute.size, sizeof(long), 1, dataDictionary);
	fread(&DirAtributo, sizeof(long), 1, dataDictionary);
	while (DirAtributo != -1 && (strcmp(newAttribute.name, nom)) != 0)
	{
		fseek(dataDictionary, DirAtributo, SEEK_SET);
		fread(newAttribute.name, 50, 1, dataDictionary);
		fread(&newAttribute.isPrimary, sizeof(bool), 1, dataDictionary);
		fread(&newAttribute.type, sizeof(long), 1, dataDictionary);
		fread(&newAttribute.size, sizeof(long), 1, dataDictionary);
		fread(&DirAtributo, sizeof(long), 1, dataDictionary);
	}
	newAttribute.nextAtribute = vacio;
	if (DirAtributo == -1 && (strcmp(newAttribute.name, nom)) != 0)
	{
		printf("No existe el atributo, favor de volver a intentarlo.\n");
		return;
	}
	eliminaAtributo(dataDictionary, nom, cab);
	
	printf("Nuevo nombre: ");
	scanf("%s", newAttribute.name);
	
	DirAtributo = appendAttribute(dataDictionary, newAttribute);
	reorderAttributes(dataDictionary, cab, newAttribute.name, DirAtributo, newAttribute.isPrimary);
}

void menuAtributos(char *diccionario, Entidades entidad)
{
	FILE *Diccionario = fopen(diccionario, "rb+");
	int ops;
	char nom[N];
	
	printf("----------Atributos de %s----------\n", entidad.nom);
	printf(" 1)Imprimir Atributos\n 2)Nuevo Atributo\n 3)Eliminar Atributo\n 4)Modificar Atributo\n 5)Seleccionar atributo 0)salir\n Opcion: ");
	scanf("%d", &ops);
	
	switch (ops)
	{
	case 1:
		printf("--%s--\n", entidad.nom);
		imprimirAtributos(Diccionario, entidad.ListAtrubutos);
		break;
	case 2:
		CreateAttribute(Diccionario, entidad);
		break;
	case 3:
		printf("Nombre: ");
		scanf("%s", nom);
		if (eliminaAtributo(Diccionario, nom, entidad.ListAtrubutos))
			printf("Eliminado correctamente!\n");
		else
			printf("No fue posible eliminarlo, favor de volver a intentarlo.\n");
		break;
	case 4:
		printf("Nombre: ");
		scanf("%s", nom);
		modificaAtributo(Diccionario, nom, entidad.ListAtrubutos);
		break;
	case 0:
		fclose(Diccionario);
		EntidadesMenu(diccionario);
		break;
	default:
		printf("Opcion no valida, favor de volver a intentar.\n");
		break;
	}
	
	fclose(Diccionario);
	menuAtributos(diccionario, entidad);
}

int elimina(FILE *Diccionario, char nom[N])
{
	rewind(Diccionario);
	if (!Diccionario)
		return 0;
	
	Entidades entidad;
	long ant, ptr, ptrdir;
	
	fread(&ptr, sizeof(long), 1, Diccionario);
	if (ptr == -1)
	{
		return 0;
	}
	
	fseek(Diccionario, ptr, SEEK_SET);
	fread(entidad.nom, N, 1, Diccionario);
	fread(&entidad.listDatos, sizeof(long), 1, Diccionario);
	fread(&entidad.ListAtrubutos, sizeof(long), 1, Diccionario);
	ptrdir = ftell(Diccionario);            
	fread(&ptr, sizeof(long), 1, Diccionario);
	
	if (strcmp(entidad.nom, nom) == 0)
	{
		rewind(Diccionario);
		fwrite(&ptr, sizeof(long), 1, Diccionario);
		
		return 1;
	}
	
	while (ptr != -1 && strcmp(entidad.nom, nom) != 0)
	{
		ant = ptrdir;
		fseek(Diccionario, ptr, SEEK_SET);
		fread(entidad.nom, N, 1, Diccionario);
		fread(&entidad.listDatos, sizeof(long), 1, Diccionario);
		fread(&entidad.ListAtrubutos, sizeof(long), 1, Diccionario);
		ptrdir = ftell(Diccionario);
		fread(&ptr, sizeof(long), 1, Diccionario);
	}
	
	if (ptr == -1 && strcmp(entidad.nom, nom) != 0)
	{
		return 0;
	}
	
	fseek(Diccionario, ant, SEEK_SET);         
	fwrite(&ptr, sizeof(long), 1, Diccionario);
	
	return 1; 
}

void OrdenarEntidad(FILE *Diccionario, long EntidadActual, const char *nuevoNombreEntidad, long nuevaDirEntidad)
{
	long DirEntidad = -1;
	
	fseek(Diccionario, EntidadActual, SEEK_SET);
	fread(&DirEntidad, sizeof(DirEntidad), 1, Diccionario);
	
	if (DirEntidad == -1L)
	{
		fseek(Diccionario, EntidadActual, SEEK_SET);
		fwrite(&nuevaDirEntidad, sizeof(long), 1, Diccionario);
	}
	else
	{
		char currentEntityName[50];
		long nextHeaderPointer;
		
		fseek(Diccionario, DirEntidad, SEEK_SET);
		fread(&currentEntityName, sizeof(char), 50, Diccionario);
		nextHeaderPointer = ftell(Diccionario) + (sizeof(long) * 2);
		if (strcmp(currentEntityName, nuevoNombreEntidad) < 0)
		{
			OrdenarEntidad(Diccionario, nextHeaderPointer, nuevoNombreEntidad, nuevaDirEntidad);
		}
		else
		{
			if (strcmp(currentEntityName, nuevoNombreEntidad) == 0)
			{
				printf("Ya existe esta Entidad! \n");
			}
			else
			{
				fseek(Diccionario, EntidadActual, SEEK_SET);
				fwrite(&nuevaDirEntidad, sizeof(long), 1, Diccionario);
				fseek(Diccionario, nuevaDirEntidad + 50 + (sizeof(long) * 2), SEEK_SET);
				fwrite(&DirEntidad, sizeof(long), 1, Diccionario);
			}
		}
	}
}

long AgregarEntidad(FILE *Diccionario, Entidades nuevaEntidad)
{
    fseek(Diccionario, 0, SEEK_END);
    long DirEntidad = ftell(Diccionario);
    fwrite(nuevaEntidad.nom, 50, 1, Diccionario);
    fwrite(&nuevaEntidad.listDatos, sizeof(long), 1, Diccionario);
    fwrite(&nuevaEntidad.ListAtrubutos, sizeof(long), 1, Diccionario);
    fwrite(&nuevaEntidad.sig, sizeof(long), 1, Diccionario); // <-- aquí
    return DirEntidad;
}

void imprimirDatos(FILE *Diccionario, long LDatos, long LAtributos)
{
	long ListAtributos, sig;
	int datoint;
	bool datobool;
	long datolong;
	float datofloat;
	char datochar[N];
	
	ATTRIBUTE atributo;
	
	sig = LDatos;
	
	if (sig == vacio)
	{
		printf("No hay datos...\n");
	}
	else
	{
		while (sig != vacio)
		{
			ListAtributos = LAtributos;//no
			LDatos = sig;
			while (ListAtributos != -1)
			{
				fseek(Diccionario, ListAtributos, SEEK_SET);
				fread(atributo.name, N, 1, Diccionario);
				fread(&atributo.isPrimary, sizeof(bool), 1, Diccionario);
				fread(&atributo.type, sizeof(long), 1, Diccionario);
				fread(&atributo.size, sizeof(long), 1, Diccionario);
				fread(&ListAtributos, sizeof(long), 1, Diccionario);
				
				fseek(Diccionario, LDatos, SEEK_SET);
				switch (atributo.type)
				{
				case 1:
					fread(&datoint, sizeof(int), 1, Diccionario);
					printf("|%d", datoint);
					break;
				case 2:
					fread(&datolong, sizeof(long), 1, Diccionario);
					printf("|%li", datolong);
					break;
				case 3:
					fread(&datofloat, sizeof(float), 1, Diccionario);
					printf("|%.2f", datofloat);
					break;
				case 4:
					fread(&datochar, sizeof(char), N, Diccionario);
					printf("|%s", datochar);
					break;
				case 5:
					fread(&datobool, sizeof(bool), 1, Diccionario);
					if (datobool)
						printf("|Verdadero");
					else
						printf("|Falso");
					break;
				}
				LDatos = ftell(Diccionario);
			}
			fread(&sig, sizeof(long), 1, Diccionario);
			printf("\n");
		}
	}
}

void imprimir(FILE *Diccionario)
{
    Entidades Entidad;
    long direccion;

    rewind(Diccionario);

    fread(&direccion, sizeof(long), 1, Diccionario);

    if (direccion == -1)
    {
        printf("No hay entidades.\n");
        return;
    }

    while (direccion != -1)
    {
        printf("DEBUG: direccion = %ld\n", direccion); // Depuración

        fseek(Diccionario, direccion, SEEK_SET);

        fread(&Entidad.nom, sizeof(char), N, Diccionario);
        fread(&Entidad.listDatos, sizeof(long), 1, Diccionario);
        fread(&Entidad.ListAtrubutos, sizeof(long), 1, Diccionario);
        fread(&Entidad.sig, sizeof(long), 1, Diccionario);

        printf("DEBUG: sig = %ld\n", Entidad.sig); // Depuración

        printf("\n-- %s --\n", Entidad.nom);

        // ... resto del código ...

        if (direccion == Entidad.sig) 
		{
            printf("Error: sig apunta a sí mismo. Rompiendo ciclo.\n");
            break;
        }

        direccion = Entidad.sig;
    }

    printf("\n");
}

Entidades findEntity(FILE *dataDictionary, char entityName[50])
{
	Entidades currentEntity, aux;
	
	rewind(dataDictionary);
	fread(&aux.sig, sizeof(long), 1, dataDictionary);
	fseek(dataDictionary, aux.sig, SEEK_SET);

	fread(&currentEntity.nom, sizeof(char), 50, dataDictionary);
	currentEntity.listDatos = ftell(dataDictionary);
	fread(&aux.listDatos, sizeof(long), 1, dataDictionary);
	currentEntity.ListAtrubutos = ftell(dataDictionary);

	fread(&aux.ListAtrubutos, sizeof(long), 1, dataDictionary);
	currentEntity.sig = ftell(dataDictionary);
	fread(&aux.sig, sizeof(long), 1, dataDictionary);
	
	while (aux.sig != -1 && (strcmp(currentEntity.nom, entityName)) != 0)
	{
		fseek(dataDictionary, aux.sig, SEEK_SET);
		fread(&currentEntity.nom, sizeof(char), 50, dataDictionary);
		currentEntity.listDatos = ftell(dataDictionary);
		fread(&aux.listDatos, sizeof(long), 1, dataDictionary);
		currentEntity.ListAtrubutos = ftell(dataDictionary);
		fread(&aux.ListAtrubutos, sizeof(long), 1, dataDictionary);
		currentEntity.sig = ftell(dataDictionary);
		fread(&aux.sig, sizeof(long), 1, dataDictionary);
	}
	
	if (aux.sig == -1 && (strcmp(currentEntity.nom, entityName)) != 0)
	{
		currentEntity.sig = 0;
	}
	
	return currentEntity;
}

void modificarEntidad(FILE *Diccionario, char nom[50])
{
	rewind(Diccionario);
	long DirEntidad;
	Entidades ptr, nuevaEntidad, aux;
	
	ptr = findEntity(Diccionario, nom);
	if (ptr.sig == 0)
	{
		printf("La entidad no existe...\n");
		return;
	}
	
	elimina(Diccionario, nom);
	
	printf("Nuevo nombre: ");
	scanf("%s", nuevaEntidad.nom);
	fseek(Diccionario, ptr.listDatos, SEEK_SET);
	fread(&nuevaEntidad.listDatos, sizeof(long), 1, Diccionario);
	fread(&nuevaEntidad.ListAtrubutos, sizeof(long), 1, Diccionario);
	nuevaEntidad.sig = vacio; // vacio es -1
	
	aux = findEntity(Diccionario, nuevaEntidad.nom);
	while (aux.sig != 0)
	{
		if (aux.sig != 0)
			printf("Este nombre ya esta en uso!, favor de selecionar otro.\n");
		printf("Nuevo nombre: ");
		scanf("%s", nuevaEntidad.nom);
		aux = findEntity(Diccionario, nuevaEntidad.nom);
	}
	
	DirEntidad = AgregarEntidad(Diccionario, nuevaEntidad);
	
	OrdenarEntidad(Diccionario, 0, nuevaEntidad.nom, DirEntidad);
	printf("Modificado correctamente! \n");
}

void AgregarDato(FILE *Diccionario, long nuevoDato, long LDatos, long LAtributos)
{
	long ListAtributos, sig, fin;
	int datoint;
	bool datobool;
	long datoLong;
	float datofloat;
	char datochar[N];
	
	ATTRIBUTE atributo;
	
	fseek(Diccionario, LDatos, SEEK_SET);
	fread(&sig, sizeof(long), 1, Diccionario);
	
	if (sig == vacio)
	{
		fseek(Diccionario, LDatos, SEEK_SET);
		fwrite(&nuevoDato, sizeof(long), 1, Diccionario);
	}
	else
	{
		while (sig != vacio)
		{
			ListAtributos = LAtributos;
			while (ListAtributos != -1)
			{
				fseek(Diccionario, ListAtributos, SEEK_SET);
				fread(atributo.name, N, 1, Diccionario);
				fread(&atributo.isPrimary, sizeof(bool), 1, Diccionario);
				fread(&atributo.type, sizeof(long), 1, Diccionario);
				fread(&atributo.size, sizeof(long), 1, Diccionario);
				fread(&ListAtributos, sizeof(long), 1, Diccionario);
				
				fseek(Diccionario, sig, SEEK_SET);
				switch (atributo.type)
				{
				case 1:
					fread(&datoint, sizeof(int), 1, Diccionario);
					sig = ftell(Diccionario);
					break;
				case 2:
					fread(&datoLong, sizeof(long), 1, Diccionario);
					sig = ftell(Diccionario);
					break;
				case 3:
					fread(&datofloat, sizeof(float), 1, Diccionario);
					sig = ftell(Diccionario);
					break;
				case 4:
					fread(&datochar, sizeof(char), N, Diccionario);
					sig = ftell(Diccionario);
					break;
				case 5:
					fread(&datobool, sizeof(bool), 1, Diccionario);
					sig = ftell(Diccionario);
					break;
				}
			}
			fin = ftell(Diccionario);
			fread(&sig, sizeof(long), 1, Diccionario);
		}
		fseek(Diccionario, fin, SEEK_SET);
		fwrite(&nuevoDato, sizeof(long), 1, Diccionario);
	}
}

void insertarDatos(FILE *Diccionario, Entidades entidad)
{
	long LDatos, LAtributos, ListAtributos, sig, nuevoDato, pos;
	int datoint;
	bool datobool;
	long datoLong;
	float datofloat;
	char datochar[N];
	
	ATTRIBUTE atributo;
	
	fseek(Diccionario, 0, SEEK_END);
	nuevoDato = ftell(Diccionario);
	printf("pos: %li\n", nuevoDato);
	
	fseek(Diccionario, entidad.listDatos, SEEK_SET);
	fread(&LDatos, sizeof(long), 1, Diccionario);
	fread(&LAtributos, sizeof(long), 1, Diccionario);
	ListAtributos = LAtributos;
	if (ListAtributos == vacio)
	{
		printf("No hay Atributos...\n");
		return;
	}
	
	while (ListAtributos != -1)
	{
		fseek(Diccionario, ListAtributos, SEEK_SET);
		fread(atributo.name, N, 1, Diccionario);
		fread(&atributo.isPrimary, sizeof(bool), 1, Diccionario);
		fread(&atributo.type, sizeof(long), 1, Diccionario);
		fread(&atributo.size, sizeof(long), 1, Diccionario);
		fread(&ListAtributos, sizeof(long), 1, Diccionario);
		
		printf("%s: ", atributo.name);
		switch (atributo.type)
		{
		case 1:
			scanf(" %d", &datoint);
			fseek(Diccionario, 0, SEEK_END);
			fwrite(&datoint, sizeof(int), 1, Diccionario);
			break;
		case 2:
			scanf(" %li", &datoLong);
			fseek(Diccionario, 0, SEEK_END);
			fwrite(&datoLong, sizeof(long), 1, Diccionario);
			break;
		case 3:
			scanf(" %f", &datofloat);
			fseek(Diccionario, 0, SEEK_END);
			fwrite(&datofloat, atributo.size, 1, Diccionario);
			break;
		case 4:
			scanf(" %s", datochar);
			fseek(Diccionario, 0, SEEK_END);
			fwrite(&datochar, sizeof(char), N, Diccionario);
			break;
		case 5:
			do
			{
				printf("\n 1)Verdadero \n 0)Falso \n opcion: ");
				scanf(" %d", &datoint);
			} while (datoint < 0 || datoint > 1);

			datobool = datoint;
			fseek(Diccionario, 0, SEEK_END);
			fwrite(&datobool, sizeof(bool), 1, Diccionario);
			break;
		default:
			printf("Tipo no valido, favor de volver a intentarlo.\n");
			break;
		}
		pos = ftell(Diccionario);
		printf("pos: %li\n", pos);
	}
	sig = vacio;
	fwrite(&sig, sizeof(long), 1, Diccionario);
	AgregarDato(Diccionario, nuevoDato, entidad.listDatos, LAtributos);
}

void EntidadesMenu(char diccionario[N])
{
	FILE *Diccionario = fopen(diccionario, "rb+");
	int ops;
	long DirEntidad;
	char nom[N];
	Entidades nuevaEntidad, entidad;
	
	printf("----------ENTIDADES----------\n");
	printf("1)Imprimir \n2)Nueva Entidad \n3)Eliminar Entidad \n4)Modificar entidad \n5)Seleccionar Entidad \n6)Agregar Datos \n0)salir \nOpcion: ");
	scanf("%d", &ops);
	switch (ops)
	{
	case 1:
		imprimir(Diccionario);
		break;
	case 2:
		printf("Nombre: ");
		scanf("%s", nuevaEntidad.nom);
		nuevaEntidad.sig = vacio;
		nuevaEntidad.listDatos = vacio;
		nuevaEntidad.ListAtrubutos = vacio;
		DirEntidad = AgregarEntidad(Diccionario, nuevaEntidad);
		OrdenarEntidad(Diccionario, 0, nuevaEntidad.nom, DirEntidad);
		
		break;
	case 3:
		printf("Nombre: ");
		scanf("%s", nom);
		if (elimina(Diccionario, nom))
		{
			printf("Eliminado correctamente!\n");
		}
		else
		{
			printf("No fue posible eliminar, favor de volver a intentar\n");
		}
		break;
	case 4:
		printf("Nombre: ");
		scanf("%s", nom);
		modificarEntidad(Diccionario, nom);
		break;
	case 5:
		rewind(Diccionario);
		printf("Nombre de la Entidad: ");
		scanf("%s", nom);
		entidad = findEntity(Diccionario, nom);
		if (entidad.sig == 0)
		{
			printf("No se encontro La entidad!, favor de revisar.\n");
			fclose(Diccionario);
			EntidadesMenu(diccionario);
		}
		fseek(Diccionario, entidad.listDatos, SEEK_SET);
		fread(&DirEntidad, sizeof(long), 1, Diccionario);
		if (DirEntidad != vacio)
		{
			printf("Ya hay datos en esta entidad, no puedes modificar ni agregar mas atributos.\n");
			fclose(Diccionario);
			EntidadesMenu(diccionario);
		}
		printf("Entrando a los Atributos de la Entidad...........\n\n");
		fclose(Diccionario);
		menuAtributos(diccionario, entidad);
		break;
	case 6:
		rewind(Diccionario);
		printf("Nombre de la Entidad a la que se le quiere insertar los datos: ");
		scanf("%s", nom);
		entidad = findEntity(Diccionario, nom);
		if (entidad.sig == 0)
		{
			printf("No se encontro La entidad!, favor de revisar.\n");
			fclose(Diccionario);
			EntidadesMenu(diccionario);
		}
		insertarDatos(Diccionario, entidad);
		break;
	case 0:
		fclose(Diccionario);
		printf("Saliendo del Archivo...................\n\n");
		menu();
		break;
	default:
		printf("Opcion no valida, favor de volver a intentar.\n");
		break;
	}
	fclose(Diccionario);
	EntidadesMenu(diccionario);
}

void menu()
{
	FILE *diccionario;
	int ops;
	long num = vacio;
	char nom[N];
	
	printf("----------MENU----------\n");
	printf("1)Crear Diccionario \n2)Abrir diccionario \n0)salir \nOpcion: ");
	scanf("%d", &ops);
	switch (ops)
	{
	case 1:
		printf("Nombre del diccionario: ");
		scanf("%s", nom);
		if (!(diccionario = fopen(nom, "wb")))
		{
			printf("Archivo no encontrado\n");
			menu();
		}
		else
		{
			long num = vacio;
			fwrite(&num, sizeof(long), 1, diccionario);
		}
		break;
	case 2:
		printf("Nombre del diccionario: ");
		scanf("%s", nom);
		if (!(diccionario = fopen(nom, "rb+")))
		{
			printf("Archivo no encontrado\n");
			menu();
		}
		break;
	case 0:
		printf("Cerrando programa... \n");
		exit(0);
		break;
	default:
		menu();
		break;
	}
	fclose(diccionario);
	printf("Abriendo Archivo.............\n\n");
	EntidadesMenu(nom);
}

int main()
{
	menu();
}

//Codigos recientes

int removeAttribute(FILE *dataDictionary, long currentAttributePointer, char attributeName[])
{
	long currentAttributeDirection = -1;
	fseek(dataDictionary, currentAttributePointer, SEEK_SET);
	fread(&currentAttributeDirection, sizeof(currentAttributeDirection), 1, dataDictionary);

	if(currentAttributeDirection == -1)
	{
		return 0;
	}
	else{
	ATTRIBUTE aux;
	long nextAttributePointer;
	fseek(dataDictionary, currentAttributeDirection, SEEK_SET);
	nextAttributePointer = ftell(dataDictionary) - sizeof(long);

	char currentAttributeName[50];
	fseek(dataDictionary, currentAttributeDirection, SEEK_SET);
	fread(currentAttributeName, sizeof(char), 50, dataDictionary);

	if(strcmp(currentAttributeName, attributeName) == 0)
	{
		fseek(dataDictionary, currentAttributePointer, SEEK_SET);
		fwrite(&aux.nextAtribute, sizeof(long), 1, dataDictionary);
		return 1;
	}
	else
	{
		return removeAttribute(dataDictionary, nextAttributePointer, attributeName);
	}
	}
}

ATTRIBUTE readAttribute(FILE *state, long address)
{
	ATTRIBUTE attribute;
	fseek(state, address, SEEK_SET);
	fread(&attribute, sizeof(ATTRIBUTE), 1, state);
	return attribute;
}

size_t calculateTotalDataSize(Entidades entity, FILE *state)
{
	size_t totalSize = 0;
	ATTRIBUTE attribute;
	long attributePosition = entity.ListAtrubutos;

	while (attributePosition != vacio)
	{
		attribute = readAttribute(state, attributePosition);
		totalSize += attribute.size;
		attributePosition = attribute.nextAtribute;
	}

	return totalSize;
}

int captureDataRecord(Entidades entity, FILE *state, char *dataBuffer)
{
    ATTRIBUTE attribute;
	long attributePosition = entity.ListAtrubutos;
    size_t offset = 0;
	char input[N];
    while (attributePosition != vacio)
    {
		attribute = readAttribute(state, attributePosition);
    }

}