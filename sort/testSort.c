#include <stdio.h>
#include "sort.h"
#include "../utils/arrayUtils.h"

// random arrays checks
int main()
{
  int32 length;
  int32* arr = generate_random_array(1000, &length);
  int32* backUp =  copyArray(arr, length);

  bubbleSort(arr, length);
  printArray(arr, length);

  int32* arr1 = copyArray(arr, length);
  arr = backUp;
  backUp = copyArray(arr, length);

  oddEvenSort(arr, length);
  printArray(arr, length);

  int32* arr2 = copyArray(arr, length);

  printf("Are equal: %d\n", areEqual(arr1, arr2, length));

  return 0;
}