#ifndef SORT_H
#define SORT_H

#include <stdint.h>

#define Dlong long long
#define int32 int32_t

#define INT_MAX 2147483647
#define INT_MIN -2147483648

void bubbleSort(int32 *a, int dim);

void oddEvenSort(int32 *arr, Dlong dim);

#endif