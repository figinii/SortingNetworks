#include "comparatorList.h"

comparator *createComparator();
comparatorList *createNode(comparator *comparator);
void freeList(comparatorList *head);

comparator *createComparator()
{
    comparator *newComparator = (comparator *)malloc(sizeof(comparator));
    if (!newComparator)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    return newComparator;
}

comparatorList *createNode(comparator *comparator)
{
    comparatorList *newNode = (comparatorList *)malloc(sizeof(comparatorList));
    if (!newNode)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    newNode->comparator = comparator;
    newNode->next = NULL;

    return newNode;
}

void freeList(comparatorList *head)
{
    comparatorList *current = head;
    while (current != NULL)
    {
        comparatorList *next = current->next;
        free(current->comparator);
        free(current);
        current = next;
    }
}

