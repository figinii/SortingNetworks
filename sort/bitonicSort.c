/*
    da fare:
    - iniziare con l'implementazione su 64 bit secchi... sulla single word
    - generatore dei blocchi marroni e dei blocchi rosa in funzione della dimensione.

    fare in modo che operi sui singoli bit; l'idea sarebbe quella di estrarre i bit utili 
    dalla parola in due poi usate per operare sui bit d'interesse, analogo con quanto fatto 
    con i confronti su bit pari e dispari

    poi estendere a fare confronti tra 2 parole da 64 a quel punto scrivi mail a Barenghi
    e chiedi se ha senso

    marrone: (k, n-k-1)  k=0; k<=n/2; k++;
    rosa: (k, k+n/2)  k=0; k<=n/2; k++; 
*/

#include <stdio.h>
#include <stdint.h>
#define WORD_LEN 64
#define WORD_TYPE uint64_t
#define ARR_LEN_TYPE long long 

#define ODD 0x5555555555555555
#define PAIR 0x3333333333333333
#define NIBBLE 0x0F0F0F0F0F0F0F0F
#define BYTE 0x00FF00FF00FF00FF
#define SHORT 0x0000FFFF0000FFFF
#define HALF_WORD 0x00000000FFFFFFFF

void printBitsWord(WORD_TYPE num, int dim);

WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter);
WORD_TYPE contiguosBit2power(int exp); /** può diventare una cache di (2^n)-1 con max n=64 */
void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2);

WORD_TYPE alternated01(int blockLen, int wordDim);
void brown(WORD_TYPE* num, int wordDim, int blockDim);
void rose(WORD_TYPE* num, int wordDim, int blockDim);

void wordBitonicSort(WORD_TYPE* word, int wordDim);

void brownArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim);
void roseArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim);
void arrBitonicSort(WORD_TYPE* arr, ARR_LEN_TYPE arrLenInBit, int wordDim);

int main()
{
    // WORD_TYPE num1 = 1245;
    // WORD_TYPE num2 = 1345;

    // printBitsWord(num1, WORD_LEN);
    // printBitsWord(num2, WORD_LEN);

    // compareAndSwapWord(&num1, &num2);
    // printBitsWord(num1, WORD_LEN);
    // printBitsWord(num2, WORD_LEN);

    // compareAndSwapWord(&num1, &num2);

    // printBitsWord(num1, WORD_LEN);
    // printBitsWord(num2, WORD_LEN);
    // printBitsWord(num1, WORD_LEN);
    // printBitsWord(num2, WORD_LEN);

    WORD_TYPE num3 = 38529352965235246;
    ARR_LEN_TYPE arrLen = 16;
    WORD_TYPE arr[arrLen];

    for(int i=0; i<arrLen; i++)
        arr[i] = num3;

    for(int i=arrLen-1; i>=0; i--){
        printf("%X", arr[i]);
    }
    printf("\n");

    arrBitonicSort(arr, arrLen * WORD_LEN, WORD_LEN);
    
    for(int i=arrLen-1; i>=0; i--){
        printf("%X", arr[i]);
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

void brown(WORD_TYPE* num, int wordDim, int blockDim)
{
    int halfLen = blockDim/2;
    WORD_TYPE upperMask;
    WORD_TYPE lowerMask;
    
    lowerMask = alternated01(halfLen, wordDim);
    upperMask = (wordReverse(*num, blockDim) & lowerMask);

    lowerMask = *num & lowerMask;

    compareAndSwapWord(&lowerMask, &upperMask);
    upperMask = wordReverse(upperMask, blockDim);

    *num = lowerMask | upperMask;
}

void rose(WORD_TYPE* num, int wordDim, int blockDim)
{
    int halfLen = blockDim/2;
    WORD_TYPE lowerMask = alternated01(halfLen, wordDim);
    WORD_TYPE upperMask = lowerMask << halfLen;

    lowerMask = *num & lowerMask;
    upperMask = (*num & upperMask) >> halfLen;

    compareAndSwapWord(&lowerMask, &upperMask);
    upperMask <<= halfLen;

    *num = lowerMask | upperMask;   
}

//da eliminare - inutilizzata
WORD_TYPE contiguosBit2power(int exp)
{
    return exp!=WORD_LEN? ((WORD_TYPE)1<<exp) -1 : -1;
}

//rendere array una define
WORD_TYPE wordReverse(WORD_TYPE word, int stopAfter)
{
    WORD_TYPE maskArr[] = {ODD, PAIR, NIBBLE, BYTE, SHORT, HALF_WORD};
    WORD_TYPE result = word;
    int i = 1;

    for(int j = 0; i<stopAfter; i<<=1, j++)
    {
        result = ((result >> i) & maskArr[j]) | ((result & maskArr[j]) << i);
    }

    return result;
}

//as input the power of 2 to use
WORD_TYPE alternated01(int blockLen, int wordDim)
{
    WORD_TYPE maskArr[] = {ODD, PAIR, NIBBLE, BYTE, SHORT, HALF_WORD};

    int pow = 0;

    for(; pow<wordDim; pow++)
    {
        if(blockLen & 1)
            break;

        blockLen >>= 1;
    }
    return maskArr[pow];
}

void wordBitonicSort(WORD_TYPE* word, int wordDim)
{
    
    for(int i = 2; i <= wordDim; i <<= 1)
    {
        brown(word, wordDim, i);

        for(int j = i/2; j>=2; j>>=1)
        {
            rose(word, wordDim, j);
        }
    }
}

void roseArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            rose(&arr[i], wordDim, (int)blockDim);
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

void brownArr(WORD_TYPE* arr, ARR_LEN_TYPE arrLen, int wordDim, ARR_LEN_TYPE blockDim)
{
    if(blockDim <= WORD_LEN)
    {
        for(ARR_LEN_TYPE i = 0; i < arrLen; i++)
            brown(&arr[i], wordDim, (int)blockDim);
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
        brownArr(arr, arrLenInWord, wordDim, i);

        for(ARR_LEN_TYPE j = i/2; j>=2; j>>=1)
        {
            roseArr(arr, arrLenInWord, wordDim, j);
        }
    }
}

