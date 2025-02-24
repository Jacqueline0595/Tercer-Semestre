#include "main.h"

// Hola

int main()
{
    int userSelection;
    do{
        printMainMenu();
        scanf("%d", &userSelection);
        processUserSelection(userSelection);
    } while(userSelection != 0);

    return 0;
}

void printMainMenu()
{
    printf("---------Main menu--------- \n");
    printf("--- %d Create new file \n", NEW_FILE);
    printf("--- %d Open existing file \n", OPEN_FILE);
    printf("--- %d Exit \n", EXIT);
}

void processUserSelection(int usSelec)
{
    FILE *dataFile;
    int userSelec;
    switch (usSelec)
    {
    case NEW_FILE:
        // TODO: ask for a new file name
        dataFile = CreateFile("test.dat");
        long header = -1;

        fwrite(&header, sizeof(long), 1, dataFile);
        for (int i = 0; i < 1; i++)
        {
            REGISTER dataBlock = createNewDataBlock();
            fwrite(&dataBlock, sizeof(REGISTER), 1, dataFile);
        }

        fclose(dataFile);
    break;
    case OPEN_FILE:
        printf("Openning existing file \n");
        /* dataFile = OpenFile("test.dat");
        fclose(dataFile); */
        do{
            printDictionaryMenu();
            scanf("%d", &userSelec);
        } while(userSelec != 0);
    break;
    default:
        printf("Wrong option \n");
    break;

    }
}

FILE *CreateFile(const char *fileName)
{
    printf("Creating a new file... \n");
    FILE *dataFile = fopen(fileName, "wb+");

    return dataFile;
}

FILE *OpenFile(const char *fileName)
{
    FILE *dataFile = fopen(fileName, "rb+");
    printf("Dictionary name: %c \n", *fileName);
    printDictionaryMenu();
    return dataFile;
}

REGISTER createNewDataBlock()
{
    REGISTER dataBlock;

    printf("Enter the name: ");
    fflush(stdin);
    fgets(dataBlock.name, STRING_LENGHT, stdin);
    // search the end of the line and insted put '\0'
    // send the direction of '\n'
    *(strchr(dataBlock.name, '\n')) = '\0';

    printf("Enter the generation: ");
    scanf("%d", &dataBlock.generation);

    printf("Enter the current semester: ");
    scanf("%d", &dataBlock.semester);

    return dataBlock;
}

void printDictionaryMenu()
{
    printf("--------Dictionary menu-------- \n");
    printf("--- %d Print data dictionary \n", PRINT);
    printf("--- %d Create an entity \n", CREATE_ENTITY);
    printf("--- %d Delete an entity \n", DELETE_ENTITY);
    printf("--- %d Modify an entity \n", MODIFY_ENTITY);
    printf("--- %d Select an entity \n", SELECT_ENTITY);
    printf("--- %d Exit \n", RETURN);
}

void printEntityMenu()
{
    printf("--------Entity menu-------- \n");
    printf("--- %d Print data dictionary \n", PRINT2);
    printf("--- %d Create an attribute \n", CREATE_ATTRIBUTE);
    printf("--- %d Delete an attribute \n", DELETE_ATTRIBUTE);
    printf("--- %d Modify an attribute \n", MODIFY_ATTRIBUTE);
    printf("--- %d Select an attribute \n", SELECT_ATTRIBUTE);
    printf("--- %d Exit \n", RETURN2);
}