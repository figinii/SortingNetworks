#ifndef SORT_H
#define SORT_H

#include <stdint.h>
#include <stddef.h>


#define Dlong int64_t
#define int32 int32_t
typedef void (*comparator)(int32, int32, int32*);

void bubbleSort(int32 *a, Dlong dim);

void mergExchange(int32 *arr, Dlong dim, comparator comparator);

#endif