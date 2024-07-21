#include <stdio.h>
#include <stdbool.h>
#include "../sort/sort.h"
#include "../sort/comparator/compare.h"
#include "../utils/arrayUtils.h"

int main(int argc, char *argv[])
{
    Dlong length;
	int32* arr;
	
	printf("input Length? ");
  	scanf("%lld", &length);
	
    arr = generate_random_array(length, &length, false);
  	
  	mergExchange(arr, length, compareAndSave);
  	printArray(arr, length);

  	return 0;
}