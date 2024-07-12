#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define int32 int32_t

void printArray(int32 arr[], int32 size);
int32* generate_random_array(int32 max_length, int32 *length);
int32* copyArray(int32* arr, int32 size);
void freeArray(int32* arr);
bool areEqual(int32* arr1, int32* arr2, int32 size);

#endif