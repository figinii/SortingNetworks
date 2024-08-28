#include "../lib/bitonic/bitonicSort.h"
#include <time.h>

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

    __asm__ volatile ("rdtsc" : "=a"(lo_start), "=d"(hi_start));
    sort(arr, arrLenInBit);
    __asm__ volatile ("rdtsc" : "=a"(lo_end), "=d"(hi_end));


    start = ((uint64_t)hi_start <<32) | lo_start;
    end = ((uint64_t)hi_end <<32) | lo_end;

    return end-start;
}