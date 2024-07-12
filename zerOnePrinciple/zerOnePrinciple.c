#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../utils/comparatorList.h"

int numOfImputs(FILE *inFile)
{
    int numOfImputs = -1;
    int ch;

    do
    {
        numOfImputs++;
        ch = fgetc(inFile);
    } while (ch != EOF && ch != '\n');
    fseek(inFile, 0, SEEK_SET);
    return numOfImputs;
}

comparatorList *sortingNetworkComparatorList(FILE *inFile)
{

    int inputLen = numOfImputs(inFile);
    char *line = malloc((inputLen + 2) * sizeof(char));
    comparatorList *head = NULL;
    comparatorList *tail = NULL;

    while (fgets(line, inputLen + 2, inFile))
    {
        line[inputLen] = '\0';
        // printf("Line: %s\n", line);
        comparator *newComparator = NULL;
        for (int i = 0; i < inputLen; i++)
        {
            if (line[i] == COMPARATOR_ID)
            {
                if (newComparator == NULL)
                {
                    newComparator = createComparator();
                    newComparator->firstIndex = i;
                }
                else
                {
                    newComparator->secondIndex = i;
                    comparatorList *newNode = createNode(newComparator);
                    if (head == NULL)
                    {
                        head = newNode;
                        tail = newNode;
                    }
                    else
                    {
                        tail->next = newNode;
                        tail = newNode;
                    }
                    newComparator = NULL;
                }
            }
        }
    }
    free(line);
    fseek(inFile, 0, SEEK_SET);
    return head;
}

void reset(int *rep, int inputLen)
{
    for (int i = 0; i < inputLen; i++)
    {
        rep[i] = 0;
    }
}

int *bitwiseRep(int *rep, int inputLen, int num)
{
    reset(rep, inputLen);
    for (int i = 0; i < inputLen; i++)
    {
        rep[i] = num & 1;
        num >>= 1;
    }
    return rep;
}

bool checkIfSorted(int *input, int inputLen)
{
    for (int i = 0; i < inputLen - 1; i++)
    {
        if (input[i] < input[i + 1])
        {
            return false;
        }
    }
    return true;
}

void compare(int *a, int *b)
{
    if (*a < *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

/* void printArray(int* arr, int size){
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
} */

bool zerOnePrinciple(comparatorList *head, int inputLen)
{
    int *input = (int *)calloc(inputLen, sizeof(int));
    for (int i = 0; i < pow(2, inputLen); i++)
    {
        bitwiseRep(input, inputLen, i);
        for (comparatorList *current = head; current != NULL; current = current->next)
        {
            compare(&input[current->comparator->firstIndex], &input[current->comparator->secondIndex]);
        }
        //        printArray(input, inputLen);
        if (!checkIfSorted(input, inputLen))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    FILE *inFile = fopen("oddEvenMerge.txt", "r");
    if (inFile == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // printf("Number of inputs: %d\n", numOfImputs(inFile));
    comparatorList *head = sortingNetworkComparatorList(inFile);
    /* printf("Comparators:\n");
    for(comparatorList* current = head; current != NULL; current = current->next){
        printf("First index: %d, Second index: %d\n", current->comparator->firstIndex, current->comparator->secondIndex);
    } */
    if (zerOnePrinciple(head, numOfImputs(inFile)))
    {
        printf("The sorting network satisfies the 0-1 principle\n");
    }
    else
    {
        printf("The sorting network does not satisfy the 0-1 principle\n");
    }

    fclose(inFile);
    freeList(head);
    return 0;
}