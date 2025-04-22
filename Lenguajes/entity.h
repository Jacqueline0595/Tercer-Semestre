#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAIN_HEADER_POSSITION 0L
#define ENTITY_NAME_LENGHT 50
#define empty -1

typedef struct Entity
{
    char name[ENTITY_NAME_LENGHT];
    long listDat;
    long listAttr;
    long sig;
} ENTITY;

typedef struct Attribute
{
    char name[ENTITY_NAME_LENGHT];
    bool isPrimary;
    int type;
    int size;
    long nextAttribute;
} ATTRIBUTE;


long getDataDictionaryHeader(FILE *dataDictionary);
int appendEntity(FILE *dataDictionary, ENTITY dataEntity);

#endif