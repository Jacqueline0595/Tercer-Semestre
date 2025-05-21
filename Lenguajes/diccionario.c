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
    long next;
} ATTRIBUTES;

// ------ Other functions ------

void toUpperCase(char *strin);
void askEntityName(char *name, int band);
void askEntityName2(char *name);
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
void createAttribute(FILE *dictionary, const char *dictionaryName, ENTITIES currentEntity);
long writeAttribute(FILE *dictionary, ATTRIBUTES newAttribute);
void orderAttribute(FILE *dictionary, const char *dictionaryName, long currentAttr, ATTRIBUTES attribute, long newAttrDir);
int deleteAttribute(FILE *dictionary, const char *dictionaryName, const char *nameToDelete, long listAttr);
void modifyAttribute(FILE *dictionary, const char *dictionaryName, const char *targetName, long listAttr);

// ------ Data functions ------

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
    SELECT_ENTITY,
    ADD_DATA
};

enum AttributeOp
{ 
    RETURN2, 
    PRINT2, 
    CREATE_ATTRIBUTE, 
    DELETE_ATTRIBUTE, 
    MODIFY_ATTRIBUTE
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
    system("cls");
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

void askEntityName2(char *name)
{
    printf("Enter the name of the entity you want to add data: ");
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
            printf("Invalid input. Please enter a valid number.\n");
            continue;
        }
        fflush(stdin);
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
    printf("Enter the name of the new dictionary (just name): ");
    fgets(name, LENGTH, stdin);
    cleanInput(name);
    strcat(name, ".dat");

    long num = empty;

    FILE *existingFile = fopen(name, "rb");
    if(existingFile)
    {
        fclose(existingFile);
        printf("Error: File '%s' already exists. Please choose a different name.\n", name);
        return;
    }

    dictionary = fopen(name, "wb");
    if (!dictionary)
    {
        printf("Error: Could not create the file.\n");
        return;
    }
    fwrite(&num, sizeof(long), 1, dictionary);
    fclose(dictionary);
    system("cls");
    processInputDictionary(name);
}

void openFile(char *name)
{
    fflush(stdin);
    printf("Enter the name of the dictionary to open (just name): ");
    fgets(name, LENGTH, stdin);
    cleanInput(name);

    strcat(name, ".dat");

    FILE *dictionary = fopen(name, "rb+");
    if (!dictionary)
    {
        printf("Error: File '%s' not found or could not be opened.\n", name);
        return;
    }

    fclose(dictionary);
    system("cls");
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
    printf("----- %d Add data to an entity \n", ADD_DATA);
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
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        if(userSelec < RETURN || userSelec > ADD_DATA)
        {
            printf("Invalid option. Please select a valid menu option.\n");
            continue;
        }
        fflush(stdin);
        executeDictionaryOption(userSelec, dictionary);
    } while(userSelec != RETURN);
}

void executeDictionaryOption(int userSelec, char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
    ENTITIES entity;
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

        case ADD_DATA:
            askEntityName2(name);
            entity = findEntity(dictionary, name);
            if(entity.sig == 0)
            {
                printf("Error: Entity '%s' not found.\n", name);
                break;
            }
            createData(dictionary, dictionaryName, entity);
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

    system("cls");
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
        const char *typeString;

        if (direction2 == empty)
        {
            printf("\n\t| No attributes found for entity '%s'.\n", entity.name);
        }
        else
        {
            printf("\n\t ----- Attributes of entity '%s': ----- \n", entity.name);
            printf("\t| %-30s | %-10s | %-10s | %-10s | %-10s |\n", "Attribute name", "Is primary", "Type", "Size", "Next");

            printf("\t|------------------------------------------------------------------------------------|\n");
            while (direction2 != empty)
            {
                fseek(dictionary, direction2, SEEK_SET);
                fread(&attribute.name, LENGTH, 1, dictionary);
                fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
                fread(&attribute.type, sizeof(int), 1, dictionary);
                fread(&attribute.size, sizeof(int), 1, dictionary);
                fread(&direction2, sizeof(long), 1, dictionary);
                switch (attribute.type)
                {
                    case 0: typeString = "Bit"; break;
                    case 1: typeString = "Integer"; break;
                    case 2: typeString = "Float"; break;
                    case 3: typeString = "Char"; break;
                    case 4: typeString = "String"; break;
                    default: typeString = "Unknown"; break;
                }
                const char *primaryString = attribute.isPrimary ? "Yes" : "No";

                printf("\t| %-30s | %-10s | %-10s | %-10d | %-10ld |\n", attribute.name, primaryString, typeString, attribute.size, direction2);
            }
            if(entity.listDat == empty)
            {
                printf("\n\n\t| No data found for entity '%s'.\n", entity.name);
            }
            else
            {
                printf("\n\t\t ----- Data of entity '%s': ----- \n", entity.name);
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

    system("cls");

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

    while (aux.sig != empty && (strcmp(currentEntity.name, entityName)) != 0)
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

    if(aux.sig == empty && (strcmp(currentEntity.name, entityName)) != 0)
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

    system("cls");

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

    system("cls");

    rewind(dictionary);
    ENTITIES originalEntity, updatedEntity, checkEntity;
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

    system("cls");

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
        printf("The entity already has data, we couldn't modify it. \n");
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

        if(userSelec < RETURN2 || userSelec > MODIFY_ATTRIBUTE)
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
            printAttributes(dictionary, dictionaryName, entity.listAttr);
        break;

        case CREATE_ATTRIBUTE:
            createAttribute(dictionary, dictionaryName, entity);
        break;

        case DELETE_ATTRIBUTE:
            askAttributeName(name, 1);
            if(deleteAttribute(dictionary, dictionaryName, name, entity.listAttr))
                printf("Attribute deleted successfully.\n");
            else
                printf("Error: Attribute not found.\n");
        break;

        case MODIFY_ATTRIBUTE:
            askAttributeName(name, 0);
            modifyAttribute(dictionary, dictionaryName, name, entity.listAttr);
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

    system("cls");

    ATTRIBUTES attribute;
    long dir;
    const char *typeString;

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
            switch (attribute.type)
                {
                    case 0: typeString = "Bit"; break;
                    case 1: typeString = "Integer"; break;
                    case 2: typeString = "Float"; break;
                    case 3: typeString = "Char"; break;
                    case 4: typeString = "String"; break;
                    default: typeString = "Unknown"; break;
                }
                const char *primaryString = attribute.isPrimary ? "Yes" : "No";
            printf("| %-30s | %-10s | %-10s | %-10d | %-10ld |\n", attribute.name, primaryString, typeString, attribute.size, dir);
        }
}

void createAttribute(FILE *dictionary, const char *dictionaryName, ENTITIES currentEntity)
{
    if (!dictionary)
    {
        fprintf(stderr, "Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    system("cls");

    ATTRIBUTES newAttribute = {0};
    int stringLength = 0;

    fflush(stdin);
    fseek(dictionary, currentEntity.listDat, SEEK_SET);

    printf("Name of the new attribute: ");
    fflush(stdin);
    fgets(newAttribute.name, LENGTH, stdin);
    cleanInput(newAttribute.name);
    toUpperCase(newAttribute.name);

    do
    {
        printf("Is it a primary key? (1 for yes, 0 for no): ");
    } while (scanf("%d", &newAttribute.isPrimary) != 1 || (newAttribute.isPrimary != 0 && newAttribute.isPrimary != 1));

    printf("Type of the attribute (%d:BITE, %d:INTEGER, %d:FLOAT, %d:CHAR, %d:STRING): ", BIT, INTEGER, FLOAT, CHAR, STRING);
    while (scanf("%d", &newAttribute.type) != 1 || newAttribute.type < BIT || newAttribute.type > STRING)
    {
        printf("Invalid type. Please enter a valid option: ");
        while (getchar() != '\n');
    }

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
            do
            {
                printf("Size of the string (1 to %d): ", LENGTH - 1);
                if (scanf("%d", &stringLength) != 1)
                {
                    stringLength = 0;
                    while (getchar() != '\n');
                }
            } while (stringLength <= 0 || stringLength >= LENGTH);

            newAttribute.size = sizeof(char) * stringLength;
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

void orderAttribute(FILE *dictionary, const char *dictionaryName, long currentAttr, ATTRIBUTES attribute, long newAttrDir)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    long attrDir = empty;
    char currentAttrName[LENGTH] = {0};
    long nextHeaderPointer = 0;
    int isPrimary = 0;

    if (fseek(dictionary, currentAttr, SEEK_SET) != 0 || fread(&attrDir, sizeof(long), 1, dictionary) != 1)
    {
        printf("Error: We couldn't read attribute pointer at position %ld.\n", currentAttr);
        return;
    }

    if (attrDir == empty)
    {
        if (fseek(dictionary, currentAttr, SEEK_SET) == 0)
            fwrite(&newAttrDir, sizeof(long), 1, dictionary);
        else
            printf("Error: We couldn't create new attribute at empty position.\n");

        return;
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
                printf("Error: A primary key already exists in this entity.\n");
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
            printf("Error: An attribute with this name already exists. Choose another name.\n");
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

int deleteAttribute(FILE *dictionary, const char *dictionaryName, const char *nameToDelete, long listAttr)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return 0;
    }

    if (listAttr == empty)
    {
        printf("No attributes to delete. The list is empty.\n");
        return 0;
    }

    system("cls");

    rewind(dictionary);

    ATTRIBUTES attribute;
    long previousPtr = empty;
    long currentPtr = empty;
    long currentPos = empty;

    fseek(dictionary, listAttr, SEEK_SET);
    if (fread(&currentPtr, sizeof(long), 1, dictionary) != 1)
    {
        printf("Error reading initial attribute pointer.\n");
        return 0;
    }

    if (currentPtr == empty)
    {
        printf("No attributes to delete. The list pointer is empty.\n");
        return 0;
    }

    fseek(dictionary, currentPtr, SEEK_SET);
    if (fread(attribute.name, LENGTH, 1, dictionary) != 1 ||
        fread(&attribute.isPrimary, sizeof(int), 1, dictionary) != 1 ||
        fread(&attribute.type, sizeof(int), 1, dictionary) != 1 ||
        fread(&attribute.size, sizeof(int), 1, dictionary) != 1)
    {
        printf("Error reading first attribute.\n");
        return 0;
    }

    currentPos = ftell(dictionary);
    if (fread(&currentPtr, sizeof(long), 1, dictionary) != 1)
    {
        printf("Error reading 'next' pointer of first attribute.\n");
        return 0;
    }

    if (strcmp(attribute.name, nameToDelete) == 0)
    {
        fseek(dictionary, listAttr, SEEK_SET);
        fwrite(&currentPtr, sizeof(long), 1, dictionary);
        printf("Deleting '%s'...\n", nameToDelete);
        return 1;
    }

    while (currentPtr != empty)
    {
        previousPtr = currentPos;

        fseek(dictionary, currentPtr, SEEK_SET);
        if (fread(attribute.name, LENGTH, 1, dictionary) != 1 ||
            fread(&attribute.isPrimary, sizeof(int), 1, dictionary) != 1 ||
            fread(&attribute.type, sizeof(int), 1, dictionary) != 1 ||
            fread(&attribute.size, sizeof(int), 1, dictionary) != 1)
        {
            printf("Error reading attribute during traversal.\n");
            return 0;
        }

        currentPos = ftell(dictionary);
        if (fread(&currentPtr, sizeof(long), 1, dictionary) != 1)
        {
            printf("Error reading 'next' pointer during traversal.\n");
            return 0;
        }

        if (strcmp(attribute.name, nameToDelete) == 0)
        {
            fseek(dictionary, previousPtr, SEEK_SET);
            fwrite(&currentPtr, sizeof(long), 1, dictionary);
            printf("Deleting '%s'...\n", nameToDelete);
            return 1;
        }
    }

    printf("Attribute '%s' not found.\n", nameToDelete);

    return 0;
}

void modifyAttribute(FILE *dictionary, const char *dictionaryName, const char *targetName, long listAttr)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    system("cls");

    rewind(dictionary);

    ATTRIBUTES attribute;
    long currentDir;

    fseek(dictionary, listAttr, SEEK_SET);
    if (fread(&currentDir, sizeof(long), 1, dictionary) != 1)
    {
        printf("Error reading attribute list pointer.\n");
        return;
    }

    if (currentDir == empty)
    {
        printf("The entity doesn't have any attributes.\n");
        return;
    }

    long foundDir = empty;
    while (currentDir != empty)
    {
        fseek(dictionary, currentDir, SEEK_SET);
        if (fread(attribute.name, LENGTH, 1, dictionary) != 1 ||
            fread(&attribute.isPrimary, sizeof(int), 1, dictionary) != 1 ||
            fread(&attribute.type, sizeof(int), 1, dictionary) != 1 ||
            fread(&attribute.size, sizeof(int), 1, dictionary) != 1 ||
            fread(&attribute.next, sizeof(long), 1, dictionary) != 1)
        {
            printf("Error reading attribute data during search.\n");
            return;
        }

        if (strcmp(attribute.name, targetName) == 0)
        {
            foundDir = currentDir;
            break;
        }

        currentDir = attribute.next;
    }

    if (foundDir == empty)
    {
        printf("The attribute '%s' doesn't exist. Please try another name.\n", targetName);
        return;
    }

    if (!deleteAttribute(dictionary, dictionaryName, targetName, listAttr))
    {
        printf("Unable to delete the original attribute. Modification aborted.\n");
        return;
    }

    printf("Enter the new name of the attribute: ");
    fflush(stdin);
    fgets(attribute.name, LENGTH, stdin);
    cleanInput(attribute.name);
    toUpperCase(attribute.name);

    do {
        printf("Is this attribute a primary key? (0 = No, 1 = Yes): ");
        if (scanf("%d", &attribute.isPrimary) != 1 || (attribute.isPrimary != 0 && attribute.isPrimary != 1))
        {
            printf("Invalid input. Enter 1 for Yes or 0 for No.\n");
            while (getchar() != '\n');
            attribute.isPrimary = empty;
        }
    } while (attribute.isPrimary != 0 && attribute.isPrimary != 1);

    do {
        printf("Enter the attribute type (%d = BIT, %d = INTEGER, %d = FLOAT, %d = CHAR, %d = STRING): ", BIT, INTEGER, FLOAT, CHAR, STRING);
        if (scanf("%d", &attribute.type) != 1 || attribute.type < BIT || attribute.type > STRING)
        {
            printf("Invalid type. Please enter 0, 1, 2, 3 or 4.\n");
            while (getchar() != '\n');
            attribute.type = empty;
        }
    } while (attribute.type < BIT || attribute.type > STRING);

    int stringLength = 0;

    switch (attribute.type)
    {
        case BIT:
            attribute.size = sizeof(unsigned char);
        break;

        case INTEGER:
            attribute.size = sizeof(int);
        break;

        case FLOAT:
            attribute.size = sizeof(double);
        break;

        case CHAR:
            attribute.size = sizeof(char);
        break;

        case STRING:
            do
            {
                printf("Size of the string (1 to %d): ", LENGTH - 1);
                if (scanf("%d", &stringLength) != 1)
                {
                    stringLength = 0;
                    while (getchar() != '\n');
                }
            } while (stringLength <= 0 || stringLength >= LENGTH);

            attribute.size = stringLength;
        break;
    }

    while (getchar() != '\n'); // limpiar el buffer final

    long newDir = writeAttribute(dictionary, attribute);
    orderAttribute(dictionary, dictionaryName, listAttr, attribute, newDir);

    printf("Attribute modified successfully.\n");
}

// ------ Data functions ------

void createData(FILE *dictionary, char *dictionaryName, ENTITIES currentEntity)
{
    if (dictionary == NULL)
    {
        printf("Error: Couldn't open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    long listData, listAttr, listAttributes, next, newDat;
    unsigned char dataBit;
    int dataInt;
    double dataFloat;
    char dataChar;
    char dataString[LENGTH];
    const char *typeString;

    ATTRIBUTES attribute;

    fseek(dictionary, 0, SEEK_END);
    newDat = ftell(dictionary);

    fseek(dictionary, currentEntity.listDat, SEEK_SET);
    fread(&listData, sizeof(long), 1, dictionary);
    fread(&listAttr, sizeof(long), 1, dictionary);
    listAttributes = listAttr;

    if (listAttributes == empty)
    {
        printf("No attributes found for this entity. Data entry aborted.\n");
        return;
    }

    while (listAttributes != empty)
    {
        fseek(dictionary, listAttributes, SEEK_SET);
        fread(attribute.name, LENGTH, 1, dictionary);
        fread(&attribute.isPrimary, sizeof(int), 1, dictionary);
        fread(&attribute.type, sizeof(int), 1, dictionary);
        fread(&attribute.size, sizeof(int), 1, dictionary);
        fread(&listAttributes, sizeof(long), 1, dictionary);

        switch (attribute.type)
        {
            case 0: typeString = "Bit"; break;
            case 1: typeString = "Integer"; break;
            case 2: typeString = "Float"; break;
            case 3: typeString = "Char"; break;
            case 4: typeString = "String"; break;
            default: typeString = "Unknown"; break;
        }

        printf("\tEnter the %s (Type: %s): ", attribute.name, typeString);
        switch (attribute.type)
        {
            case BIT:
                do
                {
                    printf("\t\nWhich option: \n\t1)True 0)False ");
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
        // Removed unused variable 'possition'
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
    unsigned char dataBit;
    int dataInt;
    double dataFloat;
    char dataChar;
    char dataString[LENGTH];

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

void printData(FILE *dictionary, long listData, long listAttri)
{
    if (listData == empty)
    {
        printf("\n\t| No data found for entity.\n");
        return;
    }

    long currentData = listData;
    long currentAttr;
    ATTRIBUTES attr;
    unsigned char bitValue;
    int intValue;
    double floatValue;
    char charValue;
    char stringValue[LENGTH];

    printf("\t\t");

    while (currentData != empty)
    {
        currentAttr = listAttri;

        while (currentAttr != empty)
        {
            fseek(dictionary, currentAttr, SEEK_SET);
            fread(attr.name, LENGTH, 1, dictionary);
            fread(&attr.isPrimary, sizeof(int), 1, dictionary);
            fread(&attr.type, sizeof(int), 1, dictionary);
            fread(&attr.size, sizeof(int), 1, dictionary);
            fread(&currentAttr, sizeof(long), 1, dictionary);

            fseek(dictionary, currentData, SEEK_SET);

            switch (attr.type)
            {
                case BIT:
                    fread(&bitValue, sizeof(unsigned char), 1, dictionary);
                    printf("| %s : %-10s ", attr.name, bitValue ? "True" : "False");
                break;
                case INTEGER:
                    fread(&intValue, sizeof(int), 1, dictionary);
                    printf("| %s : %-10d ", attr.name, intValue);
                break;
                case FLOAT:
                    fread(&floatValue, sizeof(double), 1, dictionary);
                    printf("| %s : %-10.2lf ", attr.name, floatValue);
                break;
                case CHAR:
                    fread(&charValue, sizeof(char), 1, dictionary);
                    printf("| %s : %-10c ", attr.name, charValue);
                break;
                case STRING:
                    fread(stringValue, attr.size, sizeof(char), dictionary);
                    stringValue[attr.size] = '\0'; 
                    printf("| %s : %-50s ", attr.name, stringValue);
                break;
            }

            currentData = ftell(dictionary);
        }

        fread(&currentData, sizeof(long), 1, dictionary);
        printf("|\n");
        printf("\t\t");
    }

    printf("\n\n");
}