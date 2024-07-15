#include <stdio.h>
#include <stdbool.h>
#include "sort.h"
#include "../utils/arrayUtils.h"
#define Dlong long long

// random arrays checks
int main()
{
  	Dlong length;
	Dlong maxLen;
  	char c;
	int32* arr;
	int32* backUp;
	bool randomSize;

	printf("max arr Length? ");
  	scanf("%lld", &maxLen);
	scanf("%c", &c);
  	printf("use a random arr (y/n)? ");
  	scanf("%c", &c);
	
  	if(c == 'y'){
		randomSize = true;
  	}else{
		randomSize = false;
	}

	arr = generate_random_array(maxLen, &length, randomSize);
  	backUp =  copyArray(arr, length);

  	bubbleSort(arr, length);
  	printArray(arr, length);

  	int32* arr1 = copyArray(arr, length);
  	arr = backUp;
  	backUp = copyArray(arr, length);

  	mergExchange(arr, length);
  	printArray(arr, length);

  	int32* arr2 = copyArray(arr, length);

  	printf("Are equal: %d\n", areEqual(arr1, arr2, length));

  	return 0;
}