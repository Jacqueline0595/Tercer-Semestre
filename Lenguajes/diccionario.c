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
    DATA_ATTRIBUTE 
};

int main()
{
    processUserSelection();
    return 0;
}

// ------ Other functions

void toUpperCase(char *strin)
{
    int length = strlen(strin);
    for (int i = 0; i < length; i++)
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
    FILE *dictionary;
    int userSel;
    long num = empty;
    char name[LENGTH];

    do 
    {
        printMainMenu();
        scanf("%d", &userSel);

        switch(userSel)
        {
            case NEW_FILE:
                processInputDictonary();
            break;

            case OPEN_FILE:
                processInputDictonary();
            break;

            case EXIT:
                printf("Ending program, see u later \n");
            break;

            default:
                /* system("cls"); */
                printf("Wrong option. Try again.\n");
            break;
        }

    } while(userSel != EXIT);
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

void processInputDictonary(char *dictionary)
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
            break;

            case CREATE_ENTITY:
            break;

            case DELETE_ENTITY:
                /* system("cls"); */
            break;

            case MODIFY_ENTITY:
                /* system("cls"); */
            break;

            case SELECT_ENTITY:
                /* system("cls"); */
            break;

            case RETURN:
                printf("Back to the main menu \n");
                processUserSelection();
            break;

            default:
                /* system("cls"); */
                printf("Wrong option \n");
            break;
        }
    } while(userSelec != RETURN);
    
    fclose(dict);
}

// ------ Attributes functions ------

void printEntityMenu(ENTITIES entity)
{
    printf("\t -------- %s's menu -------- \n", entity.name);
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