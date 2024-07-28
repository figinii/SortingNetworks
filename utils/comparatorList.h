#ifndef COMPARE_LIST_H
#define COMPARE_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define COMPARATOR_ID '*'

typedef struct
{
    int firstIndex;
    int secondIndex;
    bool swap;
} comparator;

typedef struct comparatorList
{
    comparator *comparator;
    struct comparatorList *next;
    struct comparatorList *prev;
} comparatorList;

comparatorList *createNode(comparator *comparator);

void freeList(comparatorList *head);

comparator *createComparator();

#endif