#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAIN_HEADER_POSSITION 0L
#define ENTITY_NAME_LENGHT 50

typedef struct Entity
{
    char name[ENTITY_NAME_LENGHT];
    long dataPointer;
    long attributesPointer;
    long entityPointer;
} ENTITY;

long getDataDictionaryHeader(FILE *dataDictionary);
int appendEntity(FILE *dataDictionary, Entity dataEntity);

#endif