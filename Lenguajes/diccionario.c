#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
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
    long next;
} ATTRIBUTES;

void toUpperCase(char *strin);
void askEntityName(char *name, int band);
void cleanInput(char *input);

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
void printDictionary(FILE *dictionary, char *dictionaryName);
void createEntity(FILE *dictionary, char *dictionaryName);
long writeEntity(FILE *dictionary, ENTITIES newEntity);
void orderEntity(FILE *dictionary, long currentEntity, const char *newNameEntity, long newDirEntity);
ENTITIES findEntity(FILE *dataDictionary, char *entityName);
int deleteEntity(FILE *dictionary, char *dictionaryName, char *name);
void modifyEntity(FILE *dictionary, char *dictionaryName, char *oldName);
void selectEntity(FILE *dictionary, char *dictionaryName, char *name);

// ------ Attributes functions ------

void printEntityMenu(ENTITIES entity);
void processInputEntity(char *dict, ENTITIES entity);
void executeEntityOption(int userSelec, FILE *dictionary, ENTITIES entity);

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

void cleanInput(char *input)
{
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
    else
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void askEntityName(char *name, int band)
{
    printf("Enter the name of the entity you want to %s: ", band == 0 ? "delete" : band == 1 ? "modify" : "select");
    fflush(stdin);
    fgets(name, LENGTH, stdin);
    cleanInput(name);
    toUpperCase(name);
}

// ------ Main menu ------

void printMainMenu()
{
    printf("----------- Main menu ----------- \n");
    printf("----- %d Create new file \n", NEW_FILE);
    printf("----- %d Open existing file \n", OPEN_FILE);
    printf("----- %d Exit \n", EXIT);
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
            while (getchar() != '\n');
            printf("Invalid input. Please enter a valid number.\n");
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
    fflush(stdin);
    printf("Enter the name of the new dictionary: ");
    fgets(name, LENGTH, stdin);
    cleanInput(name);
    long num = empty;

    dictionary = fopen(name, "wb");
    if (!dictionary)
    {
        printf("Error: Could not create the file.\n");
        return;
    }
    fwrite(&num, sizeof(long), 1, dictionary);
    fclose(dictionary);
    printf("File created successfully. Opening the file...\n\n");
    processInputDictionary(name);
}

void openFile(char *name)
{
    fflush(stdin);
    printf("Enter the name of the dictionary to open: ");
    fgets(name, LENGTH, stdin);
    cleanInput(name);

    FILE *dictionary = fopen(name, "rb+");
    if (!dictionary)
    {
        printf("Error: File '%s' not found or could not be opened.\n", name);
        return;
    }

    fclose(dictionary);
    printf("File '%s' opened successfully. Opening the file...\n\n", name);
    processInputDictionary(name);
}

// ------ Entity functions ------

void printDictionaryMenu(char *dictionary)
{
    printf("\n\n\t ----------- %s menu ----------- \n", dictionary);
    printf("----- %d Print data dictionary \n", PRINT);
    printf("----- %d Create an entity \n", CREATE_ENTITY);
    printf("----- %d Delete an entity \n", DELETE_ENTITY);
    printf("----- %d Modify an entity \n", MODIFY_ENTITY);
    printf("----- %d Select an entity \n", SELECT_ENTITY);
    printf("----- %d Exit \n", RETURN);
}

void processInputDictionary(char *dictionary)
{
    int userSelec;

    if(dictionary == NULL || strlen(dictionary) == 0)
    {
        printf("Error: Invalid dictionary name.\n");
        return;
    }

    do
    {
        printDictionaryMenu(dictionary);
        fflush(stdin);
        printf("Enter your choice: ");
        if(scanf("%d", &userSelec) != 1)
        {
            while (getchar() != '\n'); 
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
}

void executeDictionaryOption(int userSelec, char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    char name[LENGTH];
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    switch(userSelec)
    {
        case PRINT:
            printf("Printing data dictionary...\n");
            printDictionary(dictionary, dictionaryName);
        break;

        case CREATE_ENTITY:
            printf("Creating a new entity...\n");
            createEntity(dictionary, dictionaryName);
        break;

        case DELETE_ENTITY:
            printf("Deleting an entity...\n");
            askEntityName(name, 0);
            if(deleteEntity(dictionary, dictionaryName, name))
                printf("Entity deleted successfully.\n");
            else
                printf("Error: Entity not found.\n");
        break;

        case MODIFY_ENTITY:
            printf("Modifying an entity...\n");
            askEntityName(name, 1);
            modifyEntity(dictionary, dictionaryName, name);
        break;

        case SELECT_ENTITY:
            printf("Selecting an entity...\n");
            askEntityName(name, 2);
            selectEntity(dictionary, dictionaryName, name);
        break;

        case RETURN:
            printf("Returning to the main menu...\n");
        break;

        default:
            printf("Invalid option. Please try again.\n");
        break;
    }

    fclose(dictionary);
}

void printDictionary(FILE *dictionary, char *dictionaryName)
{
    if(!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ENTITIES entity;
    long direction;

    rewind(dictionary);
    fread(&direction, sizeof(long), 1, dictionary);
    if(direction == empty)
    {
        printf("No entities found in the dictionary.\n");
        fclose(dictionary);
        return;
    }

    printf("\n------- Data Dictionary: %s -------\n", dictionaryName);
    printf("| %-30s | %-10s | %-10s | %-10s |\n", "Entity Name", "List Data", "List Attr", "Next");

    printf("|-----------------------------------------------------------------------|\n");
    while(direction != empty)
    {
        fseek(dictionary, direction, SEEK_SET);
        fread(&entity.name, LENGTH, 1, dictionary);
        fread(&entity.listDat, sizeof(long), 1, dictionary);
        fread(&entity.listAttr, sizeof(long), 1, dictionary);
        fread(&direction, sizeof(long), 1, dictionary);
        printf("| %-30s | %-10ld | %-10ld | %-10ld |\n", entity.name, entity.listDat, entity.listAttr, direction);

        ATTRIBUTES attribute;
        long direction2 = entity.listAttr;

        if (direction2 == empty)
        {
            printf("\t| No attributes found for entity '%s'.\n", entity.name);
        }
        else
        {
            printf("\t ----- Attributes of entity '%s': ----- \n", entity.name);
            printf("\t| %-30s | %-10s | %-10s | %-10s | %-10s |\n", "Attribute name", "Is primary", "Type", "Size", "Next");
            while (direction2 != empty)
            {
                fseek(dictionary, direction2, SEEK_SET);
                fread(&attribute.name, LENGTH, 1, dictionary);
                fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
                fread(&attribute.type, sizeof(int), 1, dictionary);
                fread(&attribute.size, sizeof(int), 1, dictionary);
                fread(&direction2, sizeof(long), 1, dictionary);
                printf("\t| %-30s | %-10d | %-10d | %-10d | %-10ld |\n", attribute.name, attribute.isPrimary, attribute.type, attribute.size, direction2);
            }
            if(entity.listDat == empty)
            {
                printf("\tNo data found for entity '%s'.\n", entity.name);
            }
            else
            {
                printf("\t ----- Data of entity '%s': ----- \n", entity.name);
                // Implementar printData
            }
        }
    }

    printf("\n--- End of Dictionary ---\n");
}

void createEntity(FILE *dictionary, char *dictionaryName)
{
    if (!dictionary)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ENTITIES newEntity;
    long dirEntity;
    fflush(stdin);
    
    printf("Enter the name of the new entity: ");
    fgets(newEntity.name, LENGTH, stdin);
    cleanInput(newEntity.name);
    toUpperCase(newEntity.name);

    if(findEntity(dictionary, newEntity.name).sig != 0)
    {
        printf("Error: Entity '%s' already exists in the dictionary.\n", newEntity.name);
        return;
    }

    newEntity.listDat = empty;
    newEntity.listAttr = empty;
    newEntity.sig = empty;

    dirEntity = writeEntity(dictionary, newEntity);

    orderEntity(dictionary, 0, newEntity.name, dirEntity);

    printf("Entity '%s' created successfully, and added to %ld.\n", newEntity.name, dirEntity);
}

long writeEntity(FILE *dictionary, ENTITIES newEntity)
{
    long dirEntity;
    fseek(dictionary, 0, SEEK_END);
    dirEntity = ftell(dictionary);
    printf("Adding %s | %ld | %ld | %ld \n", newEntity.name, newEntity.listDat, newEntity.listAttr, newEntity.sig);
    fwrite(newEntity.name, 50, 1, dictionary);
    fwrite(&newEntity.listDat, sizeof(long), 1, dictionary);
    fwrite(&newEntity.listAttr, sizeof(long), 1, dictionary);
    fwrite(&newEntity.sig, sizeof(long), 1, dictionary);
    return dirEntity;
}

void orderEntity(FILE *dictionary, long currentEntity, const char *newNameEntity, long newDirEntity)
{
    long dirEntity = empty;

    fseek(dictionary, currentEntity, SEEK_SET);
    fread(&dirEntity, sizeof(long), 1, dictionary);

    if (dirEntity == empty)
    {
        fseek(dictionary, currentEntity, SEEK_SET);
        fwrite(&newDirEntity, sizeof(long), 1, dictionary);
    }
    else
    {
        char currentEntityName[50];
        long nextHeaderPointer;

        fseek(dictionary, dirEntity, SEEK_SET);
        fread(&currentEntityName, sizeof(char), 50, dictionary);
        nextHeaderPointer = ftell(dictionary) + (sizeof(long) * 2);
        if (strcmp(currentEntityName, newNameEntity) < 0)
        {
            orderEntity(dictionary, nextHeaderPointer, newNameEntity, newDirEntity);
        }
        else
        {
            fseek(dictionary, currentEntity, SEEK_SET);
            fwrite(&newDirEntity, sizeof(long), 1, dictionary);
            fseek(dictionary, newDirEntity + LENGTH + (sizeof(long) * 2), SEEK_SET);
            fwrite(&dirEntity, sizeof(long), 1, dictionary);
        }
    }
}

ENTITIES findEntity(FILE *dataDictionary, char *entityName)
{
    ENTITIES currentEntity, aux;

    rewind(dataDictionary);
    fread(&aux.sig, sizeof(long), 1, dataDictionary);
    fseek(dataDictionary, aux.sig, SEEK_SET);
    fread(&currentEntity.name, sizeof(char), 50, dataDictionary);
    currentEntity.listDat = ftell(dataDictionary);
    fread(&aux.listDat, sizeof(long), 1, dataDictionary);
    currentEntity.listAttr = ftell(dataDictionary);
    fread(&aux.listAttr, sizeof(long), 1, dataDictionary);
    currentEntity.sig = ftell(dataDictionary);
    fread(&aux.sig, sizeof(long), 1, dataDictionary);

    while (aux.sig != -1 && (strcmp(currentEntity.name, entityName)) != 0)
    {

        fseek(dataDictionary, aux.sig, SEEK_SET);
        fread(&currentEntity.name, sizeof(char), 50, dataDictionary);
        currentEntity.listDat = ftell(dataDictionary);
        fread(&aux.listDat, sizeof(long), 1, dataDictionary);
        currentEntity.listAttr = ftell(dataDictionary);
        fread(&aux.listAttr, sizeof(long), 1, dataDictionary);
        currentEntity.sig = ftell(dataDictionary);
        fread(&aux.sig, sizeof(long), 1, dataDictionary);
    }

    if(aux.sig == -1 && (strcmp(currentEntity.name, entityName)) != 0)
        currentEntity.sig = 0;

    return currentEntity;
}

int deleteEntity(FILE *dictionary, char *dictionaryName, char *name) 
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return 0;
    }

    ENTITIES entity;
    long currentPtr = empty, previousPtr = empty, currentPos = empty;
    long headPtr;
    rewind(dictionary);
    fread(&headPtr, sizeof(long), 1, dictionary);

    currentPtr = headPtr;

    while (currentPtr != empty)
    {
        fseek(dictionary, currentPtr, SEEK_SET);

        fread(entity.name, LENGTH, 1, dictionary);
        fread(&entity.listDat, sizeof(long), 1, dictionary);
        fread(&entity.listAttr, sizeof(long), 1, dictionary);
        currentPos = ftell(dictionary);
        fread(&entity.sig, sizeof(long), 1, dictionary);

        if (strcmp(entity.name, name) == 0)
        {
            if (currentPtr == headPtr)
            {
                rewind(dictionary);
                fwrite(&entity.sig, sizeof(long), 1, dictionary);
            }
            else
            {
                fseek(dictionary, previousPtr, SEEK_SET);
                fwrite(&entity.sig, sizeof(long), 1, dictionary);
            }
            return 1;
        }

        previousPtr = currentPos;
        currentPtr = entity.sig;
    }

    return 0;
}

void modifyEntity(FILE *dictionary, char *dictionaryName, char *oldName)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    rewind(dictionary);
    ENTITIES originalEntity, updatedEntity, checkEntity;
    ATTRIBUTES attribute;
    long entityAddress;

    originalEntity = findEntity(dictionary, oldName);
    if (originalEntity.sig == 0)
    {
        printf("Error: Entity '%s' not found.\n", oldName);
        return;
    }

    if (!deleteEntity(dictionary, dictionaryName, oldName))
    {
        printf("Error deleting the entity '%s'.\n", oldName);
        return;
    }

    do {
        printf("Enter the new name of the entity: ");
        fflush(stdin);
        fgets(updatedEntity.name, LENGTH, stdin);
        cleanInput(updatedEntity.name);
        toUpperCase(updatedEntity.name);

        checkEntity = findEntity(dictionary, updatedEntity.name);
        if (checkEntity.sig != 0)
            printf("This name is already used. Please enter another name.\n");

    } while (checkEntity.sig != 0);

    fseek(dictionary, originalEntity.listDat, SEEK_SET);
    fread(&updatedEntity.listDat, sizeof(long), 1, dictionary);
    fread(&updatedEntity.listAttr, sizeof(long), 1, dictionary);
    updatedEntity.sig = empty;

    if(updatedEntity.listAttr != empty)
    {
        fseek(dictionary, updatedEntity.listAttr, SEEK_SET);
        fread(attribute.name, LENGTH, 1, dictionary);
        fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
        fread(&attribute.type, sizeof(int), 1, dictionary);
        fread(&attribute.size, sizeof(int), 1, dictionary);
        fread(&updatedEntity.listAttr, sizeof(long), 1, dictionary);
        if(attribute.isPrimary == 1)
        {
            printf("Error: Cannot modify an entity with primary key attributes.\n");
            return;
        }
    }

    entityAddress = writeEntity(dictionary, updatedEntity);
    orderEntity(dictionary, 0, updatedEntity.name, entityAddress);

    printf("Successfully modified!\n");
}

void selectEntity(FILE *dictionary, char *dictionaryName, char *name)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    rewind(dictionary);
    ENTITIES entity;
    long dirData;
    entity = findEntity(dictionary, name);
    if (entity.sig == 0)
    {
        printf("Error: Entity '%s' not found.\n", name);
        return;
    }
    fseek(dictionary, entity.listDat, SEEK_SET);
    fread(&dirData, sizeof(long), 1, dictionary);
    if (dirData != empty)
    {
        printf("The entity already has data, we couldn't modify it\n");
        fclose(dictionary);
        return;
    }

    printf("Going to the entity menu. \n");
    fclose(dictionary);
    processInputEntity(dictionaryName, entity);
}

// ------ Attributes functions ------

void printEntityMenu(ENTITIES entity)
{
    printf("\n\n\t\t ----------- %s's menu ----------- \n", entity.name);
    printf("\t----- %d Print attributes \n", PRINT2);
    printf("\t----- %d Create an attribute \n", CREATE_ATTRIBUTE);
    printf("\t----- %d Delete an attribute \n", DELETE_ATTRIBUTE);
    printf("\t----- %d Modify an attribute \n", MODIFY_ATTRIBUTE);
    printf("\t----- %d Add data to the entity \n", ADD_DATA_ATTRIBUTE);
    printf("\t----- %d Modify data to the entity \n", MODIFY_DATA_ATTRIBUTE);
    printf("\t----- %d Delete data to the entity \n", DELETE_DATA_ATTRIBUTE);
    printf("\t----- %d Exit \n", RETURN2);
}

void processInputEntity(char *dictionaryName, ENTITIES entity)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    int userSelec;

    do
    {
        printEntityMenu(entity);
        fflush(stdin);
        printf("Enter your choice: ");
        scanf("%d", &userSelec);
        while (getchar() != '\n'); 

        if(userSelec < RETURN2 || userSelec > DELETE_DATA_ATTRIBUTE)
        {
            printf("Invalid option. Please try again.\n");
            continue;
        }

        executeEntityOption(userSelec, dictionary, entity);


    } while (userSelec != RETURN2);

    fclose(dictionary);
}

void executeEntityOption(int userSelec, FILE *dictionary, ENTITIES entity)
{
    switch (userSelec)
    {
        case PRINT2:
            printf("Printing attributes of entity '%s'...\n", entity.name);
            // Implementar printAttributes
            break;

        case CREATE_ATTRIBUTE:
            printf("Creating a new attribute for entity '%s'...\n", entity.name );
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
            // Implementar deleteDataFromEntityty
            break;

        case RETURN2:
            printf("Returning to the dictionary menu...\n");
            break;

        default:        
            printf("Invalid option. Please try again.\n");
        break;
    }
}