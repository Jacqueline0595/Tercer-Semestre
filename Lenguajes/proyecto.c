#include "main.h"

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
    switch(usSelec)
    {
        case NEW_FILE:
            printf("Creating a new file... \n");
            FILE *dataFile = fopen("test.dat", "wb+");

            REGISTER firstRecord;
            memset(firstRecord.name, '\0', STRING_LENGHT);
            strcat(firstRecord.name, "Jacqueline Gomez");
            firstRecord.generation = 2023;
            firstRecord.semester = 3;

            fwrite(&firstRecord, sizeof(REGISTER), 1, dataFile);

            fclose(dataFile);
        break;
        case OPEN_FILE:
            printf("Openning existing file \n");
        break;
        default:
            printf("Wrong option \n");
        break;
    }
}