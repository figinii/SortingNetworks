#include "./timedSortFunction.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#define MAX_LEN_IN_WORD 2056 

#define WORD_TYPE uint64_t 
#define LENGHT_TYPE long long

#define REQUIRED_PARAM 2
#define OPTIONS 1

WORD_TYPE* generate_random_array(LENGHT_TYPE length);
WORD_TYPE* copyArray(WORD_TYPE* arr, LENGHT_TYPE size);

int main(int argc, char* argv[])
{
	WORD_TYPE* arr;
    uint64_t cycles, time;
    int sampleSize = 500;
    FILE *results;

    if(argc < REQUIRED_PARAM || argc > REQUIRED_PARAM + OPTIONS)
    {
        printf("use: ./timedSort outputFile.csv (sampleSize)\n");
        return 1;
    }
    if(argc > REQUIRED_PARAM)
        sampleSize = argv[REQUIRED_PARAM + 0] - "0";

    
    
    results = fopen(argv[REQUIRED_PARAM - 1], "w");
    if(results == NULL)    
    {
        errno = EIO;
        perror("error opening the given file");
        return 1;
    }

    fprintf(results, "sampleLen,cycles,time\n");

    for(LENGHT_TYPE length = 1; length < MAX_LEN_IN_WORD; length <<= 1)
    {
        arr = generate_random_array(length);
        for(int j = 0; j < sampleSize; j++)
        {
            time = sortingTimedGetTime(arr, length*WORD_LEN);
            cycles = sortingTimedTSCReg(arr, length*WORD_LEN);
            fprintf(results, "%lld,%llu,%llu\n", length, cycles, time);
        }
    }

  	return 0;
}

WORD_TYPE* generate_random_array(LENGHT_TYPE length)
{
    srand(time(NULL));
    
    WORD_TYPE *array = (WORD_TYPE *)malloc(length * sizeof(WORD_TYPE));
    if (array == NULL) {
        fprintf(stderr, "Memory asizellocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (LENGHT_TYPE i = 0; i < length; i++) {
        array[i] = rand();
    }
    
    return array;
}

WORD_TYPE* copyArray(WORD_TYPE* arr, LENGHT_TYPE size)
{
    WORD_TYPE* copy = (WORD_TYPE*)malloc(size * sizeof(WORD_TYPE));
    for(WORD_TYPE i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}