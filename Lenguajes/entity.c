#include "entity.h"

int appendEntity(FILE *dataDictionary, ENTITY dataEntity)
{
    const long nullPointer = -1L;
    long newEntityPosition = nullPointer;

    fseek(dataDictionary, MAIN_HEADER_POSSITION, SEEK_END);

    newEntityPosition = ftell(dataDictionary);

    fwrite(dataEntity.name, sizeof(char), sizeof(dataEntity.name), dataDictionary );
    fwrite(dataEntity.dataPointer, sizeof(long), 1,dataDictionary);
    fwrite(dataEntity.attributesPointer, sizeof(long), 1, dataDictionary );
    fwrite(dataEntity.entityPointer, sizeof(long), 1, dataDictionary );

    printf("New Entity \"%s added at position %ld \n" dataEntity.name, newEntityPosition );
    return newEntityPosition;
}

long getDataDictionaryHeader(FILE *dataDictionary)
{
    long header;

    fseek(dataDictionary, MAIN_HEADER_POSSITION, SEEK_SET);
    fread(&header, sizeof(header), 1, dataDictionary);

    return header;
}