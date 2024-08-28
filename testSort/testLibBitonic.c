#include "../lib/bitonic/bitonicSort.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WORD_TYPE uint64_t 
#define WORD_LEN (sizeof(uint64_t)*8)
#define LENGHT_TYPE long long

WORD_TYPE* generate_random_array(LENGHT_TYPE length);
void printBitsWord(WORD_TYPE num)
{
    for(LENGHT_TYPE i=WORD_LEN-1; i>=0; i--)
    {
        LENGHT_TYPE tmp = (num>>i) &1;
        printf("%d", tmp);
    }
    printf("\n");
}
int main()
{
    int singleWord;
    LENGHT_TYPE length;
	WORD_TYPE* arr;

    printf("single word? (y/n)? ");
    scanf(" %c", &singleWord);
    
    if(singleWord == 'y')
        singleWord = 1;
    else
        singleWord = 0;

    if(!singleWord)
    {
        while (getchar() != '\n');
	    printf("arr Length? ");
  	    scanf("%lld", &length);
    }else
    {
        length = 1;
    }

	arr = generate_random_array(length);
    
    for(LENGHT_TYPE i = 0; i < length; i++){
        printf("%X", arr[i]);
    }
    printf("\n");
    sort(arr, length*WORD_LEN);

    for(LENGHT_TYPE i = length-1; i >= 0; i--)
    {
        if(singleWord)
            printBitsWord(arr[i]);
        else
            printf("%X", arr[i]);
    }
    printf("\n");

  	return 0;
}
WORD_TYPE* generate_random_array(LENGHT_TYPE length)
{
    srand(time(NULL));
    
    WORD_TYPE *array = (WORD_TYPE *)malloc(length * sizeof(WORD_TYPE));
    if (array == NULL) {
        fprintf(stderr, "Memory asizellocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (LENGHT_TYPE i = 0; i < length; i++) {
        array[i] = rand();
    }
    
    return array;
}