#include <stdio.h>
#include <stdint.h>

#define WORD_LEN 64
#define WORD_TYPE uint64_t
#define LOG2_64(x) ((sizeof(int64_t) * 8 - 1) - __builtin_clzll(x))

#define ODD 0x5555555555555555
#define PAIR 0x3333333333333333
#define NIBBLE 0x0F0F0F0F0F0F0F0F
#define BYTE 0x00FF00FF00FF00FF
#define SHORT 0x0000FFFF0000FFFF
#define HALF_WORD 0x00000000FFFFFFFF
#define MASK_ARRAY {ODD, PAIR, NIBBLE, BYTE, SHORT, HALF_WORD}

#define ARR_LEN_TYPE long long 

void printBitsWord(WORD_TYPE num, int dim);

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter);
void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2);

WORD_TYPE alternated01(int blockLen);
void merger(WORD_TYPE* num, int wordDim, int blockDim);
void bitonicSorter(WORD_TYPE* num, int wordDim, int blockDim);

void wordBitonicSort(WORD_TYPE* word, int wordDim);

void mergerArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim);
void bitonicSorterArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim);
void arrBitonicSort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit, int wordDim);

int main()
{
    WORD_TYPE num = 38529352965235246;
    ARR_LEN_TYPE arrLen = 16;
    WORD_TYPE arr[arrLen];

    for(int i=0; i<arrLen; i++)
        arr[i] = num;

    for(int i=arrLen-1; i>=0; i--){
        printf("%X", arr[i]);
    }
    printf("\n");

    arrBitonicSort(arr, arrLen * WORD_LEN, WORD_LEN);
    
    for(int i=0; i<arrLen; i++){
        //printBitsWord(arr[i], WORD_LEN);
        printf("%X", arr[i]);
        //printf("\n");
    }

    printf("\n");


}


void printBitsWord(WORD_TYPE num, int dim)
{
    for(int i=WORD_LEN-1; i>=0; i--)
    {
        int tmp = (num>>i) &1;
        printf("%d", tmp);
    }
}

void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2)
{
    WORD_TYPE tmp = *word1 & *word2;
    
    *word2 = *word1 | *word2;
    *word1 = tmp; 
}

void merger(WORD_TYPE* num, int wordDim, int blockDim)
{
    int halfLen = blockDim/2;
    WORD_TYPE upperMask;
    WORD_TYPE lowerMask;
    
    lowerMask = alternated01(halfLen);
    upperMask = (wordReverse(*num, blockDim) & lowerMask);

    lowerMask = *num & lowerMask;

    compareAndSwapWord(&lowerMask, &upperMask);
    upperMask = wordReverse(upperMask, blockDim);

    *num = lowerMask | upperMask;
}

void bitonicSorter(WORD_TYPE* num, int wordDim, int blockDim)
{
    int halfLen = blockDim/2;
    WORD_TYPE lowerMask = alternated01(halfLen);
    WORD_TYPE upperMask = lowerMask << halfLen;

    lowerMask = *num & lowerMask;
    upperMask = (*num & upperMask) >> halfLen;

    compareAndSwapWord(&lowerMask, &upperMask);
    upperMask <<= halfLen;

    *num = lowerMask | upperMask;   
}

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter)
{
    WORD_TYPE maskArray[] = MASK_ARRAY;
    WORD_TYPE result = word;
    int i = 1;

    for(int j = 0; i<stopAfter; i<<=1, j++)
    {
        result = ((result >> i) & maskArray[j]) | ((result & maskArray[j]) << i);
    }

    return result;
}

WORD_TYPE alternated01(int blockLen)
{
    WORD_TYPE maskArray[] = MASK_ARRAY;
    return maskArray[LOG2_64(blockLen)];
}

void wordBitonicSort(WORD_TYPE* word, int wordDim)
{
    
    for(int i = 2; i <= wordDim; i <<= 1)
    {
        merger(word, wordDim, i);

        for(int j = i/2; j>=2; j>>=1)
        {
            bitonicSorter(word, wordDim, j);
        }
    }
}

void bitonicSorterArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            bitonicSorter(&arr[i], wordDim, (int)blockDim);
    }else
    {                               // >>6 = /(64)*2
        ARR_LEN_TYPE blockDimInWord = blockDim/wordDim;
        ARR_LEN_TYPE halfDistance = blockDimInWord / 2;
        for(ARR_LEN_TYPE k = 0; k < arrLen; k+=blockDimInWord)
        {
            for(ARR_LEN_TYPE i = 0; i < blockDimInWord/2; i++){
                compareAndSwapWord(&arr[i+k], &arr[i+k+halfDistance]);
            }
        }

    }
}

void mergerArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            merger(&arr[i], wordDim, (int)blockDim);
    }else
    {
        ARR_LEN_TYPE blockDimInWord = blockDim/wordDim;

        for(ARR_LEN_TYPE k = 0; k < arrLen; k += blockDimInWord)
        {
            for(ARR_LEN_TYPE i = 0, j; i < blockDimInWord/2; i++)
            {
                j = blockDimInWord - i - 1;
                WORD_TYPE revertedTmp = wordReverse(arr[j+k], WORD_LEN);
                compareAndSwapWord(&arr[i+k], &revertedTmp);
                arr[j+k] = wordReverse(revertedTmp, WORD_LEN);
            }
        }    
    }
}

void arrBitonicSort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit, int wordDim)
{
    ARR_LEN_TYPE arrLenInWord = arrLenInBit / wordDim;
    for(ARR_LEN_TYPE i = 2; i <= arrLenInBit; i <<= 1)
    {
        mergerArr(arr, arrLenInWord, wordDim, i);

        for(ARR_LEN_TYPE j = i/2; j>=2; j>>=1)
        {
            bitonicSorterArr(arr, arrLenInWord, wordDim, j);
        }
    }
}

