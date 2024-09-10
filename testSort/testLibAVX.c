#include "../lib/bitonic/bitonicAVX2.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LENGHT_TYPE long long

WORD_TYPE* generate_random_array(LENGHT_TYPE length);
WORD_TYPE random_num();
void _mm256_print(__m256i num);


int main()
{
    int singleWord;
    LENGHT_TYPE length;
	WORD_TYPE* arr;

    printf("single word? (y/n)? ");
    scanf(" %c", &singleWord);
    
    srand(time(NULL));

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
        _mm256_print(arr[i]);
    }
    printf("\n");
    
    sort(arr, length*WORD_LEN);

    for(LENGHT_TYPE i = length-1; i >= 0; i--)
    {
        _mm256_print(arr[i]);
    }
    printf("\n");

  	return 0;
}

WORD_TYPE* generate_random_array(LENGHT_TYPE length)
{    
    WORD_TYPE *array = (WORD_TYPE *)malloc(length * sizeof(WORD_TYPE));
    if (array == NULL) {
        fprintf(stderr, "Memory asizellocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for (LENGHT_TYPE i = 0; i < length; i++) {
        array[i] = random_num();
    }
    
    return array;
}

WORD_TYPE random_num()
{
    return _mm256_set_epi64x(rand(), rand(), rand(), rand());
}

void _mm256_print(__m256i num) {
    for (int i = WORD_LEN/64 -1; i >= 0; i--) {
        printf("%llX ", num[i]);
    }
    printf("\n");
}