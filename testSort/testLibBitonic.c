#include "../lib/bitonic/bitonicSort.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

uint64_t* generate_random_array(long long max_length, long long *size, bool randomSize);

void printBitsWord(WORD_TYPE num, int dim)
{
    for(int i=WORD_LEN-1; i>=0; i--)
    {
        int tmp = (num>>i) &1;
        printf("%d", tmp);
    }
    printf("\n");
}

int main()
{
    long long length;
	uint64_t* arr;

	printf("max arr Length? ");
  	scanf("%lld", &length);

	arr = generate_random_array(length, &length, false);

    for(long i = 0; i < length; i++){
        printf("%X", arr[i]);
    }
    printf("\n");

    sort(arr, length*WORD_LEN);
  	
    for(long i = length-1; i >= 0; i--)
    {
        //printBitsWord(arr[i], 64);
        printf("%X", arr[i]);
    }
    printf("\n");

  	return 0;
}

uint64_t* generate_random_array(long long max_length, long long *size, bool randomSize)
{
    srand(time(NULL));
    
    if(randomSize){
        *size = rand() % max_length;
    }else{
        *size = max_length;
    }
    
    uint64_t *array = (uint64_t *)malloc(*size * sizeof(uint64_t));
    if (array == NULL) {
        fprintf(stderr, "Memory asizellocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    // Populate the array with random values
    for (long long i = 0; i < *size; i++) {
        array[i] = rand();
    }
    
    return array;
}