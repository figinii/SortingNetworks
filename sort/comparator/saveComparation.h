#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../utils/configs.h"

#pragma once

#define int32 int32_t

#define FILE_NAME_LEN 100
#define PATH_LEN FILE_NAME_LEN + 20

#define FILE_NAME "comparatorList_"

void printComparationToFile(int32 firstIndex, int32 secondIndex, bool swap);