#include <stdio.h>
#include <stdbool.h>
#include "../lib/mergExchange.h"
#include "../utils/arrayUtils.h"
#define Dlong int64_t

// random arrays checks
int main()
{
  	Dlong length;
  	char c;
	int32* arr;

	printf("max arr Length? ");
  	scanf("%lld", &length);

	arr = generate_random_array(length, &length, false);
  	mergExchange(arr, length);
  	printArray(arr, length);

	printf("is sorted? %s\n", checkIfSorted(arr, length) ? "true" : "false");

  	return 0;
}