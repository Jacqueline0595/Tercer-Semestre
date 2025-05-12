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

void toUpperCase(char *strin);

// ------ Principal functions ------

void printMainMenu();
void processUserSelection();
void executeMenuOption(int userSel);
void createNewFile(FILE *dictionary, char *name);
void openFile(char *name);

// ------ Entity functions ------

void printDictionaryMenu(char *dictionary);
void processInputDictionary(char *dictionary);
void executeDictionaryOption(int userSelec, char *dictionary);
void printDictionary(char *dictionaryName);
void createEntity(char *dictionaryName);
void orderEntity(char *dictionaryName);
long findEntity(FILE *dictionary, const char *entityName, ENTITIES *foundEntity);
void deleteEntity(char *dictionaryName);
void modifyEntity(char *dictionaryName);
void selectEntity(char *dictionaryName);

// ------ Attributes functions ------

void printEntityMenu(ENTITIES entity);
void processInputEntity(char *dict, ENTITIES entity);
// void executeEntityOption(int userSelec, FILE *dictionary, ENTITIES entity);
void executeEntityOption(int userSelec, ENTITIES entity);

enum MenuOption 
{ 
    EXIT, 
    NEW_FILE, 
    OPEN_FILE 
};

enum EntityOp
{ 
    RETURN, 
    PRINT, 
    CREATE_ENTITY, 
    DELETE_ENTITY, 
    MODIFY_ENTITY, 
    SELECT_ENTITY 
};

enum AttributeOp
{ 
    RETURN2, 
    PRINT2, 
    CREATE_ATTRIBUTE, 
    DELETE_ATTRIBUTE, 
    MODIFY_ATTRIBUTE, 
    ADD_DATA_ATTRIBUTE,
    MODIFY_DATA_ATTRIBUTE,
    DELETE_DATA_ATTRIBUTE
};

int main()
{
    processUserSelection();
    return 0;
}

// ------ Other functions ------

void toUpperCase(char *strin)
{
    int length = strlen(strin);
    for(int i = 0; i < length; i++)
    {
        strin[i] = toupper((unsigned char)strin[i]);
    }
}

// ------ Main menu ------

void printMainMenu()
{
    printf("\t ---------Main menu--------- \n");
    printf("--- %d Create new file \n", NEW_FILE);
    printf("--- %d Open existing file \n", OPEN_FILE);
    printf("--- %d Exit \n", EXIT);
}

void processUserSelection()
{
    int userSel;

    do 
    {
        printMainMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &userSel) != 1 || userSel < EXIT || userSel > OPEN_FILE)
        {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        executeMenuOption(userSel);

    } while (userSel != EXIT);
}

void executeMenuOption(int userSel)
{
    FILE *dictionary = NULL;
    char name[LENGTH];

    switch(userSel)
    {
        case NEW_FILE:
            createNewFile(dictionary, name);
        break;

        case OPEN_FILE:
            openFile(name);
        break;

        case EXIT:
            printf("Exiting the program. See you later!\n");
        break;

        default:
            printf("Invalid option. Please try again.\n");
        break;
    }
}

void createNewFile(FILE *dictionary, char *name)
{
    printf("Enter the name of the new dictionary: ");
    scanf("%s", name);

    dictionary = fopen(name, "wb+");
    if (!dictionary)
    {
        printf("Error: Could not create the file.\n");
        return;
    }

    long num = empty;
    fwrite(&num, sizeof(long), 1, dictionary);
    fclose(dictionary);
    printf("File created successfully. Opening the file...\n\n");
    processInputDictionary(name);
}

void openFile(char *name)
{
    printf("Enter the name of the dictionary to open: ");
    scanf("%s", name);

    FILE *dictionary = fopen(name, "rb+");
    if (!dictionary)
    {
        printf("Error: File '%s' not found or could not be opened.\n", name);
        return;
    }

    long firstValue;
    if (fread(&firstValue, sizeof(long), 1, dictionary) != 1)
    {
        printf("Error: The file '%s' is not a valid dictionary file.\n", name);
        fclose(dictionary);
        return;
    }

    fclose(dictionary);
    printf("File '%s' opened successfully. Opening the file...\n\n", name);
    processInputDictionary(name);
}

// ------ Entity functions ------

void printDictionaryMenu(char *dictionary)
{
    printf("\n\n\t -------- %s menu -------- \n", dictionary);
    printf("--- %d Print data dictionary \n", PRINT);
    printf("--- %d Create an entity \n", CREATE_ENTITY);
    printf("--- %d Delete an entity \n", DELETE_ENTITY);
    printf("--- %d Modify an entity \n", MODIFY_ENTITY);
    printf("--- %d Select an entity \n", SELECT_ENTITY);
    printf("--- %d Exit \n", RETURN);
}

void processInputDictionary(char *dictionary)
{
    int userSelec;

    if(dictionary == NULL || strlen(dictionary) == 0)
    {
        printf("Error: Invalid dictionary name.\n");
        return;
    }

    FILE *dictiona = fopen(dictionary, "rb+");
    if(!dictiona)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionary);
        return;
    }

    do
    {
        printDictionaryMenu(dictionary);
        printf("Enter your choice: ");
        if(scanf("%d", &userSelec) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if(userSelec < RETURN || userSelec > SELECT_ENTITY)
        {
            printf("Invalid option. Please select a valid menu option.\n");
            continue;
        }
        executeDictionaryOption(userSelec, dictionary);
    } while(userSelec != RETURN);

    fclose(dictiona);
}

void executeDictionaryOption(int userSelec, char *dictionary)
{
    switch(userSelec)
    {
        case PRINT:
            printf("Printing data dictionary...\n");
            printDictionary(dictionary);
        break;

        case CREATE_ENTITY:
            printf("Creating a new entity...\n");
            createEntity(dictionary);
        break;

        case DELETE_ENTITY:
            printf("Deleting an entity...\n");
            deleteEntity(dictionary);
        break;

        case MODIFY_ENTITY:
            printf("Modifying an entity...\n");
            modifyEntity(dictionary);
        break;

        case SELECT_ENTITY:
            printf("Selecting an entity...\n");
            selectEntity(dictionary);
        break;

        case RETURN:
            printf("Returning to the main menu...\n");
        break;

        default:
            printf("Invalid option. Please try again.\n");
        break;
    }
}

void printDictionary(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb");
    if(!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ENTITIES entity;
    printf("\n------- Data Dictionary: %s -------\n", dictionaryName);
    printf("| %-20s | %-10s | %-10s | %-10s |\n", "Entity Name", "List Data", "List Attr", "Next");

    while(fread(&entity, sizeof(ENTITIES), 1, dictionary) == 1)
    {
        printf("| %-20s | %-10ld | %-10ld | %-10ld |\n", entity.name, entity.listDat, entity.listAttr, entity.sig);
    }

    fclose(dictionary);
    printf("\n--- End of Dictionary ---\n");
}

void createEntity(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ENTITIES newEntity;
    printf("Enter the name of the new entity: ");
    scanf("%s", newEntity.name);
    toUpperCase(newEntity.name);

    newEntity.listDat = empty;
    newEntity.listAttr = empty;
    newEntity.sig = empty;

    fseek(dictionary, 0, SEEK_END);

    if (fwrite(&newEntity, sizeof(ENTITIES), 1, dictionary) != 1)
    {
        printf("Error: Could not write the new entity to the file.\n");
        fclose(dictionary);
        return;
    }

    printf("Entity '%s' created successfully.\n", newEntity.name);
    fclose(dictionary);

    orderEntity(dictionaryName);
}

void orderEntity(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ENTITIES entities[100];
    int count = 0;

    while (fread(&entities[count], sizeof(ENTITIES), 1, dictionary) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        printf("No entities found to order.\n");
        fclose(dictionary);
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(entities[i].name, entities[j].name) > 0)
            {
                ENTITIES temp = entities[i];
                entities[i] = entities[j];
                entities[j] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        if (i == count - 1)
        {
            entities[i].sig = empty;
        }
        else
        {
            entities[i].sig = (i + 1) * sizeof(ENTITIES);
        }
    }

    rewind(dictionary);
    if (fwrite(entities, sizeof(ENTITIES), count, dictionary) != (size_t)count)
    {
        printf("Error: Could not write the ordered entities to the file.\n");
        fclose(dictionary);
        return;
    }

    printf("Entities ordered successfully.\n");
    fclose(dictionary);
}

long findEntity(FILE *dictionary, const char *entityName, ENTITIES *foundEntity)
{
    ENTITIES entity;
    long position = 0;

    rewind(dictionary); // Asegurarse de empezar desde el inicio del archivo

    while (fread(&entity, sizeof(ENTITIES), 1, dictionary) == 1)
    {
        char entityNameUpper[LENGTH];
        strcpy(entityNameUpper, entity.name);
        toUpperCase(entityNameUpper); // Convertir el nombre leído a mayúsculas

        char searchNameUpper[LENGTH];
        strcpy(searchNameUpper, entityName);
        toUpperCase(searchNameUpper); // Convertir el nombre buscado a mayúsculas

        if (strcmp(entityNameUpper, searchNameUpper) == 0)
        {
            if (foundEntity != NULL)
            {
                *foundEntity = entity; // Copiar la entidad encontrada
            }
            return ftell(dictionary) - sizeof(ENTITIES); // Retornar la posición exacta en bytes
        }
        position++;
    }

    return -1; // Retornar -1 si no se encuentra la entidad
}

void deleteEntity(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    char entityName[LENGTH];
    printf("Enter the name of the entity to delete: ");
    scanf("%s", entityName);
    toUpperCase(entityName);

    ENTITIES entityToDelete;
    long positionToDelete = findEntity(dictionary, entityName, &entityToDelete);

    if (positionToDelete == -1)
    {
        printf("Error: Entity '%s' not found.\n", entityName);
        fclose(dictionary);
        return;
    }

    ENTITIES entities[100];
    int count = 0;

    rewind(dictionary);
    while (fread(&entities[count], sizeof(ENTITIES), 1, dictionary) == 1)
    {
        count++;
    }

    for (int i = 0; i < count; i++)
    {
        if (i == positionToDelete / sizeof(ENTITIES))
        {
            continue;
        }

        if (entities[i].sig == positionToDelete)
        {
            entities[i].sig = entityToDelete.sig;
        }
    }

    rewind(dictionary);
    for (int i = 0; i < count; i++)
    {
        if (i != positionToDelete / sizeof(ENTITIES))
        {
            fwrite(&entities[i], sizeof(ENTITIES), 1, dictionary);
        }
    }

    fclose(dictionary);

    orderEntity(dictionaryName);

    printf("Entity '%s' deleted and dictionary reordered successfully.\n", entityName);
}

void modifyEntity(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    char currentName[LENGTH];
    printf("Enter the name of the entity to modify: ");
    scanf("%s", currentName);
    toUpperCase(currentName);

    ENTITIES entityToModify;
    long positionToModify = findEntity(dictionary, currentName, &entityToModify);

    if (positionToModify == -1)
    {
        printf("Error: Entity '%s' not found.\n", currentName);
        fclose(dictionary);
        return;
    }

    char newName[LENGTH];
    ENTITIES existingEntity;

    do
    {
        printf("Enter the new name for the entity: ");
        scanf("%s", newName);
        toUpperCase(newName);

        if (strcmp(currentName, newName) == 0)
        {
            printf("The new name is the same as the current name. Try again.\n");
            continue;
        }

        long existingPosition = findEntity(dictionary, newName, &existingEntity);
        if (existingPosition != -1)
        {
            printf("The name '%s' is already used by another entity. Try again.\n", newName);
        }
        else
        {
            break;
        }
    } while (1);

    strcpy(entityToModify.name, newName);

    fseek(dictionary, positionToModify, SEEK_SET);
    if (fwrite(&entityToModify, sizeof(ENTITIES), 1, dictionary) != 1)
    {
        printf("Error: Could not update the entity in the file.\n");
        fclose(dictionary);
        return;
    }

    orderEntity(dictionaryName);

    printf("Entity '%s' successfully modified to '%s'.\n", currentName, newName);
    fclose(dictionary);
}

void selectEntity(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    char entityName[LENGTH];
    printf("Enter the name of the entity to select: ");
    scanf("%s", entityName);
    toUpperCase(entityName);

    ENTITIES selectedEntity;
    long position = findEntity(dictionary, entityName, &selectedEntity);

    if (position == -1)
    {
        printf("Error: Entity '%s' not found.\n", entityName);
        fclose(dictionary);
        return;
    }

    printf("Entity '%s' selected successfully.\n", selectedEntity.name);

    processInputEntity(dictionaryName, selectedEntity);

    fclose(dictionary);
}

// ------ Attributes functions ------

void printEntityMenu(ENTITIES entity)
{
    printf("\n\n\t -------- %s's menu -------- \n", entity.name);
    printf("--- %d Print attributes \n", PRINT2);
    printf("--- %d Create an attribute \n", CREATE_ATTRIBUTE);
    printf("--- %d Delete an attribute \n", DELETE_ATTRIBUTE);
    printf("--- %d Modify an attribute \n", MODIFY_ATTRIBUTE);
    printf("--- %d Add data to the entity \n", ADD_DATA_ATTRIBUTE);
    printf("--- %d Modify data to the entity \n", MODIFY_DATA_ATTRIBUTE);
    printf("--- %d Delete data to the entity \n", DELETE_DATA_ATTRIBUTE);
    printf("--- %d Exit \n", RETURN2);
}

void processInputEntity(char *dict, ENTITIES entity)
{
    FILE *dictionary = fopen(dict, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dict);
        return;
    }

    int userSelec;

    do
    {
        printEntityMenu(entity);
        printf("Enter your choice: ");
        scanf("%d", &userSelec);

        if(userSelec < RETURN2 || userSelec > DELETE_DATA_ATTRIBUTE)
        {
            printf("Invalid option. Please try again.\n");
            continue;
        }

        // executeEntityOption(userSelec, dictionary, entity);
        executeEntityOption(userSelec, entity);


    } while (userSelec != RETURN2);

    fclose(dictionary);
}

/* void executeEntityOption(int userSelec, FILE *dictionary, ENTITIES entity) */
void executeEntityOption(int userSelec, ENTITIES entity)
{
    switch (userSelec)
    {
        case PRINT2:
            printf("Printing attributes of entity '%s'...\n", entity.name);
            // Implementar printAttributes
            break;

        case CREATE_ATTRIBUTE:
            printf("Creating a new attribute for entity '%s'...\n", entity.name);
            // Implementar createAttribute
            break;

        case DELETE_ATTRIBUTE:
            printf("Deleting an attribute from entity '%s'...\n", entity.name);
            // Implementar deleteAttribute
            break;

        case MODIFY_ATTRIBUTE:
            printf("Modifying an attribute of entity '%s'...\n", entity.name);
            // Implementar modifyAttribute
            break;

        case ADD_DATA_ATTRIBUTE:
            printf("Adding data to entity '%s'...\n", entity.name);
            // Implementar addDataToEntity
            break;

        case MODIFY_DATA_ATTRIBUTE:
            printf("Modifying data in entity '%s'...\n", entity.name);
            // Implementar modifyDataInEntity
            break;

        case DELETE_DATA_ATTRIBUTE:
            printf("Deleting data from entity '%s'...\n", entity.name);
            // Implementar deleteDataFromEntity
            break;

        case RETURN2:
            printf("Returning to the dictionary menu...\n");
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
    }
}