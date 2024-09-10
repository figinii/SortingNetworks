#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include "../lib/mergeExchange/mergExchange.h"

#define BILLION 1000000000L

#define MAX_LEN_IN_WORD 64 

#define LENGHT_TYPE long long

#define REQUIRED_PARAM 2
#define OPTIONS 1

int32* generate_random_array(long long length);
int32* copyArray(int32* arr, Dlong size);

uint64_t sortingTimedGetTime(int32_t* arr, long long arrLenInBit);
uint64_t sortingTimedTSCReg(int32_t* arr, long long arrLenInBit);

int main(int argc, char* argv[])
{
	int32_t* arr;
    uint64_t cycles, time;
    int sampleSize = 1000;
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

    for(LENGHT_TYPE length = 512; length <= 2048; length <<= 1)
    {
        arr = generate_random_array(length);
        for(int j = 0; j < sampleSize; j++)
        {
            time = sortingTimedGetTime(arr, length);
            cycles = sortingTimedTSCReg(arr, length);
            fprintf(results, "%lld,%llu,%llu\n", length, cycles, time);
        }
    }

  	return 0;
}

int32* generate_random_array(long long length) 
{
    srand(time(NULL));
    
    int *array = (int *)malloc(length * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory asizellocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < length; i++) {
        array[i] = rand();
    }
    
    return array;
}

int32* copyArray(int32* arr, Dlong size){
    int32* copy = (int32*)malloc(size * sizeof(int32));
    for(int32 i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}


uint64_t sortingTimedGetTime(int32_t* arr, long long arrLenInBit)
{
	struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    mergExchange(arr, arrLenInBit);
  	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

uint64_t sortingTimedTSCReg(int32_t* arr, long long arrLenInBit)
{
    unsigned int lo_start, hi_start, lo_end, hi_end;
    uint64_t start, end;

    asm volatile ("rdtsc" : "=a"(lo_start), "=d"(hi_start));
    mergExchange(arr, arrLenInBit);
    asm volatile ("rdtsc" : "=a"(lo_end), "=d"(hi_end));


    start = ((uint64_t)hi_start <<32) | lo_start;
    end = ((uint64_t)hi_end <<32) | lo_end;

    return end-start;
}