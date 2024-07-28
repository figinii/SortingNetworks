#ifndef COMPARE_H
#define COMPARE_H

#include <stdint.h>
#include <stdbool.h>

#define int32 int32_t

void compare(int32 firstIndex, int32 secondIndex, int32* arr);
void compareAndSave(int32 firstIndex, int32 secondIndex, int32* arr);

#endif