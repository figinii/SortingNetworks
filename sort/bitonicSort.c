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
#define TYPE_LEN 64
#define WORD_TYPE uint64_t

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

int main()
{
    // WORD_TYPE num1 = 1245;
    // WORD_TYPE num2 = 1345;

    // printBitsWord(num1, TYPE_LEN);
    // printBitsWord(num2, TYPE_LEN);

    // compareAndSwapWord(&num1, &num2);
    // printBitsWord(num1, TYPE_LEN);
    // printBitsWord(num2, TYPE_LEN);

    // compareAndSwapWord(&num1, &num2);

    // printBitsWord(num1, TYPE_LEN);
    // printBitsWord(num2, TYPE_LEN);
    // printBitsWord(num1, TYPE_LEN);
    // printBitsWord(num2, TYPE_LEN);

    WORD_TYPE num3 = 91;
    printBitsWord(num3, TYPE_LEN);
    wordBitonicSort(&num3, TYPE_LEN);
    printBitsWord(num3, TYPE_LEN); 

}


void printBitsWord(WORD_TYPE num, int dim)
{
    for(int i=TYPE_LEN-1; i>=0; i--)
    {
        int tmp = (num>>i) &1;
        printf("%d", tmp);
    }
    printf("\n");
}

void compareAndSwapWord(WORD_TYPE* word1, WORD_TYPE* word2 /** order acending/descending */)
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

WORD_TYPE contiguosBit2power(int exp)
{
    return exp!=TYPE_LEN? ((WORD_TYPE)1<<exp) -1 : -1;
}

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

/** instead of generating use a map */
WORD_TYPE alternated01(int blockLen, int wordDim)
{
    int oddEvenLen = 2*blockLen;
    WORD_TYPE bitBlock = contiguosBit2power(blockLen);
    WORD_TYPE maskOnWord = bitBlock;

    for(int i=oddEvenLen; i<wordDim; i+=oddEvenLen)
    {   
        bitBlock <<= oddEvenLen;
        maskOnWord |= bitBlock;
    } 

    return maskOnWord;
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