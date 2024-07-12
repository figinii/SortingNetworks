#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define Dlong long long
#define int32 int32_t

void printArray(int32 arr[], Dlong size);
int32* generate_random_array(Dlong max_length, Dlong *size);
int32* copyArray(int32* arr, Dlong size);
void freeArray(int32* arr);
bool areEqual(int32* arr1, int32* arr2, Dlong size);
int *bitwiseRep(int *rep, Dlong size, int num);
bool checkIfSorted(int32 *arr, Dlong size);
void reset(int32 *arr, Dlong size);

#endif