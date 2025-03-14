#include "main.h"

// Hola

int main()
{
    int userSelection;
    do{
        printMainMenu();
        scanf("%d", &userSelection);
        processUserSelection(userSelection);
    } while(userSelection != EXIT);

    return 0;
}

void printMainMenu()
{
    printf("\t ---------Main menu--------- \n");
    printf("--- %d Create new file \n", NEW_FILE);
    printf("--- %d Open existing file \n", OPEN_FILE);
    printf("--- %d Exit \n", EXIT);
}

void processUserSelection(int usSelec)
{
    FILE *dataFile = NULL;
    switch (usSelec)
    {
        case NEW_FILE:
            // TODO: ask for a new file name
            dataFile = CreateFile("test.dat");
            if(dataFile)
            {
                long header = -1;
                fwrite(&header, sizeof(long), 1, dataFile);
                for (int i = 0; i < 1; i++)
                {
                    REGISTER dataBlock = createNewDataBlock();
                    fwrite(&dataBlock, sizeof(REGISTER), 1, dataFile);
                }

                fclose(dataFile);
            }
        break;
        case OPEN_FILE:
            printf("Openning existing file \n");
            /* dataFile = OpenFile("test.dat");
            fclose(dataFile); */
            processInputDictonary();
        break;
        case EXIT:
            printf("Bye bye \n");
        break;
        default:
            printf("Wrong option \n");
        break;
    }
    fclose(dataFile);
}

FILE *CreateFile(const char *fileName)
{
    printf("Creating a new file... \n");
    FILE *dataFile = fopen(fileName, "wb+");

    if(!dataFile)
        fprintf(stderr, "Error creating file\n");

    return dataFile;
}

FILE *OpenFile(const char *fileName)
{
    FILE *dataFile = fopen(fileName, "rb+");
    if(dataFile)
    {
        printf("Dictionary name: %s \n", fileName);
        printDictionaryMenu();
    }
    return dataFile;
}

REGISTER createNewDataBlock()
{
    REGISTER dataBlock;

    printf("Enter the name: ");
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

void processInputDictonary()
{
    int userSelec;
    do{
        printDictionaryMenu();
        scanf("%d", &userSelec);
        switch(userSelec)
        {
            case PRINT:
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

int openDataDictionary(const char * fileName)
{
    int operationResult = EXIT_SUCCESS;
    long header;
    FILE *file = fopen(fileName, "rb");

    if(file)
    {
        if(fread(&header, sizeof(header), 1, file) != 1)
        {
            fprintf(stderr, "Failed to read data. \n");
            operationResult = EXIT_FAILURE;
        } else {
            printf("The header value is: %ld \n", header);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Failed to open the data dictionary \n");
        operationResult = EXIT_FAILURE;
    }
    return operationResult;
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