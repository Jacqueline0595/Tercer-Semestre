#ifndef ENTITY_H
#define ENTITY_H
#define empty -1
#define LENGHT 50

typedef struct entity
{
    char name[LENGHT];
    long listDat;
    long listAttr;
    long sig;
} ENTITIES;

enum EntityOption 
{ 
    RETURN, 
    PRINT, 
    CREATE_ENTITY, 
    DELETE_ENTITY, 
    MODIFY_ENTITY, 
    SELECT_ENTITY 
};

void processInputDictonary(const char *dictionary);
void printDictionary(FILE *dict);
long createEntity(FILE *dict, ENTITIES newEntity);
void orderEntity(FILE *dict, long currentEntity, const char *newNameEntity, long newDirEntity);
int deleteEntity(FILE *dict, char name[LENGHT]);
ENTITIES findEntity(FILE *dict, char entityName[LENGHT]);
void modifyEntity(FILE *dict, char name[LENGHT]);

#endif