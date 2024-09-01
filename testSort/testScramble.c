#include "../lib/bitonic/bitonicCmpParam.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WORD_TYPE __m512i 
#define COMPONENTS_DIM 64
#define WORD_LEN (sizeof(WORD_TYPE)*8)
#define LENGHT_TYPE int64_t

WORD_TYPE* generate_random_array(LENGHT_TYPE length);
WORD_TYPE random_num();
void _mm512_print(__m512i num);


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
        _mm512_print(arr[i]);
    }
    printf("\n");
    
    sort(arr, length*WORD_LEN, compareAndSwapWord);

    for(LENGHT_TYPE i = length-1; i >= 0; i--)
    {
        _mm512_print(arr[i]);
    }
    printf("\n");

    sort(arr, length*WORD_LEN, scrambler);

    for(LENGHT_TYPE i = length-1; i >= 0; i--)
    {
        _mm512_print(arr[i]);
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
    srand(time(NULL));
    return _mm512_set_epi64(1, 0, 0, 0, 0, 0, 0, 0);
}

void _mm512_print(__m512i num) {
    for (int i = WORD_LEN/64 -1; i >= 0; i--) {
        printf("%llX ", num[i]);
    }
    printf("\n");
}