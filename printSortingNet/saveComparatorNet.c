#include <stdio.h>
#include <stdbool.h>
#include "../sort/sort.h"
#include "../sort/comparator/compare.h"
#include "../utils/arrayUtils.h"

int main(int argc, char *argv[])
{
    Dlong length;
	int32* arr;
	
	if(argc < 2)
	{
		printf("Usage: %s <length>\n", argv[0]);
		return 1;
	}

	length = atoll(argv[1]);
	
    arr = generate_random_array(length, &length, false);
  	
  	mergExchange(arr, length, compareAndSave);
  	printArray(arr, length);

  	return 0;
}