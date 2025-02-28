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

enum
{
    RETURN,
    PRINT,
    CREATE_ENTITY,
    DELETE_ENTITY,
    MODIFY_ENTITY,
    SELECT_ENTITY
}OPTIONEntity;

enum
{
    RETURN2,
    PRINT2,
    CREATE_ATTRIBUTE,
    DELETE_ATTRIBUTE,
    MODIFY_ATTRIBUTE,
    SELECT_ATTRIBUTE
}OPTIONAttribute;

void printMainMenu();
void processUserSelection(int usSelec);
FILE * CreateFile(const char* fileName);
FILE * OpenFile(const char* fileName);
REGISTER createNewDataBlock();
void processInputDictonary();
void printDictionaryMenu(); // Data dictionary menu
void processInputEntity();
void printEntityMenu();

