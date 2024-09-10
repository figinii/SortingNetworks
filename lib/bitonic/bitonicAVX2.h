#include <stdint.h>
#include <immintrin.h>

#define WORD_TYPE __m256i
#define WORD_LEN (sizeof(WORD_TYPE)*8)
#define COMPONENTS_DIM 64
#define LOG2(x) ((COMPONENTS_DIM - 1) - __builtin_clzll(x))

#define ODD _mm256_set1_epi64x(0x5555555555555555)
#define PAIR _mm256_set1_epi64x(0x3333333333333333)
#define NIBBLE _mm256_set1_epi64x(0x0F0F0F0F0F0F0F0F)
#define BYTE _mm256_set1_epi64x(0x00FF00FF00FF00FF)
#define SHORT _mm256_set1_epi64x(0x0000FFFF0000FFFF)
#define HALF_WORD _mm256_set1_epi64x(0x00000000FFFFFFFF)
#define WORD _mm256_set_epi64x(0, 0xFFFFFFFFFFFFFFFF, 0, 0xFFFFFFFFFFFFFFFF)
#define DOUBLE_WORD _mm256_set_epi64x(0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)
    
#define MASK_ARRAY {ODD, PAIR, NIBBLE, BYTE, SHORT, HALF_WORD, WORD, DOUBLE_WORD}

#define ARR_LEN_TYPE long long 

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter);
WORD_TYPE alternated01(int blockLen);
void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2);

void merger(WORD_TYPE* num, int blockDim);
void bitonicSorter(WORD_TYPE* num, int blockDim);
void singleWordSort(WORD_TYPE* word);

void mergerArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim);
void bitonicSorterArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim);
void sort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit);

__m256i _mm256_lShift(__m256i reg, unsigned int shift);
__m256i _mm256_rShift(__m256i reg, unsigned int shift);
__m256i _mm256_lWordShift(__m256i reg, unsigned int shift);
__m256i _mm256_rWordShift(__m256i reg, unsigned int shift);

void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2)
{
    WORD_TYPE tmp = _mm256_and_si256(*word1, *word2);
    
    *word2 = _mm256_or_si256(*word1, *word2);
    *word1 = tmp; 
}

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter)
{
    WORD_TYPE maskArray[] = MASK_ARRAY;
    WORD_TYPE result = word;
    
    for(int j = 0, i = 1; i<stopAfter; i<<=1, j++)
    {
        result = _mm256_or_si256(_mm256_and_si256(_mm256_rShift(result, i), maskArray[j]),
                                 _mm256_lShift(_mm256_and_si256(result, maskArray[j]), i));
    }

    return result;
}

WORD_TYPE alternated01(int blockLen)
{
    WORD_TYPE maskArray[] = MASK_ARRAY;
    int i = LOG2(blockLen);
    return maskArray[i];
}

void merger(WORD_TYPE* num, int blockDim)
{
    int halfLen = blockDim/2;
    WORD_TYPE upperMask;
    WORD_TYPE lowerMask;
    
    lowerMask = alternated01(halfLen);
    upperMask = _mm256_and_si256(wordReverse(*num, blockDim), lowerMask);

    lowerMask = _mm256_and_si256(*num, lowerMask);

    compareAndSwapWord(&lowerMask, &upperMask);
    upperMask = wordReverse(upperMask, blockDim);

    *num = _mm256_or_si256(lowerMask, upperMask);
}

void bitonicSorter(WORD_TYPE* num, int blockDim)
{
    int halfLen = blockDim/2;
    WORD_TYPE lowerMask = alternated01(halfLen);
    WORD_TYPE upperMask = _mm256_lShift(lowerMask, halfLen);

    lowerMask = _mm256_and_si256(*num, lowerMask);
    upperMask = _mm256_rShift(_mm256_and_si256(*num, upperMask), halfLen);

    compareAndSwapWord(&lowerMask, &upperMask);
    upperMask = _mm256_lShift(upperMask, halfLen);

    *num = _mm256_or_si256(lowerMask, upperMask);   
}

void singleWordSort(WORD_TYPE* word)
{
    for(int i = 2; i <= WORD_LEN; i <<= 1)
    {
        merger(word, i);
        for(int j = i/2; j>=2; j>>=1)
        {
            bitonicSorter(word, j);
        }
    }
}

void bitonicSorterArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            bitonicSorter(&arr[i], (int)blockDim);
    }else
    {                               // >>6 = /(64)*2
        ARR_LEN_TYPE blockDimInWord = blockDim/WORD_LEN;
        ARR_LEN_TYPE halfDistance = blockDimInWord / 2;
        for(ARR_LEN_TYPE k = 0; k < arrLen; k+=blockDimInWord)
        {
            for(ARR_LEN_TYPE i = 0; i < blockDimInWord/2; i++){
                compareAndSwapWord(&arr[i+k], &arr[i+k+halfDistance]);
            }
        }

    }
}

void mergerArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            merger(&arr[i], (int)blockDim);
    }else
    {
        ARR_LEN_TYPE blockDimInWord = blockDim/WORD_LEN;

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

void sort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit)
{
    ARR_LEN_TYPE arrLenInWord = arrLenInBit / WORD_LEN;

    if(arrLenInWord == 1)
    {
        singleWordSort(&arr[0]);
        return;
    }


    for(ARR_LEN_TYPE i = 2; i <= arrLenInBit; i <<= 1)
    {   
        mergerArr(arr, arrLenInWord, i);

        for(ARR_LEN_TYPE j = i/2; j>=2; j>>=1)
        {
            bitonicSorterArr(arr, arrLenInWord, j);
        }
    }
}

WORD_TYPE _mm256_rShift(WORD_TYPE reg, unsigned int shift)
{
    unsigned int internalShift = shift % COMPONENTS_DIM;
    unsigned int externalShift = shift / COMPONENTS_DIM;
    __m256i leftShift, rightShift, result;
    
    result = reg;

    if(internalShift)
    {
        rightShift = _mm256_srli_epi64(reg, internalShift);
        leftShift = _mm256_slli_epi64(reg, COMPONENTS_DIM - internalShift);
        leftShift = _mm256_rWordShift(leftShift, 1);
        result = _mm256_or_si256(leftShift, rightShift);
    }

    if(externalShift)
        result = _mm256_rWordShift(result, externalShift);

    return result;
}

WORD_TYPE _mm256_lShift(__m256i reg, unsigned int shift)
{
    unsigned int internalShift = shift % COMPONENTS_DIM;
    unsigned int externalShift = shift / COMPONENTS_DIM;
    __m256i leftShift, rightShift, result;
    
    result = reg;

    if(internalShift)
    {
        leftShift = _mm256_slli_epi64(reg, internalShift);
        rightShift = _mm256_srli_epi64(reg, COMPONENTS_DIM - internalShift);
        rightShift = _mm256_lWordShift(rightShift, 1);
        result = _mm256_or_si256(leftShift, rightShift);
    }

    if(externalShift)
        result = _mm256_lWordShift(result, externalShift);

    return result;
}

__m256i _mm256_lWordShift(__m256i reg, unsigned int shift)
{       
    for(int i = 3 - shift; i >= 0 ; i--)
    {
        reg[i + shift] = reg[i];
    }
    for(int i = 0; i < shift; i++)
    {
        reg[i] = 0;
    }
    return reg;
}

__m256i _mm256_rWordShift(__m256i reg, unsigned int shift)
{       
    for(int i = shift; i <= 3; i++)
    {
        reg[i-shift] = reg[i];
    }
    for(int i = 3; i > 3-shift; i--)
    {
        reg[i] = 0;
    }
    return reg;
}