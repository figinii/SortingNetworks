#include "compare.h"
#include <stdio.h>

int32 greater(int32 a, int32 b);
void swap(int32 *a, int32 *b, int32 swap);
void compare(int32 firstIndex, int32 secondIndex, int32* arr);

// check if b > a
// return 0 (0x0000) if a > b, -1 (0xFFFF) otherwise
int32 greater(int32 a, int32 b)
{
    int32 diff = a - b;
    int32 diffSign = diff >> 31;
    int32 invert = (a >> 31) & ~(b >> 31);
    return (invert | diffSign);
}

// swap a and b if swap is -1(0xFFFF), do nothing otherwise
void swap(int32 *a, int32 *b, int32 swap)
{
    int32 ab = *a ^ *b;
    int32 swapMask = ab & swap;
    *a ^= swapMask;
    *b ^= swapMask;
}

// compare a and b, swap them if b > a
void compare(int32 firstIndex, int32 secondIndex, int32* arr)
{
    swap(&arr[firstIndex], &arr[secondIndex], greater(arr[firstIndex], arr[secondIndex]));
}

// int main()
// {
//     int32 a;
//     int32 b;

//     scanf("%d", &a);
//     scanf("%d", &b);
//     printf("a > b ? %d\n", greater(a, b) < 0 ? 0 : 1);
//     compare(&a, &b);
//     printf("a: %d, b: %d\n", a, b);

//     return 0;
// }