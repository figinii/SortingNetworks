#include <stdint.h>
#include <immintrin.h>
#include <time.h>

#define ARR_LEN_TYPE long long 
#define WORD_TYPE __m512i
#define WORD_LEN (sizeof(WORD_TYPE)*8)
#define LOG2(x) ((64 - 1) - __builtin_clzll(x))
#define COMPONENTS_DIM 64

#define ODD _mm512_set1_epi64(0x5555555555555555)
#define PAIR _mm512_set1_epi64(0x3333333333333333)
#define NIBBLE _mm512_set1_epi64(0x0F0F0F0F0F0F0F0F)
#define BYTE _mm512_set1_epi64(0x00FF00FF00FF00FF)
#define SHORT _mm512_set1_epi64(0x0000FFFF0000FFFF)
#define HALF_WORD _mm512_set1_epi64(0x00000000FFFFFFFF)
#define WORD _mm512_set_epi64(0, 0xFFFFFFFFFFFFFFFF, 0, 0xFFFFFFFFFFFFFFFF, 0, 0xFFFFFFFFFFFFFFFF, 0, 0xFFFFFFFFFFFFFFFF)
#define DOUBLE_WORD _mm512_set_epi64(0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)
#define QUADRUPLE_WORD _mm512_set_epi64(0, 0, 0, 0, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF)
    
#define MASK_ARRAY {ODD, PAIR, NIBBLE, BYTE, SHORT, HALF_WORD, WORD, DOUBLE_WORD, QUADRUPLE_WORD}


typedef void (*comparator)(WORD_TYPE*, WORD_TYPE* word2);

#define INITIALIZE_RANDOM_VECTOR(random)                  \
do {                                                      \
    srand(time(NULL));                                    \
    (random) = _mm512_set_epi64(rand(), rand(), rand(),   \
                                rand(), rand(), rand(),   \
                                rand(), rand());          \
}while(0)                                                 

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter);
WORD_TYPE alternated01(int blockLen);

void scrambler(WORD_TYPE* word1, WORD_TYPE* word2);
void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2);

void merger(WORD_TYPE* num, int blockDim, comparator cmp);
void bitonicSorter(WORD_TYPE* num, int blockDim, comparator cmp);
void singleWordSort(WORD_TYPE* word, comparator cmp);

void mergerArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim, comparator cmp);
void bitonicSorterArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim, comparator cmp);
void sort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit, comparator cmp);

__m512i _mm512_lShift(__m512i reg, unsigned int shift);
__m512i _mm512_rShift(__m512i reg, unsigned int shift);
__m512i _mm512_lWordShift(__m512i reg, unsigned int shift);
__m512i _mm512_rWordShift(__m512i reg, unsigned int shift);
uint64_t componentL(__m512i reg, unsigned int shift, int index);
uint64_t componentR(__m512i reg, unsigned int shift, int index);

void scrambler(WORD_TYPE* word1, WORD_TYPE* word2)
{
    WORD_TYPE random;
    INITIALIZE_RANDOM_VECTOR(random);
    WORD_TYPE scrambleMask = _mm512_xor_epi64(_mm512_and_epi64(*word1, random), 
                                      _mm512_and_epi64(*word2, random));

    *word1 = _mm512_xor_epi64(*word1, scrambleMask);
    *word2 = _mm512_xor_epi64(*word2, scrambleMask);
}

void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2)
{
    WORD_TYPE tmp = *word1 & *word2;
    *word2 = *word1 | *word2;
    *word1 = tmp; 
}

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter)
{
    WORD_TYPE maskArray[] = MASK_ARRAY;
    WORD_TYPE result = word;
    
    for(int j = 0, i = 1; i<stopAfter; i<<=1, j++)
    {
        result = _mm512_or_epi64(_mm512_and_epi64(_mm512_rShift(result, i), maskArray[j]),
                                 _mm512_lShift(_mm512_and_epi64(result, maskArray[j]), i));
    }

    return result;
}

WORD_TYPE alternated01(int blockLen)
{
    WORD_TYPE maskArray[] = MASK_ARRAY;
    int i = LOG2(blockLen);
    return maskArray[i];
}

void merger(WORD_TYPE* num, int blockDim, comparator cmp)
{
    int halfLen = blockDim/2;
    WORD_TYPE upperMask;
    WORD_TYPE lowerMask;
    
    lowerMask = alternated01(halfLen);
    upperMask = _mm512_and_epi64(wordReverse(*num, blockDim), lowerMask);

    lowerMask = _mm512_and_epi64(*num, lowerMask);

    cmp(&lowerMask, &upperMask);
    upperMask = wordReverse(upperMask, blockDim);

    *num = _mm512_or_epi64(lowerMask, upperMask);
}

void bitonicSorter(WORD_TYPE* num, int blockDim, comparator cmp)
{
    int halfLen = blockDim/2;
    WORD_TYPE lowerMask = alternated01(halfLen);
    WORD_TYPE upperMask = _mm512_lShift(lowerMask, halfLen);

    lowerMask = _mm512_and_epi64(*num, lowerMask);
    upperMask = _mm512_rShift(_mm512_and_epi64(*num, upperMask), halfLen);

    cmp(&lowerMask, &upperMask);
    upperMask = _mm512_lShift(upperMask, halfLen);

    *num = _mm512_or_epi64(lowerMask, upperMask);   
}

void singleWordSort(WORD_TYPE* word, comparator cmp)
{
    for(int i = 2; i <= WORD_LEN; i <<= 1)
    {
        merger(word, i, cmp);
        for(int j = i/2; j>=2; j>>=1)
        {
            bitonicSorter(word, j, cmp);
        }
    }
}

void bitonicSorterArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim, comparator cmp)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            bitonicSorter(&arr[i], (int)blockDim, cmp);
    }else
    {                               // >>6 = /(64)*2
        ARR_LEN_TYPE blockDimInWord = blockDim/WORD_LEN;
        ARR_LEN_TYPE halfDistance = blockDimInWord / 2;
        for(ARR_LEN_TYPE k = 0; k < arrLen; k+=blockDimInWord)
        {
            for(ARR_LEN_TYPE i = 0; i < blockDimInWord/2; i++){
                cmp(&arr[i+k], &arr[i+k+halfDistance]);
            }
        }

    }
}

void mergerArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, ARR_LEN_TYPE blockDim, comparator cmp)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            merger(&arr[i], (int)blockDim, cmp);
    }else
    {
        ARR_LEN_TYPE blockDimInWord = blockDim/WORD_LEN;

        for(ARR_LEN_TYPE k = 0; k < arrLen; k += blockDimInWord)
        {
            for(ARR_LEN_TYPE i = 0, j; i < blockDimInWord/2; i++)
            {
                j = blockDimInWord - i - 1;
                WORD_TYPE revertedTmp = wordReverse(arr[j+k], WORD_LEN);
                cmp(&arr[i+k], &revertedTmp);
                arr[j+k] = wordReverse(revertedTmp, WORD_LEN);
            }
        }    
    }
}

void sort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit, comparator cmp)
{
    ARR_LEN_TYPE arrLenInWord = arrLenInBit / WORD_LEN;

    if(arrLenInWord == 1)
    {
        singleWordSort(&arr[0], cmp);
        return;
    }


    for(ARR_LEN_TYPE i = 2; i <= arrLenInBit; i <<= 1)
    {   
        mergerArr(arr, arrLenInWord, i, cmp);

        for(ARR_LEN_TYPE j = i/2; j>=2; j>>=1)
        {
            bitonicSorterArr(arr, arrLenInWord, j, cmp);
        }
    }
}

WORD_TYPE _mm512_rShift(WORD_TYPE reg, unsigned int shift)
{
    unsigned int internalShift = shift % COMPONENTS_DIM;
    unsigned int externalShift = shift / COMPONENTS_DIM;
    __m512i leftShift, rightShift, result;
    
    result = reg;

    if(internalShift)
    {
        rightShift = _mm512_srli_epi64(reg, internalShift);
        leftShift = _mm512_slli_epi64(reg, COMPONENTS_DIM - internalShift);
        leftShift = _mm512_rWordShift(leftShift, 1);
        result = _mm512_or_epi64(leftShift, rightShift);
    }

    if(externalShift)
        result = _mm512_rWordShift(result, externalShift);

    return result;
}

WORD_TYPE _mm512_lShift(__m512i reg, unsigned int shift)
{
    unsigned int internalShift = shift % COMPONENTS_DIM;
    unsigned int externalShift = shift / COMPONENTS_DIM;
    __m512i leftShift, rightShift, result;
    
    result = reg;

    if(internalShift)
    {
        leftShift = _mm512_slli_epi64(reg, internalShift);
        rightShift = _mm512_srli_epi64(reg, COMPONENTS_DIM - internalShift);
        rightShift = _mm512_lWordShift(rightShift, 1);
        result = _mm512_or_epi64(leftShift, rightShift);
    }

    if(externalShift)
        result = _mm512_lWordShift(result, externalShift);

    return result;
}

__m512i _mm512_lWordShift(__m512i reg, unsigned int shift)
{       
    return _mm512_set_epi64(
        componentL(reg, shift, 7), componentL(reg, shift, 6),
        componentL(reg, shift, 5), componentL(reg, shift, 4),
        componentL(reg, shift, 3), componentL(reg, shift, 2),
        componentL(reg, shift, 1), componentL(reg, shift, 0));
}

__m512i _mm512_rWordShift(__m512i reg, unsigned int shift)
{       
    return _mm512_set_epi64(
        componentR(reg, shift, 7), componentR(reg, shift, 6),
        componentR(reg, shift, 5), componentR(reg, shift, 4),
        componentR(reg, shift, 3), componentR(reg, shift, 2),
        componentR(reg, shift, 1), componentR(reg, shift, 0));
}

uint64_t componentL(__m512i reg, unsigned int shift, int index)
{
    int indexShift = index - shift;
    if(indexShift < 0)
        return 0;
    return reg[indexShift];
}

uint64_t componentR(__m512i reg, unsigned int shift, int index)
{
    int indexShift = index + shift;
    if(indexShift > 7)
        return 0;
    return reg[indexShift];
}