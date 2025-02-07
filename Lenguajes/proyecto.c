#include "main.h"

// Hola

int main()
{
    int userSelection;
    printMainMenu();
    scanf("%d", &userSelection);
    processUserSelection(userSelection);

    return 0;
}

void printMainMenu()
{
    printf("-------Main menu------- \n");
    printf("--- %d Create new file \n", NEW_FILE);
    printf("--- %d Open existing file \n", OPEN_FILE);
    printf("--- %d Exir \n", EXIT);
}

void processUserSelection(int usSelec)
{
    FILE *dataFile;
    switch (usSelec)
    {
    case NEW_FILE:
        // TODO: ask for a new file name
        dataFile = CreateFile("test.dat");
        long header = -1;

        fwrite(&header, sizeof(long), 1, dataFile);
        for (int i = 0; i < 3; i++)
        {
            REGISTER dataBlock = createNewDataBlock();
            fwrite(&dataBlock, sizeof(REGISTER), 1, dataFile);
        }

        fclose(dataFile);
        break;
    case OPEN_FILE:
        printf("Openning existing file \n");
        dataFile = OpenFile("test.dat");
        fseek(dataFile, 0, SEEK_END);
        for(int i = 0; i < 1; i++)
        {
            REGISTER dataBlock = createNewDataBlock();
            fwrite(&dataBlock, sizeof(REGISTER), 1, dataFile);
        }
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

FILE * OpenFile(const char* fileName)
{
    printf("Creating a new file... \n");
    FILE *dataFile = fopen(fileName, "rb+");

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