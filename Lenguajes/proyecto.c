// #include "main.h"
// #include "entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define empty -1
#define LENGHT 50

typedef struct entity
{
    char name[LENGHT];
    long listDat;
    long listAttr;
    long sig;
} ENTITIES;

typedef struct atribute
{
    char name[LENGHT];
    bool isPrimary;
    int type;
    int size;
    long nextAttribute;
} ATTRIBUTES;

enum
{
    EXIT,
    NEW_FILE,
    OPEN_FILE
}OPTION;

enum
{
    RETURN,
    PRINT,
    CREATE_ENTITY,
    DELETE_ENTITY,
    MODIFY_ENTITY,
    SELECT_ENTITY
}OPTIONEntity;

enum
{
    RETURN2,
    PRINT2,
    CREATE_ATTRIBUTE,
    DELETE_ATTRIBUTE,
    MODIFY_ATTRIBUTE,
    SELECT_ATTRIBUTE
}OPTIONAttribute;

void printMainMenu();
void processUserSelection();

void printDictionaryMenu(const char *dictionary);
void processInputDictonary(const char *dictionary);
void printDictionary(FILE *dict);
long createEntity(FILE *dict, ENTITIES newEntity);
void orderEntity(FILE *dict, long currentEntity, const char *newNameEntity, long newDirEntity);
int deleteEntity(FILE *dict, char name[LENGHT]);
ENTITIES findEntity(FILE *dict, char entityName[LENGHT]);
void modifyEntity(FILE *dict, char name[LENGHT]);

void printEntityMenu(ENTITIES entity);
void processInputEntity(const char *dict, ENTITIES entity);

int main()
{
    processUserSelection();
    return 0;
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
    char name[LENGHT];

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

void printDictionaryMenu(const char *dictionary)
{
    printf("\n\n\t -------- %s menu-------- \n", dictionary);
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
    int userSelec;
    long dirEntity;
    char name[LENGHT];
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
                scanf("%s", newEntity.name);
                newEntity.listAttr = empty;
                newEntity.listDat = empty;
                newEntity.sig = empty;
                dirEntity = createEntity(dict, newEntity);
                orderEntity(dict, 0, newEntity.name, dirEntity);
                printf("Added to %ld \n", dirEntity);
            break;

            case DELETE_ENTITY:
                /* system("cls"); */
                printf("Name: ");
                scanf("%s", name);
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
                scanf("%s", name);
                modifyEntity(dict, name);
            break;

            case SELECT_ENTITY:
                /* system("cls"); */
                rewind(dict);
                printf("Name of the entity: ");
                scanf("%s", name);
                entity = findEntity(dict, name);

                if (entity.sig == 0)
                {
                    /* system("cls"); */
                    printf("The entity wasn't found \n");
                    fclose(dict);
                    return;
                }

                fseek(dict, entity.listDat, SEEK_SET);
                fread(&dirEntity, sizeof(long), 1, dict);

                if(dirEntity != empty)
                {
                    printf("The entity already has data \n");
                    fclose(dict);
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

            fread(&entity.name, LENGHT, 1, dict);
            fread(&entity.listDat, sizeof(long), 1, dict);
            fread(&entity.listAttr, sizeof(long), 1, dict);
            fread(&dir, sizeof(long), 1, dict);
            printf("\n\t------- %s %ld -------\n", entity.name, dir);

            ATTRIBUTES attri;
            long dir2;
            printf("\t\t------ Attributes ------ \n");
            if(entity.listAttr == empty)
                printf("There is not attributes \n");
            else
            {
                dir2 = entity.listAttr;
                while(dir2 != empty)
                {
                    fseek(dict, dir2, SEEK_SET);

                    fread(&attri.name, LENGHT, 1, dict);
                    fread(&attri.isPrimary, sizeof(bool), 1, dict);
                    fread(&attri.type, sizeof(int), 1, dict);
                    fread(&attri.size, sizeof(int), 1, dict);
                    fread(&attri.nextAttribute, sizeof(long), 1, dict);

                    printf("Attribute: %s | Primary: %d | Type: %d | Size: %d\n", attri.name, attri.isPrimary, attri.type, attri.size);

                    dir2 = attri.nextAttribute;
                }
            }
        }
}

long createEntity(FILE *dict, ENTITIES newEntity)
{
    long dirEntity;
    fseek(dict, 0, SEEK_END);
    dirEntity = ftell(dict);
    fwrite(newEntity.name, LENGHT, 1, dict);
    fwrite(&newEntity.listDat, sizeof(long), 1, dict);
    fwrite(&newEntity.listAttr, sizeof(long), 1, dict);
    fwrite(&newEntity.sig, sizeof(long), 1, dict);
    return dirEntity;
}

void orderEntity(FILE *dict, long currentEntity, const char *newNameEntity, long newDirEntity)
{
    long dirEntity = -1;
    char currentEntityName[LENGHT];
    long nextHeaderPointer;

    fseek(dict, currentEntity, SEEK_SET);
    fread(&dirEntity, sizeof(dirEntity), 1, dict);

    if (dirEntity == -1L)
    {
        fseek(dict, currentEntity, SEEK_SET);
        fwrite(&newDirEntity, sizeof(long), 1, dict);
    }
    else
    {
        fseek(dict, dirEntity, SEEK_SET);
        fread(&currentEntityName, sizeof(char), LENGHT, dict);
        nextHeaderPointer = ftell(dict) + (sizeof(long) * 2);

        if (strcmp(currentEntityName, newNameEntity) < 0)
        {
            
            orderEntity(dict, nextHeaderPointer, newNameEntity, newDirEntity);
        }
        else
        {
            if (strcmp(currentEntityName, newNameEntity) == 0)
            {
                printf("The entity already exists \n");
                return;
            }
            else
            {
                fseek(dict, currentEntity, SEEK_SET);
                fwrite(&newDirEntity, sizeof(long), 1, dict);
                fseek(dict, newDirEntity + LENGHT + (sizeof(long) * 2), SEEK_SET);
                fwrite(&dirEntity, sizeof(long), 1, dict);
            }
        }
    }
}

int deleteEntity(FILE *dict, char name[LENGHT])
{
    ENTITIES enti;
    long ant, ptr, ptrdir;

    rewind(dict);
    if (!dict)
        return 0;

    fread(&ptr, sizeof(long), 1, dict);
    if (ptr == -1)
    {
        return 0; 
    }

    fseek(dict, ptr, SEEK_SET);
    fread(enti.name, LENGHT, 1, dict);
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

    while (ptr != -1 && strcmp(enti.name, name) != 0)
    {
        ant = ptrdir;
        fseek(dict, ptr, SEEK_SET); 
        fread(enti.name, LENGHT, 1, dict);
        fread(&enti.listDat, sizeof(long), 1, dict);
        fread(&enti.listAttr, sizeof(long), 1, dict);
        ptrdir = ftell(dict);
        fread(&ptr, sizeof(long), 1, dict);
    }

    if (ptr == -1 && strcmp(enti.name, name) != 0)
        return 0;

    fseek(dict, ant, SEEK_SET);
    fwrite(&ptr, sizeof(long), 1, dict);

    return 1;
}

ENTITIES findEntity(FILE *dict, char entityName[LENGHT])
{
    ENTITIES currentEntity, aux;
    rewind(dict);

    fread(&aux.sig, sizeof(long), 1, dict);
    fseek(dict, aux.sig, SEEK_SET);
    fread(&currentEntity.name, sizeof(char), LENGHT, dict);
    currentEntity.listDat = ftell(dict);
    fread(&aux.listDat, sizeof(long), 1, dict);
    currentEntity.listAttr = ftell(dict);
    fread(&aux.listAttr, sizeof(long), 1, dict);
    currentEntity.sig = ftell(dict);
    fread(&aux.sig, sizeof(long), 1, dict);

    while (aux.sig != -1 && (strcmp(currentEntity.name, entityName)) != 0)
    {
        fseek(dict, aux.sig, SEEK_SET);
        fread(&currentEntity.name, sizeof(char), LENGHT, dict);
        currentEntity.listDat = ftell(dict);
        fread(&aux.listDat, sizeof(long), 1, dict);
        currentEntity.listAttr = ftell(dict);
        fread(&aux.listAttr, sizeof(long), 1, dict);
        currentEntity.sig = ftell(dict);
        fread(&aux.sig, sizeof(long), 1, dict);
    }

    if (aux.sig == -1 && (strcmp(currentEntity.name, entityName)) != 0)
        currentEntity.sig = 0;

    return currentEntity;
}

void modifyEntity(FILE *dict, char name[LENGHT])
{
    rewind(dict);
    long dirEntity;
    ENTITIES ptr, newEntity, aux;

    ptr = findEntity(dict, name);
    if (ptr.sig == 0)
    {
        printf("The entity doesn't exists\n");
        return;
    }

    deleteEntity(dict, name);

    printf("New name: ");
    scanf("%s", newEntity.name);
    fseek(dict, ptr.listDat, SEEK_SET);
    fread(&newEntity.listDat, sizeof(long), 1, dict);
    fread(&newEntity.listAttr, sizeof(long), 1, dict);
    newEntity.sig = empty;

    aux = findEntity(dict, newEntity.name);
    while (aux.sig != 0)
    {
        if (aux.sig != 0)
            printf("This name is already used in another entity\n");
        printf("New name: ");
        scanf("%s", newEntity.name);
        aux = findEntity(dict, newEntity.name);
    }

    dirEntity = createEntity(dict, newEntity);

    orderEntity(dict, 0, newEntity.name, dirEntity);
    printf("Successfully modified\n");
}

// Parte de atributos

void printEntityMenu(ENTITIES entity)
{
    printf("\t -------- %s menu -------- \n", entity.name);
    printf("--- %d Print data dictionary \n", PRINT2);
    printf("--- %d Create an attribute \n", CREATE_ATTRIBUTE);
    printf("--- %d Delete an attribute \n", DELETE_ATTRIBUTE);
    printf("--- %d Modify an attribute \n", MODIFY_ATTRIBUTE);
    printf("--- %d Select an attribute \n", SELECT_ATTRIBUTE);
    printf("--- %d Exit \n", RETURN2);
}

void processInputEntity(const char *dict, ENTITIES entity)
{
    FILE *dictionary = fopen(dict, "rb+");
    int userSelec;
    //char name[LENGHT];
    do{
        printEntityMenu(entity);
        scanf("%d", &userSelec);
        switch(userSelec)
        {
            case PRINT2:
            break;
            case CREATE_ATTRIBUTE:
            break;
            case DELETE_ATTRIBUTE:
            break;
            case MODIFY_ATTRIBUTE:
            break;
            case SELECT_ATTRIBUTE:
            break;
            case RETURN2:
                printf("Back to the dictionary menu \n");
            break;
            default:
                printf("Wrong option \n");
            break;
        }
    } while(userSelec != RETURN2);
    fclose(dictionary);
}
