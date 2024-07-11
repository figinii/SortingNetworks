#ifndef COMPARE_LIST_H
#define COMPARE_LIST_H

#include <stdlib.h>
#include <stdio.h>

#define COMPARATOR_ID '*'

typedef struct
{
    int firstIndex;
    int secondIndex;
} comparator;

typedef struct comparatorList
{
    comparator *comparator;
    struct comparatorList *next;
} comparatorList;

comparatorList *createNode(comparator *comparator);

void freeList(comparatorList *head);

comparator *createComparator();

#endif