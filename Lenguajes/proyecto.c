#include "main.h"
#include "entity.h"


int main()
{
    processUserSelection();
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
    FILE *dataFile;
    int userSelection;
    long num = empty;
    char name[ENTITY_NAME_LENGHT];
    do
    {
        printMainMenu();
        scanf("%d", &userSelection);
        switch (userSelection)
        {
            case NEW_FILE:
                printf("Name of the dictionary: ");
                scanf("%s", name);
                if (!(dataFile = fopen(name, "wb")))
                {
                    printf("File didn't found\n");
                    break;
                }
                else
                    fwrite(&num, sizeof(long), 1, dataFile);
            break;
            case OPEN_FILE:
                printf("Name of the dictionary: ");
                scanf("%s", name);
                if (!(dataFile = fopen(name, "rb+")))
                {
                    printf("File didn't found\n");
                }
            break;
            case EXIT:
                printf("Ending program, see u later \n");
            break;
            default:
                printf("Wrong option \n");
            break;
        }
        fclose(dataFile);
        printf("\t We're going to the file...\n");
        processInputDictonary(name);
    } while(userSelection != EXIT);
}

void printDictionaryMenu()
{
    printf("\t --------Dictionary menu-------- \n");
    printf("--- %d Print data dictionary \n", PRINT);
    printf("--- %d Create an entity \n", CREATE_ENTITY);
    printf("--- %d Delete an entity \n", DELETE_ENTITY);
    printf("--- %d Modify an entity \n", MODIFY_ENTITY);
    printf("--- %d Select an entity \n", SELECT_ENTITY);
    printf("--- %d Exit \n", RETURN);
}

void processInputDictonary(char dictionary[])
{
    FILE *dataFile = fopen(dataFile, "+rb");
    int userSelec;
    long dirEntity;
    char name[ENTITY_NAME_LENGHT];
    ENTITY newEntity, entityy;

    do{
        printDictionaryMenu();
        scanf("%d", &userSelec);
        switch(userSelec)
        {
            case PRINT:
                printDictionary(dataFile);
            break;
            case CREATE_ENTITY:
            break;
            case DELETE_ENTITY:
            break;
            case MODIFY_ENTITY:
            break;
            case SELECT_ENTITY:
                processInputEntity();
            break;
            case RETURN:
                printf("Back to the main menu \n");
            break;
            default:
                printf("Wrong option \n");
            break;
        }
    } while(userSelec != RETURN);
}

void printEntityMenu()
{
    printf("\t --------Entity menu-------- \n");
    printf("--- %d Print data dictionary \n", PRINT2);
    printf("--- %d Create an attribute \n", CREATE_ATTRIBUTE);
    printf("--- %d Delete an attribute \n", DELETE_ATTRIBUTE);
    printf("--- %d Modify an attribute \n", MODIFY_ATTRIBUTE);
    printf("--- %d Select an attribute \n", SELECT_ATTRIBUTE);
    printf("--- %d Exit \n", RETURN2);
}

void processInputEntity()
{
    int userSelec;
    do{
        printEntityMenu();
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
}

void printDictionary(FILE *dataFile)
{
    ENTITY entityy;
    long dir;

    rewind(dataFile);
    fread(&dir, sizeof(long), 1, dataFile);
    if(dir == empty)
        printf("Dictionary empty... \n\n");
    else
        while(dir != empty)
        {
            fseek(dataFile, dir, SEEK_SET);

            fread(&entityy.name, ENTITY_NAME_LENGHT, 1, dataFile);
            fread(&entityy.listDat, sizeof(long), 1, dataFile);
            fread(&entityy.listAttr, sizeof(long), 1, dataFile);
            fread(&dir, sizeof(long), 1, entityy.name);
            printf("\n\t------ %s ------\n", entityy.name);

            ATTRIBUTE attri;
            long dir2;
            printf("------ Attributes ------ \n");
            if(entityy.listAttr == empty)
                printf("There is not attributes \n");
            else
            {
                dir2 = entityy.listAttr;
                while(dir2 != empty)
                {
                    fseek(dataFile, dir2, SEEK_SET);

                    fread(&attri.name, ENTITY_NAME_LENGHT, 1, dataFile);
                }
            }
        }
}