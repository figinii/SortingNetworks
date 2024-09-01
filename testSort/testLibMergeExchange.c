#include <stdio.h>
#include <stdbool.h>
#include "../lib/mergeExchange/mergExchange.h"
#include "../utils/arrayUtils.h"
#define Dlong int64_t

int main()
{
  	Dlong length;
  	char c;
	int32* arr;

	printf("arr Length? ");
  	scanf("%lld", &length);

	arr = generate_random_array(length, &length, false);
	printArray(arr, length);
  	mergExchange(arr, length);
  	printArray(arr, length);

	printf("is sorted? %s\n", checkIfSorted(arr, length) ? "true" : "false");

  	return 0;
}