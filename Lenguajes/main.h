#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRING_LENGHT 100

typedef struct Register
{
    char name[STRING_LENGHT];
    int generation;
    int semester;
}REGISTER;

enum
{
    EXIT,
    NEW_FILE,
    OPEN_FILE
}OPTION;

void printMainMenu();
void processUserSelection(int usSelec);
FILE * CreateFile(const char* fileName);
REGISTER createNewDataBlock();