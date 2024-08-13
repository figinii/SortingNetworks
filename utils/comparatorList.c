#include "comparatorList.h"

comparatorStruct *createComparator();
comparatorList *createNode(comparatorStruct *comparator);
void freeList(comparatorList *head);
comparatorList *buildComparatorListFromFile(FILE *file);

comparatorStruct *createComparator()
{
    comparatorStruct *newComparator = (comparatorStruct *)malloc(sizeof(comparatorStruct));
    if (!newComparator)
    {
        printf("Memory allocation error\n");
        exit(1);
    }
    return newComparator;
}

comparatorList *createNode(comparatorStruct *comparator)
{
    comparatorList *newNode = (comparatorList *)malloc(sizeof(comparatorList));
    if (!newNode)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    newNode->comparator = comparator;
    newNode->next = NULL;
    newNode->prev = NULL;
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

comparatorList *buildComparatorListFromFile(FILE *file){
    char buffer[100];
    comparatorList *head = NULL;
    comparatorList *last = NULL;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        
        comparatorStruct *newComparator = createComparator();
        newComparator->firstIndex = atoi(strtok(buffer, " "));
        newComparator->secondIndex = atoi(strtok(NULL, " "));
        newComparator->swap = atoi(strtok(NULL, " ")) == 1;

        comparatorList *newNode = createNode(newComparator);
        if(head == NULL){
            head = newNode;
            last = newNode;
        } else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        }
    }
    return head;
}
