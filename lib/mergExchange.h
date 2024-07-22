#ifndef MERGE_EXCHANGE_H
#define MERGE_EXCHANGE_H

#include <stdint.h>

#define Dlong int64_t
#define int32 int32_t

static inline void compare(int32 *first, int32 *second)
{
    int32 diff = *first - *second;
    int32 diffSign = diff >> 31;
    int32 invert = (*first >> 31) & ~(*second >> 31);
    int32 greater = (invert | diffSign);

    int32 ab = *first ^ *second;
    int32 swapMask = ab & greater;
    *first ^= swapMask;
    *second ^= swapMask;
}

void mergExchange(int32 *arr, Dlong dim);

#endif