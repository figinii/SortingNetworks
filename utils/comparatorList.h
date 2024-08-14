#ifndef COMPARE_LIST_H
#define COMPARE_LIST_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define COMPARATOR_ID '*'

typedef struct
{
    int firstIndex;
    int secondIndex;
    bool swap;
} comparatorStruct;

typedef struct comparatorList
{
    comparatorStruct *comparator;
    struct comparatorList *next;
    struct comparatorList *prev;
} comparatorList;


comparatorList *createNode(comparatorStruct *comparator);
void freeList(comparatorList *head);
comparatorStruct *createComparator();
comparatorList *buildComparatorListFromFile(FILE *file);

#endif