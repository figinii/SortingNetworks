#include "arrayUtils.h"

void printArray(int32 arr[], int32 size);
int32 random_int(int32 min, int32 max);
int32* generate_random_array(int32 max_length, int32 *length);
int32* copyArray(int32* arr, int32 size);
void freeArray(int32* arr);
bool areEqual(int32* arr1, int32* arr2, int32 size);


void freeArray(int32* arr){
    free(arr);
}

int32* copyArray(int32* arr, int32 size){
    int32* copy = (int32*)malloc(size * sizeof(int32));
    for(int32 i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}

int32* generate_random_array(int32 max_length, int32 *length) 
{
    srand(time(NULL));
    
    *length = rand() % max_length;
    
    int *array = (int *)malloc(*length * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    printf("%d\n", *length);
    // Populate the array with random values
    for (int i = 0; i < *length; i++) {
        array[i] = rand();
    }
    
    return array;
}

bool areEqual(int32* arr1, int32* arr2, int32 size){
    for(int32 i = 0; i < size; i++){
        if(arr1[i] != arr2[i])
            return false;
    }
    return true;

}

void printArray(int32 arr[], int32 size)
{
    int32 i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}