#include "arrayUtils.h"

void printArray(int32 arr[], Dlong size);
int32* generate_random_array(Dlong max_length, Dlong *size, bool randomSize);
int32* copyArray(int32* arr, Dlong size);
void freeArray(int32* arr);
bool areEqual(int32* arr1, int32* arr2, Dlong size);
int *bitwiseRep(int *arr, Dlong size, int num);
bool checkIfSorted(int32 *arr, Dlong zise);
void reset(int32 *arr, Dlong size);


void freeArray(int32* arr){
    free(arr);
}

int32* copyArray(int32* arr, Dlong size){
    int32* copy = (int32*)malloc(size * sizeof(int32));
    for(int32 i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}

int32* generate_random_array(Dlong max_length, Dlong *size, bool randomSize) 
{
    srand(time(NULL));
    
    if(randomSize){
        *size = rand() % max_length;
    }else{
        *size = max_length;
    }
    
    int *array = (int *)malloc(*size * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory asizellocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Populate the array with random values
    for (int i = 0; i < *size; i++) {
        array[i] = rand();
    }
    
    return array;
}

bool areEqual(int32* arr1, int32* arr2, Dlong size){
    for(int32 i = 0; i < size; i++){
        if(arr1[i] != arr2[i])
            return false;
    }
    return true;

}

void printArray(int32 arr[], Dlong size)
{
    int32 i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

bool checkIfSorted(int32 *arr, Dlong size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

int *bitwiseRep(int *arr, Dlong size, int num)
{
    reset(arr, size);
    for (int i = 0; i < size; i++)
    {
        arr[i] = num & 1;
        num >>= 1;
    }
    return arr;
}

void reset(int32 *arr, Dlong size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}