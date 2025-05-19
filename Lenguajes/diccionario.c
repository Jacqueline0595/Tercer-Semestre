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

// ------ Other functions ------

void toUpperCase(char *strin);
void askEntityName(char *name, int band);
void askAttributeName(char *name, int band);
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
void executeEntityOption(int userSelec, FILE *dictionary, ENTITIES entity,  char *dictionaryName);
void printAttributes(FILE *dictionary, char *dictionaryName, long listA);
void createAttribute(FILE *dictionary, char *dictionaryName, ENTITIES currentEntity);
long writeAttribute(FILE *dictionary, ATTRIBUTES newAttribute);
void orderAttribute(FILE *dictionary, char *dictionaryName, long currentAttr, ATTRIBUTES attribute, long newAttrDir);
int deleteAttribute(FILE *dictionary, char *dictionaryName, char *name, long listAttr);
void modifyAttribute(FILE *dictionary, char *dictionaryName, char *name, long listAttr);
void createData(FILE *dictionary, char *dictionaryName, ENTITIES currentEntity);
void addData(FILE *dictionary, char *dictionaryName, long newData, long listData, long listAttr);
void printData(FILE *dictionary, long listData, long listAttribute);

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

enum typeData
{
    BIT,
    INTEGER,
    FLOAT,
    CHAR,
    STRING
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

void askAttributeName(char *name, int band)
{
    printf("Enter the name of the attribute you want to %s: ", band ? "delete" : "modify");
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
            printDictionary(dictionary, dictionaryName);
        break;

        case CREATE_ENTITY:
            createEntity(dictionary, dictionaryName);
        break;

        case DELETE_ENTITY:
            askEntityName(name, 0);
            if(deleteEntity(dictionary, dictionaryName, name))
                printf("Entity deleted successfully.\n");
            else
                printf("Error: Entity not found.\n");
        break;

        case MODIFY_ENTITY:
            askEntityName(name, 1);
            modifyEntity(dictionary, dictionaryName, name);
        break;

        case SELECT_ENTITY:
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
            printf("\n\t ----- Attributes of entity '%s': ----- \n", entity.name);
            printf("| %-30s | %-10s | %-10s | %-10s | %-10s |\n", "Attribute name", "Is primary", "Type", "Size", "Next");

            printf("|------------------------------------------------------------------------------------|\n");
            while (direction2 != empty)
            {
                fseek(dictionary, direction2, SEEK_SET);
                fread(&attribute.name, LENGTH, 1, dictionary);
                fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
                fread(&attribute.type, sizeof(int), 1, dictionary);
                fread(&attribute.size, sizeof(int), 1, dictionary);
                fread(&direction2, sizeof(long), 1, dictionary);
                printf("| %-30s | %-10d | %-10d | %-10d | %-10ld |\n", attribute.name, attribute.isPrimary, attribute.type, attribute.size, direction2);
            }
            if(entity.listDat == empty)
            {
                printf("\t| No data found for entity '%s'.\n", entity.name);
            }
            else
            {
                printf("\n\t ----- Data of entity '%s': ----- \n", entity.name);
                printData(dictionary, entity.listDat, entity.listAttr);
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
    // ATTRIBUTES attribute;
    long entityAddress, dirData;

    originalEntity = findEntity(dictionary, oldName);
    if (originalEntity.sig == 0)
    {
        printf("Error: Entity '%s' not found.\n", oldName);
        return;
    }

    fseek(dictionary, originalEntity.listAttr, SEEK_SET);
    fread(&dirData, sizeof(long), 1, dictionary);
    if (dirData != empty)
    {
        printf("The entity already has attributes, we couldn't modify it\n");
        fclose(dictionary);
        return;
    }

    // Correct this part
    /* if(originalEntity.listAttr != empty)
    {
        fseek(dictionary, originalEntity.listAttr, SEEK_SET);
        fread(attribute.name, LENGTH, 1, dictionary);
        fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
        fread(&attribute.type, sizeof(int), 1, dictionary);
        fread(&attribute.size, sizeof(int), 1, dictionary);
        fread(&originalEntity.listAttr, sizeof(long), 1, dictionary);
        if(attribute.isPrimary == 1)
        {
            printf("Error: Cannot modify an entity with primary key attributes.\n");
            return;
        }
    } */



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

        executeEntityOption(userSelec, dictionary, entity, dictionaryName);


    } while (userSelec != RETURN2);

    fclose(dictionary);
}

void executeEntityOption(int userSelec, FILE *dictionary, ENTITIES entity,  char *dictionaryName)
{
    char name[LENGTH];

    switch (userSelec)
    {
        case PRINT2:
            printf("Printing attributes of entity '%s'...\n", entity.name);
            printAttributes(dictionary, dictionaryName, entity.listAttr);
        break;

        case CREATE_ATTRIBUTE:
            printf("Creating a new attribute for entity '%s'...\n", entity.name );
            createAttribute(dictionary, dictionaryName, entity);
        break;

        case DELETE_ATTRIBUTE:
            printf("Deleting an attribute from entity '%s'...\n", entity.name);
            askAttributeName(name, 1);
            if(deleteAttribute(dictionary, dictionaryName, name, entity.listAttr))
                printf("Attribute deleted successfully.\n");
            else
                printf("Error: Attribute not found.\n");
        break;

        case MODIFY_ATTRIBUTE:
            printf("Modifying an attribute of entity '%s'...\n", entity.name);
            askAttributeName(name, 0);
            modifyAttribute(dictionary, dictionaryName, name, entity.listAttr);
        break;

        case ADD_DATA_ATTRIBUTE:
            printf("Adding data to entity '%s'...\n", entity.name);
            createData(dictionary, dictionaryName, entity);
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

void printAttributes(FILE *dictionary, char *dictionaryName, long listA)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ATTRIBUTES attribute;
    long dir;

    printf("\t ----- Attributes ----- \n");
    printf("| %-30s | %-10s | %-10s | %-10s | %-10s |\n", "Attribute name", "Is primary", "Type", "Size", "Next");
    printf("|------------------------------------------------------------------------------------|\n");
    fseek(dictionary, listA, SEEK_SET);
    fread(&dir, sizeof(long), 1, dictionary);
    if (dir == empty || listA == empty)
        printf("\tThere aren't attributes\n");
    else
        while (dir != empty)
        {
            fseek(dictionary, dir, SEEK_SET);

            fread(&attribute.name, LENGTH, 1, dictionary);
            fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
            fread(&attribute.type, sizeof(int), 1, dictionary);
            fread(&attribute.size, sizeof(int), 1, dictionary);
            fread(&dir, sizeof(long), 1, dictionary);
            printf("| %-30s | %-10d | %-10d | %-10d | %-10ld |\n", attribute.name, attribute.isPrimary, attribute.type, attribute.size, dir);
        }
}

void createAttribute(FILE *dictionary, char *dictionaryName, ENTITIES currentEntity)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    ATTRIBUTES newAttribute;
    int size;

    printf("Name of the new attribute: ");
    fflush(stdin);
    fgets(newAttribute.name, LENGTH, stdin);
    cleanInput(newAttribute.name);
    toUpperCase(newAttribute.name);

    printf("Is it a primary key? (1 for yes, 0 for no): ");
    scanf("%d", &newAttribute.isPrimary);

    // {0:Bite, 1:Integer, 2:Float, 3:Char, 4:String}
    printf("Type of the attribute (%d for bite, %d for integer, %d for float, %d for char, %d for string): ", BIT, INTEGER, FLOAT, CHAR, STRING);
    scanf("%d", &newAttribute.type);

    // Size: *Bit=1, *Integer=4, *Float=8, *Char=1, String=? (Ask)
    switch (newAttribute.type)
    {
    case BIT:
        newAttribute.size = sizeof(unsigned char);
    break;

    case INTEGER:
        newAttribute.size = sizeof(int);
    break;

    case FLOAT:
        newAttribute.size = sizeof(double);
    break;

    case CHAR:
        newAttribute.size = sizeof(char);
    break;

    case STRING:
        // add validation for size
        printf("Size of the string: ");
        scanf("%d", &size);
        newAttribute.size = sizeof(char) * size;
    break;
    }

    newAttribute.next = empty;

    long attrDir = writeAttribute(dictionary, newAttribute);
    orderAttribute(dictionary, dictionaryName, currentEntity.listAttr, newAttribute, attrDir);
}

long writeAttribute(FILE *dictionary, ATTRIBUTES newAttribute)
{
    long attrDir;
    fseek(dictionary, 0, SEEK_END);
    attrDir = ftell(dictionary);
    fwrite(newAttribute.name, LENGTH, 1, dictionary);
    fwrite(&newAttribute.isPrimary, sizeof(int), 1, dictionary);
    fwrite(&newAttribute.type, sizeof(int), 1, dictionary);
    fwrite(&newAttribute.size, sizeof(int), 1, dictionary);
    fwrite(&newAttribute.next, sizeof(long), 1, dictionary);
    return attrDir;
}

void orderAttribute(FILE *dictionary, char *dictionaryName, long currentAttr, ATTRIBUTES attribute, long newAttrDir)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    long attrDir = empty;
    char currentAttrName[LENGTH];
    long nextHeaderPointer, isPrimary;

    fseek(dictionary, currentAttr, SEEK_SET);
    fread(&attrDir, sizeof(long), 1, dictionary);

    if (attrDir == empty)
    {
        fseek(dictionary, currentAttr, SEEK_SET);
        fwrite(&newAttrDir, sizeof(long), 1, dictionary);
    }
    else
    {
        fseek(dictionary, attrDir, SEEK_SET);
        fread(&currentAttrName, sizeof(char), LENGTH, dictionary);
        nextHeaderPointer = ftell(dictionary) + (sizeof(int) * 3);
        fread(&isPrimary, sizeof(int), 1, dictionary);

        if (attribute.isPrimary)
        {
            if (isPrimary == attribute.isPrimary)
            {
                printf("The key already exist. \n");
                return;
            }

            fseek(dictionary, currentAttr, SEEK_SET);
            fwrite(&newAttrDir, sizeof(int), 1, dictionary);
            fseek(dictionary, newAttrDir + LENGTH + (sizeof(int) * 3), SEEK_SET);
            fwrite(&attrDir, sizeof(long), 1, dictionary);
            return;
        }

        if (strcmp(currentAttrName, attribute.name) == 0)
        {
            printf("There is already an attribute with this name, please select another one.\n");
            return;
        }
        else
        {
            if (strcmp(currentAttrName, attribute.name) < 0 || isPrimary || attribute.isPrimary)
            {
                orderAttribute(dictionary, dictionaryName, nextHeaderPointer, attribute, newAttrDir);
            }
            else
            {
                
                fseek(dictionary, currentAttr, SEEK_SET);
                fwrite(&newAttrDir, sizeof(long), 1, dictionary);
                
                fseek(dictionary, newAttrDir + LENGTH + (sizeof(int) * 3), SEEK_SET);
                fwrite(&attrDir, sizeof(long), 1, dictionary);
            }
        }
    }
}

int deleteAttribute(FILE *dictionary, char *dictionaryName, char *name, long listAttr)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return 0;
    }

    rewind(dictionary);

    ATTRIBUTES attribute;
    long previousPtr, currentPtr, currentPos;

    fseek(dictionary, listAttr, SEEK_SET);
    fread(&currentPtr, sizeof(long), 1, dictionary);

    if (currentPtr == empty)
    {
        return 0;
    }

    fseek(dictionary, currentPtr, SEEK_SET);
    fread(attribute.name, LENGTH, 1, dictionary);
    fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
    fread(&attribute.type, sizeof(int), 1, dictionary);
    fread(&attribute.size, sizeof(int), 1, dictionary);
    currentPos = ftell(dictionary);
    fread(&currentPtr, sizeof(long), 1, dictionary);

    if (strcmp(attribute.name, name) == 0)
    {
        fseek(dictionary, listAttr, SEEK_SET);
        fwrite(&currentPtr, sizeof(long), 1, dictionary);
        return 1;
    }

    while (currentPtr != empty)
    {
        previousPtr = currentPos;
        fseek(dictionary, currentPtr, SEEK_SET);
        fread(attribute.name, LENGTH, 1, dictionary);
        fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
        fread(&attribute.type, sizeof(int), 1, dictionary);
        fread(&attribute.size, sizeof(int), 1, dictionary);
        currentPos = ftell(dictionary);
        fread(&currentPtr, sizeof(long), 1, dictionary);

        if (strcmp(attribute.name, name) == 0)
        {
            fseek(dictionary, previousPtr, SEEK_SET);
            fwrite(&currentPtr, sizeof(long), 1, dictionary);
            return 1;
        }
    }

    return 0;
}

void modifyAttribute(FILE *dictionary, char *dictionaryName, char *name, long listAttr)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    rewind(dictionary);
    ATTRIBUTES newAttribute;
    long dirAttr;

    fseek(dictionary, listAttr, SEEK_SET);
    fread(&dirAttr, sizeof(long), 1, dictionary);
    if (dirAttr == empty)
    {
        printf("The entity doesn't have any attributes.\n");
        return;
    }

    fseek(dictionary, dirAttr, SEEK_SET);
    fread(newAttribute.name, LENGTH, 1, dictionary);
    fread(&newAttribute.isPrimary, sizeof(int), 1, dictionary);
    fread(&newAttribute.type, sizeof(int), 1, dictionary);
    fread(&newAttribute.size, sizeof(int), 1, dictionary);
    fread(&dirAttr, sizeof(long), 1, dictionary);
    while (dirAttr != empty && (strcmp(newAttribute.name, name)) != 0)
    {
        fseek(dictionary, dirAttr, SEEK_SET);
        fread(newAttribute.name, LENGTH, 1, dictionary);
        fread(&newAttribute.isPrimary, sizeof(int), 1, dictionary);
        fread(&newAttribute.type, sizeof(int), 1, dictionary);
        fread(&newAttribute.size, sizeof(int), 1, dictionary);
        fread(&dirAttr, sizeof(long), 1, dictionary);
    }
    newAttribute.next = empty;
    if (dirAttr == empty && (strcmp(newAttribute.name, name)) != 0)
    {
        printf("The attribute doesn't exist, try with othe one.\n");
        return;
    }
    deleteAttribute(dictionary, dictionaryName, name, listAttr);

    printf("Enter the new name of the attribute: ");
    fflush(stdin);
    fgets(newAttribute.name, LENGTH, stdin);
    cleanInput(newAttribute.name);
    toUpperCase(newAttribute.name);

    dirAttr = writeAttribute(dictionary, newAttribute);
    orderAttribute(dictionary, dictionaryName, listAttr, newAttribute, dirAttr);
}

void createData(FILE *dictionary, char *dictionaryName, ENTITIES currentEntity)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    long listData, listAttr, listAttributes, next, newDat, possition;
    unsigned char dataBit;
    int dataInt;
    double dataFloat;
    char dataChar;
    char dataString[LENGTH];

    ATTRIBUTES attribute;

    fseek(dictionary, 0, SEEK_END);
    newDat = ftell(dictionary);
    printf("Possition: %ld \n", newDat);

    fseek(dictionary, currentEntity.listDat, SEEK_SET);
    fread(&listData, sizeof(long), 1, dictionary);
    fread(&listAttr, sizeof(long), 1, dictionary);
    listAttributes = listAttr;
    if (listAttributes == empty)
    {
        printf("No hay Atributos...\n");
        return;
    }

    while (listAttributes != empty)
    {
        fseek(dictionary, listAttributes, SEEK_SET);
        fread(attribute.name, LENGTH, 1, dictionary);
        fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
        fread(&attribute.type, sizeof(int), 1, dictionary);
        fread(&attribute.size, sizeof(int), 1, dictionary);
        // apuntador al siguiente attribute
        fread(&listAttributes, sizeof(long), 1, dictionary);

        printf("\tEnter %s: ", attribute.name);
        switch (attribute.type)
        {
            case BIT:
                do
                {
                    printf("\tWhich option: \n\t1)True 0)False ");
                    scanf("%hhu", &dataBit);
                } while (dataBit > 1);
                fseek(dictionary, 0, SEEK_END);
                fwrite(&dataBit, sizeof(unsigned char), 1, dictionary);
            break;
            case INTEGER:
                scanf("%d", &dataInt);
                fseek(dictionary, 0, SEEK_END);
                fwrite(&dataInt, sizeof(int), 1, dictionary);
            break;
            case FLOAT:
                scanf("%lf", &dataFloat);
                fseek(dictionary, 0, SEEK_END);
                fwrite(&dataFloat, sizeof(double), 1, dictionary);
            break;
            case CHAR:
                scanf(" %c", &dataChar);
                toUpperCase(&dataChar);
                fseek(dictionary, 0, SEEK_END);
                fwrite(&dataChar, sizeof(char), 1, dictionary);
            break;
            case STRING:
                do
                {
                    fflush(stdin);
                    fgets(dataString, LENGTH, stdin);
                    cleanInput(dataString);
                    toUpperCase(dataString);
                    fseek(dictionary, 0, SEEK_END);
                    fwrite(dataString, sizeof(char), attribute.size, dictionary);
                    if(strlen(dataString) > (size_t)attribute.size)
                        printf("The string is too long, please enter a new one less than %d: ", attribute.size);
                } while (strlen(dataString) > (size_t)attribute.size);
                
            break;
        }
        possition = ftell(dictionary);
        printf("Possition: %ld \n", possition);
    }
    next = empty;
    fwrite(&next, sizeof(long), 1, dictionary);
    addData(dictionary, dictionaryName, newDat, currentEntity.listDat, listAttr);
}

void addData(FILE *dictionary, char *dictionaryName, long newData, long listData, long listAttr)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    long listAttribute, next, end;
    unsigned char dataBit;  // BIT - 1 byte
    int dataInt;            // INTEGER - 4 bytes
    double dataFloat;       // FLOAT - 8 bytes
    char dataChar;          // CHAR - 1 byte
    char dataString[LENGTH]; // STRING - variable

    ATTRIBUTES attribute;

    fseek(dictionary, listData, SEEK_SET);
    fread(&next, sizeof(long), 1, dictionary);

    if (next == empty)
    {
        fseek(dictionary, listData, SEEK_SET);
        fwrite(&newData, sizeof(long), 1, dictionary);
    }
    else
    {
        while (next != empty)
        {
            listAttribute = listAttr;
            while (listAttribute != empty)
            {
                fseek(dictionary, listAttribute, SEEK_SET);
                fread(attribute.name, LENGTH, 1, dictionary);
                fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
                fread(&attribute.type, sizeof(int), 1, dictionary);
                fread(&attribute.size, sizeof(int), 1, dictionary);
                fread(&listAttribute, sizeof(long), 1, dictionary);

                fseek(dictionary, next, SEEK_SET);
                switch (attribute.type)
                {
                    case BIT:
                        fread(&dataBit, sizeof(unsigned char), 1, dictionary);
                        next = ftell(dictionary);
                    break;
                    case INTEGER:
                        fread(&dataInt, sizeof(int), 1, dictionary);
                        next = ftell(dictionary);
                    break;
                    case FLOAT:
                        fread(&dataFloat, sizeof(double), 1, dictionary);
                        next = ftell(dictionary);
                    break;
                    case CHAR:
                        fread(&dataChar, sizeof(char), 1, dictionary);
                        next = ftell(dictionary);
                    break;
                    case STRING:
                        fread(&dataString, sizeof(char), attribute.size, dictionary);
                        next = ftell(dictionary);
                    break;
                }
            }
            end = ftell(dictionary);
            fread(&next, sizeof(long), 1, dictionary);
        }
        fseek(dictionary, end, SEEK_SET);
        fwrite(&newData, sizeof(long), 1, dictionary);
    }
}

void printData(FILE *dictionary, long listData, long listAttribute)
{
    long listAttributes, next;
    unsigned char dataBit;
    int dataInt;
    double dataFloat;
    char dataChar;
    char dataString[LENGTH];

    ATTRIBUTES attribute;

    next = listData;

    if (next == empty)
    {
        printf("\t| No data found for entity.\n");
    }
    else
    {
        while (next != empty)
        {
            listAttributes = listAttribute;
            listData = next;
            while (listAttributes != empty)
            {
                fseek(dictionary, listAttributes, SEEK_SET);
                fread(attribute.name, LENGTH, 1, dictionary);
                fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
                fread(&attribute.type, sizeof(int), 1, dictionary);
                fread(&attribute.size, sizeof(int), 1, dictionary);
                fread(&listAttributes, sizeof(long), 1, dictionary);

                fseek(dictionary, listData, SEEK_SET);
                switch (attribute.type)
                {
                    case BIT:
                        fread(&dataBit, sizeof(unsigned char), 1, dictionary);
                        printf("| %s: %s ", attribute.name, dataBit ? "True" : "False");
                        break;
                    case INTEGER:
                        fread(&dataInt, sizeof(int), 1, dictionary);
                        printf("| %s: %d ", attribute.name, dataInt);
                        break;
                    case FLOAT:
                        fread(&dataFloat, sizeof(double), 1, dictionary);
                        printf("| %s: %.2lf ", attribute.name, dataFloat);
                        break;
                    case CHAR:
                        fread(&dataChar, sizeof(char), 1, dictionary);
                        printf("| %s: %c ", attribute.name, dataChar);
                        break;
                    case STRING:
                        fread(dataString, sizeof(char), attribute.size, dictionary);
                        printf("| %s: %s ", attribute.name, dataString);
                        break;
                }
                listData = ftell(dictionary);
            }
            fread(&next, sizeof(long), 1, dictionary);
            printf("|\n\n");
        }
    }
}
