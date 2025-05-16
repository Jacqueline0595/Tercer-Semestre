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
void createEntityFun(char *dictionaryName);
long createEntity(FILE *dictionary, ENTITIES newEntity);
void orderEntity(FILE *dictionary, long currentEntity, const char *newNameEntity, long newDirEntity);

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
    printf("%ld \n", num);
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
    if (!dictionary)
    {
        printf("Error: Could not open the file '%s'. Make sure it exists.\n", dictionaryName);
        return;
    }

    switch(userSelec)
    {
        case PRINT:
            printf("Printing data dictionary...\n");
            //printDictionary(dictionary);
        break;

        case CREATE_ENTITY:
            printf("Creating a new entity...\n");
            //createEntityFun(dictionary);
        break;

        case DELETE_ENTITY:
            printf("Deleting an entity...\n");
            //deleteEntity(dictionary);
        break;

        case MODIFY_ENTITY:
            printf("Modifying an entity...\n");
            //modifyEntity(dictionary);
        break;

        case SELECT_ENTITY:
            printf("Selecting an entity...\n");
            //selectEntity(dictionary);
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
    printf("| %-50s | %-10s | %-10s | %-10s |\n", "Entity Name", "List Data", "List Attr", "Next");

    while(fread(&entity, sizeof(ENTITIES), 1, dictionary) == 1)
    {
        printf("| %-50s | %-10ld | %-10ld | %-10ld |\n", entity.name, entity.listDat, entity.listAttr, entity.sig);
    }

    fclose(dictionary);
    printf("\n--- End of Dictionary ---\n");
}

void createEntityFun(char *dictionaryName)
{
    FILE *dictionary = fopen(dictionaryName, "rb+");
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

    newEntity.listAttr = empty;
    newEntity.listDat = empty;
    newEntity.sig = empty;

    dirEntity = createEntity(dictionary, newEntity);

    printf("Entity '%s' created successfully.\n", newEntity.name);
    orderEntity(dictionary, 0, newEntity.name, dirEntity);

    fclose(dictionary);
}

long createEntity(FILE *dictionary, ENTITIES newEntity)
{
    long dirEntity;
    fseek(dictionary, 0, SEEK_END);
    dirEntity = ftell(dictionary);
    fwrite(&newEntity, sizeof(ENTITIES), 1, dictionary);
    return dirEntity;
}

void orderEntity(FILE *dictionary, long currentEntity, const char *newNameEntity, long newDirEntity)
{
    long dirEntity = empty;
    char currentEntityName[LENGTH];
    long nextHeaderPointer;

    fseek(dictionary, currentEntity, SEEK_SET);
    fread(&dirEntity, sizeof(dirEntity), 1, dictionary);

    if (dirEntity == -1L)
    {
        fseek(dictionary, currentEntity, SEEK_SET);
        fwrite(&newDirEntity, sizeof(long), 1, dictionary);
    }
    else
    {
        fseek(dictionary, dirEntity, SEEK_SET);
        fread(&currentEntityName, sizeof(char), LENGTH, dictionary);
        nextHeaderPointer = ftell(dictionary) + (sizeof(long) * 2);

        if (strcmp(currentEntityName, newNameEntity) < 0)
        {

            orderEntity(dictionary, nextHeaderPointer, newNameEntity, newDirEntity);
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
                fseek(dictionary, currentEntity, SEEK_SET);
                fwrite(&newDirEntity, sizeof(long), 1, dictionary);
                fseek(dictionary, newDirEntity + LENGTH + (sizeof(long) * 2), SEEK_SET);
                fwrite(&dirEntity, sizeof(long), 1, dictionary);
            }
        }
    }
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
        fflush(stdin);
        printf("Enter your choice: ");
        scanf("%d", &userSelec);
        while (getchar() != '\n'); 

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
            printf("Deleting data from entity '%s'...\n", entity.name);;
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