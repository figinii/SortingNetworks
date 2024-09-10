#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>

#define COMPONENTS_DIM 64
#define WORD_TYPE __m512i

void _mm512_print(__m512i num);
__m512i _mm512_rWordShift(__m512i reg, unsigned int shift);
uint64_t componentR(__m512i reg, unsigned int shift, int index);

int main()
{
    __m512i a = _mm512_set_epi64(0, 0xFFFFFFFFFFFFFFFF, 0, 0xFFFFFFFFFFFFFFFF,0, 0xFFFFFFFFFFFFFFFF, 0, 0xFFFFFFFFFFFFFFFF);
    _mm512_print(a);
    a = _mm512_rWordShift(a, 2);
    _mm512_print(a);

    return 0;
}

void _mm512_print(__m512i num)
{
    for (int i = 512/64 -1; i >= 0; i--) {
        printf("%llX ", num[i]);
    }
    printf("\n");
}

__m512i _mm512_rWordShift(__m512i reg, unsigned int shift)
{       
    for(int i = shift; i <= 7; i++)
    {
        reg[i-shift] = reg[i];
    }
    for(int i = 7; i > 7-shift; i--)
    {
        reg[i] = 0;
    }
    return reg;
}

uint64_t componentR(__m512i reg, unsigned int shift, int index)
{
    int indexShift = index + shift;
    if(indexShift > 7)
        return 0;
    return reg[indexShift];
}