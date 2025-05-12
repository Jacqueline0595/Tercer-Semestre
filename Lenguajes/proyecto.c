// #include "main.h"
// #include "entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define empty -1
#define LENGTH 50

typedef struct entity
{
    char name[LENGTH];
    long listDat;
    long listAttr;
    long sig;
} ENTITIES;

typedef struct attribute
{
    char name[LENGTH];
    int isPrimary;
    int type;
    int size;
    int next;
} ATTRIBUTES;

// type:{0:Bite, 1:Integer, 2:Float, 3:Char, 4:String}
// Size: *Bit=1, *Integer=4, *Float=8, *Char=1, String=? (Ask)

enum MenuOption 
{ 
    EXIT, 
    NEW_FILE, 
    OPEN_FILE 
};

enum EntityOption 
{ 
    RETURN, 
    PRINT, 
    CREATE_ENTITY, 
    DELETE_ENTITY, 
    MODIFY_ENTITY, 
    SELECT_ENTITY 
};

enum AttributeOption 
{ 
    RETURN2, 
    PRINT2, 
    CREATE_ATTRIBUTE, 
    DELETE_ATTRIBUTE, 
    MODIFY_ATTRIBUTE, 
    DATA_ATTRIBUTE 
};

void toUpperCase(char *strin);

// ----- Main Menu -----
void printMainMenu();
void processUserSelection();

// ----- Entity Menu -----

void printDictionaryMenu(const char *dictionary);
void processInputDictonary(const char *dictionary);
void printDictionary(FILE *dict);
long createEntity(FILE *dict, ENTITIES newEntity);
void orderEntity(FILE *dict, ENTITIES newEntity, long newDirEntity);
int deleteEntity(FILE *dict, char name[LENGTH]);
ENTITIES findEntity(FILE *dict, char entityName[LENGTH]);
void modifyEntity(FILE *dict, char name[LENGTH]);

// ----- Attribute Menu -----

void printEntityMenu(ENTITIES entity);
void processInputEntity(const char *dict, ENTITIES entity);
/* void printAttributes(FILE *dict, long listA);
long appendAttribute(FILE *dict, ATTRIBUTES newAttribute);
int reassingAttribute(FILE *dict, long currenPointer, ATTRIBUTES attribute, long newAttrDir);
int removeAtribute(FILE *dict, long currentPointer, char attributeName[LENGTH]); */

// ----- Main Menu -----

int main()
{
    processUserSelection();
    return 0;
}

void toUpperCase(char *strin)
{
    int length = strlen(strin);
    for (int i = 0; i < length; i++)
    {
        strin[i] = toupper((unsigned char)strin[i]);
    }
}

void printMainMenu()
{
    printf("\t ---------Main menu--------- \n");
    printf("--- %d Create new file \n", NEW_FILE);
    printf("--- %d Open existing file \n", OPEN_FILE);
    printf("--- %d Exit \n", EXIT);
}

void processUserSelection()
{
    FILE *dictionary;
    int userSelection;
    long num = empty;
    char name[LENGTH];

    do 
    {
        printMainMenu();
        scanf("%d", &userSelection);

        switch(userSelection)
        {
            case NEW_FILE:
                printf("Name of the dictionary: ");
                scanf("%s", name);

                dictionary = fopen(name, "wb+");
                if (!dictionary)
                {
                    /* system("cls"); */
                    printf("Couldn't create the file.\n");
                    break;
                }

                fwrite(&num, sizeof(long), 1, dictionary);
                fclose(dictionary);
                printf("We're going to the file...\n\n");
                processInputDictonary(name);
            break;

            case OPEN_FILE:
                printf("Name of the dictionary: ");
                scanf("%s", name);

                dictionary = fopen(name, "rb+");
                if (!dictionary)
                {
                    /* system("cls"); */
                    printf("File not found.\n");
                    break;
                }

                fclose(dictionary);
                printf("We're going to the file...\n\n");
                processInputDictonary(name);
            break;

            case EXIT:
                printf("Ending program, see u later \n");
                exit(0);
            break;

            default:
                /* system("cls"); */
                printf("Wrong option. Try again.\n");
            break;
        }

    } while(userSelection != EXIT);
}

// ----- Entity Menu -----

void printDictionaryMenu(const char *dictionary)
{
    printf("\n\n\t -------- %s menu -------- \n", dictionary);
    printf("--- %d Print data dictionary \n", PRINT);
    printf("--- %d Create an entity \n", CREATE_ENTITY);
    printf("--- %d Delete an entity \n", DELETE_ENTITY);
    printf("--- %d Modify an entity \n", MODIFY_ENTITY);
    printf("--- %d Select an entity \n", SELECT_ENTITY);
    printf("--- %d Exit \n", RETURN);
}

void processInputDictonary(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "rb+");
    if(!dict)
    {
        printf("Error opening the file.\n");
        return;
    }
    int userSelec;
    long dirEntity;
    char name[LENGTH];
    ENTITIES newEntity, entity;

    do
    {
        printDictionaryMenu(dictionary);
        scanf("%d", &userSelec);
        switch(userSelec)
        {
            case PRINT:
                /* system("cls"); */
                printDictionary(dict);
            break;

            case CREATE_ENTITY:
                /* system("cls"); */
                printf("Name: ");
                scanf("%49s", newEntity.name);
                toUpperCase(newEntity.name);
                newEntity.listAttr = empty;
                newEntity.listDat = empty;
                newEntity.sig = empty;
                dirEntity = createEntity(dict, newEntity);
                orderEntity(dict, newEntity, dirEntity);
                printf("Added to %ld \n", newEntity.sig);
            break;

            case DELETE_ENTITY:
                /* system("cls"); */
                printf("Name: ");
                scanf("%49s", name);
                toUpperCase(name);
                if(deleteEntity(dict, name))
                    printf("Removed successfully \n");
                else
                {
                    /* system("cls"); */
                    printf("Couldn't be deleted");
                }
            break;

            case MODIFY_ENTITY:
                /* system("cls"); */
                printf("Name: ");
                scanf("%49s", name);
                toUpperCase(name);
                modifyEntity(dict, name);
            break;

            case SELECT_ENTITY:
                /* system("cls"); */
                rewind(dict);
                printf("Name of the entity: ");
                scanf("%49s", name);
                toUpperCase(name);

                entity = findEntity(dict, name);

                if (strcmp(entity.name, name) != 0)
                {
                    printf("The entity wasn't found \n");
                    break; 
                }

                if (entity.listDat != empty)
                {
                    printf("The entity already has data \n");
                    break;
                }

                printf("Entering the entity attributes \n");
                processInputEntity(dictionary, entity);
            break;

            case RETURN:
                fclose(dict);
                printf("Back to the main menu \n");
                processUserSelection();
            break;

            default:
                /* system("cls"); */
                printf("Wrong option \n");
            break;
        }
    } while (userSelec != RETURN);
    
    fclose(dict);
}

void printDictionary(FILE *dict)
{
    ENTITIES entity;
    long dir;

    rewind(dict);
    fread(&dir, sizeof(long), 1, dict);
    if(dir == empty)
        printf("Dictionary empty... \n\n");
    else
        while(dir != empty)
        {
            fseek(dict, dir, SEEK_SET);

            fread(&entity, sizeof(ENTITIES), 1, dict);

            printf("\n------- %s %ld -------\n", entity.name, entity.sig);
            printf("| %ld | %ld | \n", entity.listDat, entity.listAttr);

            dir = entity.sig;

            ATTRIBUTES attri;
            long dir2;

            printf("\t------ Attributes ------ \n");
            if(entity.listAttr == empty)
                printf("\tThere is not attributes \n");
            else
            {
                dir2 = entity.listAttr;
                while(dir2 != empty)
                {
                    fseek(dict, dir2, SEEK_SET);

                    fread(&attri.name, LENGTH, 1, dict);
                    fread(&attri.isPrimary, sizeof(int), 1, dict);
                    fread(&attri.type, sizeof(int), 1, dict);
                    fread(&attri.size, sizeof(int), 1, dict);
                    fread(&attri.next, sizeof(long), 1, dict);

                    printf("\tAttribute: %s | Primary: %d | Type: %d | Size: %d \n", attri.name, attri.isPrimary, attri.type, attri.size);

                    dir2 = attri.next;
                }
            }
        }
}

long createEntity(FILE *dict, ENTITIES newEntity)
{
    long dirEntity;

    fseek(dict, 0, SEEK_END);
    dirEntity = ftell(dict);

    if (newEntity.listAttr != empty)
        newEntity.listAttr = empty;
    if (newEntity.listDat != empty)
        newEntity.listDat = empty;
    
    newEntity.sig = empty;

    fwrite(&newEntity, sizeof(ENTITIES), 1, dict);

    return dirEntity;
}

void orderEntity(FILE *dict, ENTITIES newEntity, long newDirEntity)
{
    ENTITIES tempEntity;
    long prevDir = empty;
    long currentDir;

    fseek(dict, 0, SEEK_SET);
    fread(&currentDir, sizeof(long), 1, dict);

    while (currentDir != empty) {
        fseek(dict, currentDir, SEEK_SET);
        fread(&tempEntity, sizeof(ENTITIES), 1, dict);

        if (strcmp(newEntity.name, tempEntity.name) < 0) {
            break;
        }

        prevDir = currentDir;
        currentDir = tempEntity.sig;
    }

    newEntity.sig = currentDir;

    fseek(dict, newDirEntity, SEEK_SET);
    fwrite(&newEntity, sizeof(ENTITIES), 1, dict);

    if(prevDir == empty) 
    {
        fseek(dict, 0, SEEK_SET);
        fwrite(&newDirEntity, sizeof(long), 1, dict);
    } else 
    {
        fseek(dict, prevDir, SEEK_SET);
        fread(&tempEntity, sizeof(ENTITIES), 1, dict);

        tempEntity.sig = newDirEntity;

        fseek(dict, prevDir, SEEK_SET);
        fwrite(&tempEntity, sizeof(ENTITIES), 1, dict);
    }
}

int deleteEntity(FILE *dict, char name[LENGTH])
{
    ENTITIES enti;
    long ant, ptr, ptrdir;

    rewind(dict);
    if (!dict)
        return 0;

    fread(&ptr, sizeof(long), 1, dict);
    if (ptr == empty)
    {
        return 0; 
    }

    fseek(dict, ptr, SEEK_SET);
    fread(enti.name, LENGTH, 1, dict);
    fread(&enti.listDat, sizeof(long), 1, dict);
    fread(&enti.listAttr, sizeof(long), 1, dict);
    ptrdir = ftell(dict); 
    fread(&ptr, sizeof(long), 1, dict);

    if (strcmp(enti.name, name) == 0)
    {

        rewind(dict);
        fwrite(&ptr, sizeof(long), 1, dict);

        return 1;
    }

    while (ptr != empty && strcmp(enti.name, name) != 0)
    {
        ant = ptrdir;
        fseek(dict, ptr, SEEK_SET); 
        fread(enti.name, LENGTH, 1, dict);
        fread(&enti.listDat, sizeof(long), 1, dict);
        fread(&enti.listAttr, sizeof(long), 1, dict);
        ptrdir = ftell(dict);
        fread(&ptr, sizeof(long), 1, dict);
    }

    if (ptr == empty && strcmp(enti.name, name) != 0)
        return 0;

    fseek(dict, ant, SEEK_SET);
    fwrite(&ptr, sizeof(long), 1, dict);

    return 1;
}

ENTITIES findEntity(FILE *dict, char entityName[LENGTH])
{
    ENTITIES entity;
    long dir;

    rewind(dict);
    fread(&dir, sizeof(long), 1, dict);

    while(dir != empty)
    {
        fseek(dict, dir, SEEK_SET);

        fread(&entity.name, LENGTH, 1, dict);
        fread(&entity.listDat, sizeof(long), 1, dict);
        fread(&entity.listAttr, sizeof(long), 1, dict);
        fread(&entity.sig, sizeof(long), 1, dict);

        if(strcmp(entity.name, entityName) == 0)
        {
            return entity;
        }

        dir = entity.sig;
    }

    entity.sig = 0;
    return entity;
}

void modifyEntity(FILE *dict, char name[LENGTH])
{
    rewind(dict);
    long dirEntity;
    ENTITIES ptr, newEntity, aux;

    ptr = findEntity(dict, name);
    if (ptr.sig == 0)
    {
        printf("The entity doesn't exist\n");
        return;
    }

    deleteEntity(dict, name);

    printf("New name: ");
    scanf("%49s", newEntity.name);
    toUpperCase(newEntity.name);

    newEntity.listDat = ptr.listDat;
    newEntity.listAttr = ptr.listAttr;
    newEntity.sig = empty;

    aux = findEntity(dict, newEntity.name);
    while(aux.sig != 0)
    {
        if(aux.sig != 0)
            printf("This name is already used in another entity\n");
        printf("New name: ");
        scanf("%49s", newEntity.name);
        toUpperCase(newEntity.name);
        aux = findEntity(dict, newEntity.name);
    }

    dirEntity = createEntity(dict, newEntity);
    orderEntity(dict, newEntity, dirEntity);
    printf("Successfully modified\n");
}

// Parte de atributos
/*
    - Solo puede existir un atributo primario por entidad
    - No pueden exixtir dos (o más) veces el mismo nombre de atributo en una entidad
    - AL momento de agregar datos, estos se ordenan por clave primaria
    - Una vez que existen datos, LA ENTIDAD NO SE MODIFICA
    - Poner todo en mayusculas
*/

void printEntityMenu(ENTITIES entity)
{
    printf("\t -------- %s menu -------- \n", entity.name);
    printf("--- %d Print attributes \n", PRINT2);
    printf("--- %d Create an attribute \n", CREATE_ATTRIBUTE);
    printf("--- %d Delete an attribute \n", DELETE_ATTRIBUTE);
    printf("--- %d Modify an attribute \n", MODIFY_ATTRIBUTE);
    printf("--- %d Add data to the entity \n", DATA_ATTRIBUTE);
    printf("--- %d Exit \n", RETURN2);
}

void processInputEntity(const char *dict, ENTITIES entity)
{
    FILE *dictionary = fopen(dict, "rb+");
    int userSelec;
    //char name[LENGTH];
    do{
        printEntityMenu(entity);
        scanf("%d", &userSelec);
        switch(userSelec)
        {
            case PRINT2:
                // printAttributes(dictionary, entity.listAttr);
            break;
            case CREATE_ATTRIBUTE:
            break;
            case DELETE_ATTRIBUTE:
            break;
            case MODIFY_ATTRIBUTE:
            break;
            case DATA_ATTRIBUTE:
            break;
            case RETURN2:
                printf("Back to the %s menu \n", dict);
            break;
            default:
                printf("Wrong option \n");
            break;
        }
    } while(userSelec != RETURN2);
    fclose(dictionary);
}

/* void printAttributes(FILE *dict, long listA)
{
    ATTRIBUTES attri;
    long dir;

    fseek(dict, listA, SEEK_SET);
    dir = listA;
    if (dir == empty || listA == empty)
        printf("\tThere aren't attibutes\n");
    else
        while (dir != empty)
        {
            fseek(dict, dir, SEEK_SET);

            fread(&attri.name, LENGTH, 1, dict);
            fread(&attri.isPrimary, sizeof(int), 1, dict);
            fread(&attri.type, sizeof(int), 1, dict);
            fread(&attri.size, sizeof(int), 1, dict);
            fread(&dir, sizeof(long), 1, dict);
            printf("\tAttribute: %s | Primary: %d | Type: %d | Size: %d \n", attri.name, attri.isPrimary, attri.type, attri.size);
        }
}

long appendAttribute(FILE *dict, ATTRIBUTES newAttribute)
{
    long position = 0L;
    const long nullPointer = -1L;
    fseek(dict, 0, SEEK_END);
    position = ftell(dict);

    fwrite(newAttribute.name, sizeof(char), LENGTH, dict);
    fwrite(&newAttribute.isPrimary, sizeof(int), 1, dict);
    fwrite(&newAttribute.type, sizeof(int), 1, dict);
    fwrite(&newAttribute.size, sizeof(int), 1, dict);
    fwrite(&nullPointer, sizeof(long), 1, dict);

    return position;
}

int reassingAttribute(FILE *dict, long currenPointer, ATTRIBUTES attribute, long newAttrDir)
{
    long attrDirection = -1L;
    fseek(dict, currenPointer, SEEK_SET);
    fread(&attrDirection, sizeof(long), 1, dict);
    if(attrDirection == empty)
    {
        fseek(dict, currenPointer, SEEK_SET);
        fwrite(&newAttrDir, sizeof(long), 1, dict);
    }
    else{
        ATTRIBUTES aux;
        fseek(dict, attrDirection, SEEK_SET);
        fread(&aux, sizeof(ATTRIBUTES), 1, dict);
        if(strcmp(aux.name, attribute.name) == 0)
            return 0;
        if(strcmp(aux.name, attribute.name) < 0)
        {
            long nextAttibutePtr = ftell(dict) - sizeof(long);
            reassingAtribute(dict, nextAttibutePtr, attribute, newAttrDir);
        }
        else
        {
            fseek(dict, currenPointer, SEEK_SET);
            fwrite(&newAttrDir, sizeof(long), 1, dict);
            fseek(dict, newAttrDir + sizeof(ATTRIBUTES) - sizeof(long), SEEK_SET);
            fwrite(&attrDirection, sizeof(long), 1, dict);
            return 1;
        }
    }
}

void CreateAttribute(FILE *dict, ENTITIES currentEntity)
{
    ATTRIBUTES newAttribute;
    int size;

    printf("Name of the new attribute: \n");
    scanf("%49s", &newAttribute.name);
    printf("Is it a primary key? \n");
    scanf("%d", &newAttribute.isPrimary);
    printf("Type of attribute? \n\t1)Bite \t2)Integer \t3)Float \t4)Char \t5)String");
    scanf("%d", &newAttribute.type);

    switch(newAttribute.type)
    {
        case 1:
            newAttribute.size = 1;
        break;

        case 2:
            newAttribute.size = sizeof(int);
        break;

        case 3:
            newAttribute.size = sizeof(float);
        break;

        case 4:
            newAttribute.size = sizeof(char);
        break;

        case 5:
            printf("What size do you want? \n");
            scanf("%d", &size);
            newAttribute.size = sizeof(char) * size;
        break;
    }

    newAttribute.next = empty;

    long attributeDir = appendAttribute(dict, newAttribute);
    reassingAttribute(dict, currentEntity.listAttr, attributeDir, newAttribute);
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


int removeAtribute(FILE *dict, long currentPointer, char attributeName[LENGTH])
{
    long attrDirection = empty;

    fseek(dict, currentPointer, SEEK_SET);
    fread(&currentPointer, sizeof(attrDirection), 1, dict);

    if(attrDirection == empty)
    {
        return 0;
    }
    else
    {
        ATTRIBUTES aux;
        long nextAttribute;

        fseek(dict, attrDirection, SEEK_SET);
        fread(&aux, sizeof(ATTRIBUTES), 1, dict);
        nextAttribute = ftell(dict) - sizeof(long);

        if(strcmp(aux.name, attributeName) == 0) 
        {
            fseek(dict, attrDirection, SEEK_SET);
            fwrite(&aux.next, sizeof(long), 1, dict);
            return 1;
        }
        else
        {
            return removeAtribute(dict, nextAttribute, attributeName);
        }
    }
}

ATTRIBUTES readAttribute(FILE *dict, long addres)
{
    ATTRIBUTES attribute;
    fseek(dict, addres, SEEK_SET);
    fread(&attribute, sizeof(ATTRIBUTES), 1, dict);
    return attribute;
}

size_t calculateTotalDataSize(FILE *dict, ENTITIES entity)
{
    size_t totalSize = 0;
    ATTRIBUTES attribute;
    long attributePos = entity.listAttr;

    while(attributePos != empty)
    {
        attribute = readAttribute(dict, attributePos);
        totalSize += attribute.size;
        attributePos = attribute.next;
    }
    return totalSize;
}

int captureDataRecord(FILE *dict, ENTITIES entity, char *dataBuffer)
{
    ATTRIBUTES attribute;
    long attributePos = entity.listAttr;
    size_t offset = 0;
    char input[LENGTH];

    while(attributePos != empty)
    {
        attribute = readAttribute(dict, attributePos);
        
        printf("Input attribute \n");
        scanf("%49s", input);

        if(attribute.isPrimary)
            if()
    }
} */