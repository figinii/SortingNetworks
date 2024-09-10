#include "../lib/bitonic/bitonicSortIntrinsic.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WORD_TYPE __m512i 
#define COMPONENTS_DIM 64
#define WORD_LEN (sizeof(WORD_TYPE)*8)
#define LENGHT_TYPE int64_t

#define BILLION 1000000000L

uint64_t sortingTimedGetTime(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit);
uint64_t sortingTimedTSCReg(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit);
WORD_TYPE* generate_random_array(LENGHT_TYPE length);
WORD_TYPE random_num();
void _mm512_print(__m512i num);


int main()
{
    LENGHT_TYPE length;
	WORD_TYPE* arr;
    FILE *file;

    srand(time(NULL));

    // file = fopen("./test2.csv", "w");

	printf("arr Length? ");
  	scanf("%lld", &length);

	arr = generate_random_array(length);

    for(LENGHT_TYPE i = 0; i < length; i++){
        _mm512_print(arr[i]);
    }
    printf("\n");

    int a,b;
    for(int i = 0; i< 1000; i++)
    {
        a = sortingTimedGetTime(arr, length*WORD_LEN);
        b = sortingTimedTSCReg(arr, length*WORD_LEN);
        printf("%d, %d, %d\n", length*512, a, b);
    }

    for(LENGHT_TYPE i = length-1; i >= 0; i--)
    {
        _mm512_print(arr[i]);
    }
    printf("\n");

  	return 0;
}

WORD_TYPE* generate_random_array(LENGHT_TYPE length)
{    
    WORD_TYPE *array = (WORD_TYPE *)malloc(length * sizeof(WORD_TYPE));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (LENGHT_TYPE i = 0; i < length; i++) {
        array[i] = random_num();
    }
    
    return array;
}

WORD_TYPE random_num()
{
    return _mm512_set_epi64(rand(), rand(), rand(), rand(), rand(), rand(), rand(), rand());
}

void _mm512_print(__m512i num) {
    for (int i = WORD_LEN/64 -1; i >= 0; i--) {
        printf("%llX ", num[i]);
    }
    printf("\n");
}

#define BILLION 1000000000L

uint64_t sortingTimedGetTime(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit)
{
	struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    sort(arr, arrLenInBit);
  	clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    return BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
}

uint64_t sortingTimedTSCReg(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit)
{
    unsigned int lo_start, hi_start, lo_end, hi_end;
    uint64_t start, end;

    asm volatile ("rdtsc" : "=a"(lo_start), "=d"(hi_start));
    sort(arr, arrLenInBit);
    asm volatile ("rdtsc" : "=a"(lo_end), "=d"(hi_end));


    start = ((uint64_t)hi_start <<32) | lo_start;
    end = ((uint64_t)hi_end <<32) | lo_end;

    return end-start;
}